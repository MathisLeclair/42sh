/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 13:28:38 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/10 14:35:14 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	ft_suppr_quotes(char *str, int i, int j)
{
	char	quote;

	while (str[i] && (quote = str[i]))
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			while (str[++i] && str[i] != quote)
				str[j++] = str[i];
			if (str[i] && str[i + 1])
				++i;
			else
				break ;
		}
		if (str[i] != '\'' && str[i] != '\"')
		{
			str[j] = str[i];
			++i;
			++j;
		}
	}
	str[j] = 0;
}

char	**ft_split_input(char *input)
{
	int		i;
	char	**a;

	i = -1;
	a = ft_strsplitquote(input, ' ', 1);
	i = -1;
	while (a[++i])
		ft_suppr_quotes(a[i], 0, 0);
	return (a);
}

int		ft_reco_cmd3(t_env *env, char **split)
{
	int i;

	i = -1;
	if (ft_strcmp(split[0], "unset") == 0)
	{
		if (split[1][0] == '-' && split[1][1] == 'v')
			++i;
		while (split[++i])
			suppr_var_env(env->loc, split[i]);
	}
	else if (ft_strcmp(split[0], "export") == 0)
		builtin_export(env, split);
	else if (ft_strcmp(split[0], "job") == 0)
		builtin_jobs(env, split);
	else if (ft_strcmp(split[0], "fg") == 0)
		builtin_fg(env, split, 0);
	else if (ft_strcmp(split[0], "bg") == 0)
		builtin_bg(env, split);
	else
		ft_fork(env, split);
	if (split)
		free_double_array(split);
	return (save_env(env));
}

int		ft_reco_cmd2(t_env *env, char **split)
{
	if (ft_strcmp(split[0], "Patate") == 0)
	{
		ft_printf("[1]    %s segmentation fault  ./42sh\n",
			env->loc->ev[find_param(env->loc->ev, "UID")] + 4);
		exit(0);
	}
	else if (ft_strcmp(split[0], "exit") == 0)
	{
		free_double_array(split);
		ft_exit();
	}
	else if (ft_strcmp(split[0], "env") == 0)
		reco_env(env, split, 0, 0);
	else if (ft_strcmp(split[0], "history") == 0)
		history(env, split);
	else if (ft_strcmp(split[0], "read") == 0)
		builtin_read(env, split);
	else if (ft_strcmp(split[0], "local") == 0)
		print_split(env->loc->ev);
	else
		return (ft_reco_cmd3(env, split));
	if (split)
		free_double_array(split);
	return (save_env(env));
}

int		ft_reco_cmd(t_env *env)
{
	char	**split;
	int		i;
	char	*reg;

	reg = 0;
	if (*env->input == '\n')
		return (1);
	split = ft_split_input(env->input);
	if (!(i = 0) && ft_strcmp(split[0], "cd") == 0)
		ft_cd(split, env, reg, ft_strnew(INPUT_SIZE + 4));
	else if (ft_strcmp(split[0], "echo") == 0)
		ft_echo(split);
	else if (ft_strcmp(split[0], "setenv") == 0)
		while (split[++i])
			add_var_to_env(env, split[i]);
	else if (ft_strcmp(split[0], "unsetenv") == 0)
		while (split[++i])
			suppr_var_env(env, split[i]);
	else if (ft_strcmp(split[0], "aperture") == 0)
		ft_aperture();
	else
		return (ft_reco_cmd2(env, split));
	if (split)
		free_double_array(split);
	return (save_env(env));
}

void	extracredir(t_env *env)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	while (env->input[++i])
	{
		j = i;
		if (env->input[j++] == '>')
		{
			if (env->input[j] == '>')
				++j;
			while (env->input[j] && env->input[j] == ' ')
				++j;
			while (env->input[j] && ((env->input[j] >= 33 && env->input[j] <= 126) || (env->input[j] == ' ' && j > 0 && env->input[j - 1] == '\\')))
				++j;
			temp = ft_strcdup(env->input + i, j - i);
			add_str_to_dstr(&env->redir, temp);
			free(temp);
			ft_remstr(env->input, i, j);
			i = j;
		}
	}
}

int		cmprev(char *str, char *tofind)
{
	int i;
	int k;

	i = ft_strlen(str);
	while (str[--i])
	{
		k = ft_strlen(tofind);
		while (k - 1 >= 0 && i >= 0 && str[i] == tofind[k - 1])
		{
			--k;
			--i;
		}
		if (k == 0 && ft_strchr(tofind, str[i]) == 0)
		{
			env()->inp1 = ft_strcdup(str, i + 1);
			env()->inp2 = ft_strdup(str + ft_strlen(tofind) + i + 1);
			return (i);
		}
	}
	return (-1);
}

void	extract_rd_output(t_env *env, char *input)
{
	int i;
	int j;
	int u;

	i = 0;
	while (input[i] && input[i] != '<')
		++i;
	j = i + 1;
	while (input[j] == ' ' || input[j] == '\t')
		++j;
	u = j;
	while (ft_isascii(input[j]) && (input[j] != ' ' ||
		(input[j] == ' ' && input[j - 1] == '\\')))
		++j;
	free(env->inp2);
	env->inp2 = ft_strcdup(input + u, j - i);
	env->inp2[j - i] = 0;
	ft_remstr(input, i, j);
	free(env->inp1);
	env->inp1 = ft_strdup(input);
	env->inp1[ft_strlen(input)] = 0;
}

void	extract_heredoc(t_env *env, char *input)
{
	int i;
	int j;

	i = 0;
	while (input[i] && input[i] != '<')
		++i;
	j = i + 2;
	while (input[j] == ' ' || input[j] == '\t')
		++j;
	while (ft_isalpha(input[j]))
		++j;
	free(env->inp2);
	env->inp2 = ft_strcdup(input + i, j);
	ft_remstr(input, i, j);
	free(env->inp1);
	env->inp1 = ft_strdup(input);
}

void	handle_weirde(t_env *e)
{
	int i;

	i = -1;
	while (e->input[++i])
	{
		if (e->input[i] == '&' && i > 1 && e->input[i - 1] != '<' &&
			e->input[i - 1] != '>' && e->input[i + 1] != '&'
			&& e->input[i - 1] != '&')
		{
			e->boolweride = 1;
			e->input[i] = ' ';
		}
	}
}

void	parse(t_env *env, char *input)
{
	int i;

	i = -1;
	free(env->input);
	env->input = ft_strdup(input);
	handle_weirde(env);
	while (ft_strchr(env->input, '`') != 0)
		bquote(env);
	if (ft_strchr(env->input, '$'))
		ft_dollar(env, -1, 0);
	if (cmprev(input, "&&") != -1)
		oprt_and(env);
	else if (cmprev(input, "||") != -1)
		oprt_or(env);
	else if (cmprev(input, "|") != -1)
		rd_pipe(env);
	else if (cmprev(input, "<") != -1)
	{
		extract_rd_output(env, input);
		rd_input(env);
	}
	else if (cmprev(input, "<<") != -1)
	{
		extract_heredoc(env, input);
		rd_here_doc(env);
	}
	else if (cmprev(input, ">") != -1 || cmprev(input, ">>") != -1)
	{
		extracredir(env);
		while (env->redir[++i])
		{
			if (env->redir[i][0] == '>' && env->redir[i][1] == '>')
				rd_output_apd(env, i);
			else if (env->redir[i][0] == '>' && env->redir[i][1] != '>')
				rd_output(env, i);
		}
		free_double_array(env->redir);
		env->redir = malloc(sizeof(char *));
		env->redir[0] = NULL;
	}
	else
		ft_reco_cmd(env);
	if (env->inp1)
	{
		free(env->inp1);
		env->inp1 = 0;
	}
	if (env->inp2)
	{
		free(env->inp2);
		env->inp2 = 0;
	}
}

int		ft_read(t_env *env, char *input)
{
	char	**inputspl;
	int		i;

	if (input == NULL)
		input = termcaps(ft_sprintf("\e[1;32m%C\e[0;m \e[1;36m%s \e[0m%s", L'✈',
		env->dir, PROMPT));
	if (verif_quote(input, 0) == -1)
		return (0);
	if (ft_strchr(input, '(') != 0 || ft_strchr(input, ')') != 0)
		if (subshell(env, input) == -1)
			return (-1);
	inputspl = ft_strsplitquote(input, ';', 0);
	free(input);
	i = -1;
	while (inputspl && inputspl[++i])
	{
		env->input = ft_strdup(inputspl[i]);
		if (ft_strchr(env->input, '~'))
			ft_tilde(env, -1, 0);
		parse(env, inputspl[i]);
		env->input = NULL;
	}
	free_double_array(inputspl);
	return (0);
}
