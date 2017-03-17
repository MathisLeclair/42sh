/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 13:28:38 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/17 17:21:46 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	ft_suppr_quotes(char **str, int i, int j)
{
	char	quote;
	char	*tmp;

	tmp = ft_strdup(*str);
	while ((*str)[i])
	{
		if (bs_str(*str, i, '\'') || bs_str(*str, i, '\"'))
		{
			quote = (*str)[i];
			while ((*str)[++i] && !bs_str(*str, i, quote))
				tmp[j++] = (*str)[i];
			if ((*str)[i])
				++i;
		}
		else
		{
			tmp[j] = (*str)[i];
			++i;
			++j;
		}
	}
	tmp[j] = 0;
	free(*str);
	*str = tmp;
}

void	ft_suppr_bs(char **str)
{
	int		i;
	int		j;
	char	*new;

	i = -1;
	j = 0;
	while ((*str)[++i])
		if ((*str)[i] == '\\' && (*str)[i + 1])
		{
			j++;
			i++;
		}
	new = palloc(ft_strlen(*str) - j + 1);
	i = 0;
	j = -1;
	while ((*str)[i])
	{
		if ((*str)[i] == '\\' && (*str)[i + 1])
			++i;
		new[++j] = (*str)[i];
		++i;
	}
	new[++j] = 0;
	free(*str);
	*str = new;
}

char	**ft_split_input(char *input)
{
	int		i;
	char	**a;

	i = -1;
	a = ft_strsplitquote(input, ' ', 1);
	i = -1;
	while (a[++i])
	{
		ft_suppr_quotes(a + i, 0, 0);
		ft_suppr_bs(a + i);
	}
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
	else if (ft_strcmp(split[0], "hash") == 0)
		builtin_hash(env, split);
	else if (ft_strfind(split[0], '=') != -1)
		add_local(env, split);
	else
	{
		gthash(isbin(split[0]));
		ft_fork(env, split);
	}
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
		ft_exit(split);
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

int		ft_reco_cmd(t_env *env, int i)
{
	char	**split;

	if (*env->input == '\n')
		return (1);
	split = ft_split_input(env->input);
	if (split[0] == NULL)
	{
		retvalue_into_loc(env, 1);
		return (0);
	}
	if (ft_strcmp(split[0], "cd") == 0)
		ft_cd(split, env, NULL, ft_strnew(INPUT_SIZE + 4));
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

void	extracredir(t_env *e, int i, int j)
{
	char	*temp;

	i = ft_strlen(e->input);
	while (e->input[--i] && i >= 0)
	{
		j = i;
		if (e->input[j] == '>')
		{
			if (j - 1 >= 0 && --j && e->input[j] == '>')
				--i;
			j += 2;
			if (i - 1 >= 0 && ft_isdigit(e->input[i - 1]) && i - 2 >= 0
				&& e->input[i - 2] == ' ')
				i--;
			while (e->input[j] && e->input[j] == ' ')
				++j;
			while (e->input[j] && ((e->input[j] >= 33 && e->input[j] <= 126)
				|| (e->input[j] == ' ' && j > 0 && e->input[j - 1] == '\\')))
				++j;
			temp = ft_strcdup(e->input + i, j - i);
			e->redir = temp;
			ft_remstr(e->input, i, j);
			return ;
		}
	}
}

int		isinquote(char *input, int i)
{
	int u;

	u = 0;
	while (input[i])
	{
		--i;
		if ((input[i] == '"' || input[i] == '\'') &&
			((i > 1 && input[i - 1] != '\\') || i < 1))
			u = -1;
	}
	return (u);
}

int		cmprevtruc(t_env *env, char **input)
{
	int i;

	i = ft_strlen(*input);
	if (i <= 2)
		return (0);
	while ((*input)[--i])
	{
		if (((*input)[i] == '&' && (*input)[i - 1] == '&') ||
			((*input)[i] == '|' && (*input)[i - 1] == '|'))
		{
			env->inp1 = ft_strcdup((*input), i - 1);
			env->inp2 = ft_strdup((*input) + i + 1);
			if ((*input)[i] == '&')
			{
				oprt_and(env);
				return (1);
			}
			else
			{
				oprt_or(env);
				return (1);
			}
		}
	}
	return (0);
}

int		cmprev(char *str, char *tofind)
{
	int i;
	int k;

	i = ft_strlen(str);
	if (i < (int)ft_strlen(tofind))
		return (-1);
	while (str[--i])
	{
		k = ft_strlen(tofind);
		while (k - 1 >= 0 && i >= 0 && bs_str(str, i, tofind[k - 1])
			&& isinquote(str, i) == 0)
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
	while (input[j] && ft_isascii(input[j]) && (input[j] != ' ' ||
		(input[j] == ' ' && input[j - 1] == '\\')))
		++j;
	free(env->inp2);
	env->inp2 = ft_strcdup(input + u, j - i);
	env->inp2[j - i] = 0;
	ft_remstr(input, i, j);
	free(env->inp1);
	env->inp1 = ft_strdup(input);
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

int		parserror(t_env *env)
{
	int i;

	i = 0;
	if (strstr_bool("&&&", ft_strdup(env->input)) == 1)
		i = -1;
	if (strstr_bool("|||", ft_strdup(env->input)) == 1)
		i = -1;
	if (strstr_bool("|&|", ft_strdup(env->input)) == 1)
		i = -1;
	if (strstr_bool("&|&", ft_strdup(env->input)) == 1)
		i = -1;
	if (i == -1)
		error(-15, NULL, NULL);
	return (i);
}

void	parse(t_env *env, char *input)
{
	int i;

	i = -1;
	free(env->input);
	env->input = ft_strdup(input);
	while (ft_strchr(env->input, '`') != 0)
		bquote(env);
	if (env->input == NULL)
		return ;
	if (ft_strchr(env->input, '$'))
		ft_dollar(env, -1, 0);
	if (parserror(env) == -1)
		return ;
	if (ft_strfind(input, '(') != -1 || ft_strfind(input, ')') != -1)
		if (subshell(env, input) == -1)
			return ;
	if (cmprevtruc(env, &input))
		;
	else if (cmprev(input, "|") != -1)
		rd_pipe(env);
	else if (cmprev(input, "<<<") != -1)
		rd_here_string(env, -1, -1, -1);
	else if (cmprev(input, "<") != -1)
	{
		extract_rd_output(env, input);
		rd_input(env);
	}
	else if (cmprev(input, "<<") != -1)
	{
		extract_heredoc(env, input);
		rd_here_doc(env, -1, -1);
	}
	else if (cmprev(input, ">") != -1 || cmprev(input, ">>") != -1)
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
	else
		ft_reco_cmd(env, 0);
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
	char	*tmp;

	if (input == NULL)
		input = termcaps(ft_sprintf("\e[1;32m%C\e[0;m \e[1;36m%s \e[0m%s", L'✈',
		env->dir, PROMPT));
	while (verif_quote(&input, -1, 0) != 0)
		;
	inputspl = ft_strsplitquote(input, ';', 0);
	free(input);
	i = -1;
	while (inputspl && inputspl[++i])
	{
		env->input = ft_strdup(inputspl[i]);
		if (ft_strchr(env->input, '~'))
			ft_tilde(&env->input, -1, 0);
		parse(env, tmp = ft_strdup(env->input));
		free(tmp);
		free(env->input);
		env->input = NULL;
	}
	free_double_array(inputspl);
	return (0);
}
