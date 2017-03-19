/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 13:28:38 by mleclair          #+#    #+#             */
/*   Updated: 2017/05/01 17:11:30 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

void	parse3(t_env *env, int i)
{
	extracredir(env, 0, 0);
	while (env->redir[++i] != '>')
		;
	if (env->redir[i] == '>' && env->redir[i + 1] == '>')
		rd_output_apd(env, -1, -1);
	else if (env->redir[i] == '>' && env->redir[i + 1] != '>')
		rd_output(env, -1, -1, -1);
	free(env->redir);
	env->redir = NULL;
}

void	parse2(t_env *env, char **input, int i)
{
	if (verredir(env) == -1)
		return ;
	if (cmprevtruc(env, input))
		;
	else if (cmprev(*input, "|") != -1)
		rd_pipe(env);
	else if (cmprev(*input, "<<<") != -1)
		rd_here_string(env, -1, -1, -1);
	else if (cmprev(*input, "<<") != -1)
	{
		extract_heredoc(env);
		rd_here_doc(env, -1, -1);
	}
	else if (cmprev(*input, "<") != -1)
	{
		extract_rd_output(env, env->input);
		rd_input(env, -1);
	}
	else if (cmprev(*input, ">") != -1 || cmprev(*input, ">>") != -1)
		parse3(env, i);
	else
		ft_reco_cmd(env, 0);
}

void	parse(t_env *env, char **input)
{
	int		i;

	i = -1;
	free(env->input);
	env->input = ft_strdup(*input);
	while (ft_strchr(env->input, '`') != 0)
		if (bquote(env, input) == -1)
			return ;
	if ((env->bool2 == 1 && !ft_read(env, env->input, -1, 0))
		|| env->input == NULL)
		return ;
	if (ft_strchr(env->input, '$'))
		ft_dollar(env, -1, 0);
	if (parserror(env) == -1)
		return ;
	if (ft_strfind(*input, '(') != -1 || ft_strfind(*input, ')') != -1)
		if (subshell(env, input) == -1)
			return ;
	if (env->bool2 == 1 && !ft_read(env, ft_strdup(*input), -1, 0))
		return ;
	parse2(env, input, i);
	if (env->inp1)
		ft_strdel(&env->inp1);
	if (env->inp2)
		ft_strdel(&env->inp2);
}

char	*hijack_prompt(t_env *env)
{
	// if (env->cond != NULL)
	// 	printf("Current condition is: %d", env->cond->type);
	if (env->cond == NULL)
		return (PROMPT);
	else if (env->cond->type == COND_IF)
		return (PROMPT_IF);
	else if (env->cond->type == COND_WHILE)
		return (PROMPT_WHILE);
	else if (env->cond->type == COND_FOR)
		return (PROMPT_FOR);
	else
		return (PROMPT_COND);
}

void	bsquote(char **input)
{
	int		i;
	int		u;
	char	*tmp;

	u = 0;
	i = -1;
	while ((*input)[++i])
	{
		if (bs_str(*input, i, '\''))
			u = (u == 1 ? 0 : 1);
		if ((bs_str(*input, i, '(') || bs_str(*input, i, ')') ||
			bs_str(*input, i, '!') || bs_str(*input, i, '$') ||
			bs_str(*input, i, '~')) && u == 1)
		{
			tmp = ft_strnew(ft_strlen(*input));
			ft_strncat(tmp, *input, i);
			ft_strcat(tmp, "\\");
			ft_strcat(tmp, *input + i);
			free(*input);
			*input = tmp;
			++i;
		}
	}
}

int		ft_read(t_env *env, char *input, int i, int u)
{
	char	**inputspl;
	char	*tmp;

	env->bool1 = 0;
	env->bool2 = 0;
	if (input == NULL)
		input = termcaps(ft_sprintf("\e[1;32m%C\e[0;m \e[1;36m%s \e[0m%s", L'✈',
		env->dir, hijack_prompt(env)), 10, 0);
	if (ft_read2(u, &input, env) == 0)
		return (0);
	inputspl = ft_strsplitquote(input, ';', 0);
	free(input);
	while (inputspl && inputspl[++i])
	{
		env->input = ft_strdup(inputspl[i]);
		if (ft_strchr(env->input, '~'))
			ft_tilde(&env->input, -1, 0);
		bs_eol(env);
		tmp = ft_strdup(env->input);
		if (env->cond == NULL)
			parse(env, &tmp);
		else
			handle_condition(env, ft_split_input(env->input));
		free(tmp);
		free(env->input);
		env->input = NULL;
	}
	return (free_double_array(inputspl));
}
