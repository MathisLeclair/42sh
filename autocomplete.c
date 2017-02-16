/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 15:01:14 by aridolfi          #+#    #+#             */
/*   Updated: 2017/02/16 19:44:01 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		strstr_no_case(char *find, char *search_in_lc)
{
	int			i;
	int			j;
	size_t	f_len;

	if ((f_len = ft_strlen(find)) == 0)
		return (1);
	i = 0;
	while (search_in_lc[i])
	{
		if (search_in_lc[i] == find[0])
		{
			j = -1;
			while (search_in_lc[i] && search_in_lc[i] == find[++j])
				++i;
			if (j == f_len)
			{
				free(search_in_lc);
				return (1);
			}
		}
		else
			++i;
	}
	free(search_in_lc);
	return (0);
}

char	*to_lowercase(char *str)
{
	int		i;
	char	*str_lc;

	str_lc = ft_strdup(str);
	i = -1;
	while (str_lc[++i])
		if (str_lc[i] >= 'A' && str_lc[i] <= 'Z')
			str_lc[i] = str_lc[i] - 'A' + 'a';
	return (str_lc);
}

void	add_str_to_dstr(char ***dstr, char *str)
{
	int		i;
	char	**new_dstr;

	i = 0;
	while (dstr[i])
		++i;
	new_dstr = palloc(sizeof(char *) * i + 2);
	new_dstr[i + 1] = 0;
	i = -1;
	while (dstr[++i])
		new_dstr[i] = (*dstr)[i];
	new_dstr[i] = ft_strdup(str);
	free(dstr);
	*dstr = new_dstr;
}

void	ft_ac_cmd_build(char ***ac, char *find)
{
	if (strstr_no_case(find, "echo"))
		add_str_to_dstr(ac, "echo");
	if (strstr_no_case(find, "cd"))
		add_str_to_dstr(ac, "cd");
	if (strstr_no_case(find, "aperture"))
		add_str_to_dstr(ac, "aperture");
	if (strstr_no_case(find, "unsetenv"))
		add_str_to_dstr(ac, "unsetenv");
	if (strstr_no_case(find, "setenv"))
		add_str_to_dstr(ac, "setenv");
	if (strstr_no_case(find, "exit"))
		add_str_to_dstr(ac, "exit");
	if (strstr_no_case(find, "Patate"))
		add_str_to_dstr(ac, "Patate");
	if (strstr_no_case(find, "env"))
		add_str_to_dstr(ac, "env");
	if (strstr_no_case(find, "local"))
		add_str_to_dstr(ac, "local");
	if (strstr_no_case(find, "unset"))
		add_str_to_dstr(ac, "unset");
	if (strstr_no_case(find, "export"))
		add_str_to_dstr(ac, "export");
	if (strstr_no_case(find, "set"))
		add_str_to_dstr(ac, "set");
}

void	ft_ac_cmd_path(char **split_path, char *find, char ***ac)
{
	DIR			*dir;
	t_dirent	*dirent;
	int			i;

	*ac = palloc(sizeof(char *));
	**ac = 0;
	i = -1;
	while (split_path[++i])
	{
		if ((dir = opendir(split_path[i])))
		{
			while ((dirent = readdir(dir)))
				if (strstr_no_case(find, to_lowercase(dirent->d_name)))
					add_str_to_dstr(ac, dirent->d_name);
			closedir(dir);
		}
	}
}

char    **ac_cmd(char *find, t_env *env)
{
	char		**ac;
	char		**split_path;
	int			i;

	split_path = NULL;
	if ((i = find_param(env->ev, "PATH")) == -1)
	{
		if ((i = find_param(env->loc->ev, "PATH")) != -1)
			split_path = ft_strsplitquote(env->loc->ev[i], ':', 0);
	}
	else
		split_path = ft_strsplitquote(env->ev[i], ':', 0);
	if (split_path)
		ft_ac_cmd_path(split_path, find, &ac);
	ft_ac_cmd_build(&ac, find);
	return (ac);
}

char    **ac_pwd(char *find, t_env *env, int count, char *str)
{
	DIR			*dir;
	t_dirent	*dirent;
	char		**sug;
	char		**new;
	int			i;

	sug = palloc(sizeof(char *));
	sug[0] = 0;
	getcwd(str, INPUT_SIZE);
	dir = opendir(str);
	while ((dirent = readdir(dir)))
		if (strstr_no_case(find, to_lowercase(dirent->d_name)) && dirent->d_name[0] != '.')
		{
			++count;
			new = palloc(sizeof(char *) * count + 1);
			i = -1;
			while (sug[++i])
				new[i] = sug[i];
			new[i] = ft_strdup(dirent->d_name);
			new[i + 1] = 0;
			free(sug);
			sug = new;
		}
	closedir(dir);
	free(str);
	return (sug);
}

char    **auto_possibilities(char pwd, t_env *env)
{
	char	**ac;
	char	*find_lwc;
	int		i;

	find_lwc = env->input;
	env->input = env->find;
	ft_dollar(env, -1, 0);
	env->find = env->input;
	env->input = find_lwc;
	find_lwc = to_lowercase(env->find);
	ac = ft_strsplitquote(find_lwc, '/', 1);
	if (ac[0])
	{
		i = 0;
		while (ac[i])
			++i;
		find_lwc = ac[i - 1];
	}
	if (pwd == 0)
		ac = ac_cmd(find_lwc, env);
	else
		ac = ac_pwd(find_lwc, env, 0, palloc(INPUT_SIZE));
	return (ac);
}

char	*finder(char *input, int pos)
{
	char	*find;
	int		i;
	int		j;

	while (pos != 0 && input[pos] != ' ' && input[pos] != '\t')
		pos--;
	i = pos == 0 ? 0 : pos + 1;
	j = 0;
	while (input[i] && input[i++] != ' ')
		++j;
	find = malloc(j + 1);
	find[j] = 0;
	i = 0;
	pos = pos == 0 ? pos - 1 : pos;
	while (input[++pos] && input[pos] != ' ')
		find[i++] = input[pos];
	return(find);
}

char	ft_strcmp_beg(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		++i;
	if (str1[i] && str2[i])
		return (0);
	return (1);
}

void	startfind(char **ac, t_env *env, char boolean)
{
	int		i;
	int		j;

	i = 0;
	if (boolean)
	{
		while (ac[i])
		{
			if (!ft_strcmp_beg(ac[i], env->find))
			{
				free(ac[i]);
				j = i;
				while (ac[j++])
					ac[j - 1] = ac[j];
			}
			else
				++i;
		}
	}
	else
		while (ac[i])
		{
			if (ft_strcmp_beg(ac[i], env->find))
			{
				free(ac[i]);
				j = i;
				while (ac[j++])
					ac[j - 1] = ac[j];
			}
			else
				++i;
		}
}

char	**forest(char *input, int pos, t_env *env, char first)
{
	char	**ac;

	if (input[pos] == ' ' || input[pos] == '\0' || input[pos + 1] == ' ' || input[pos + 1] == '\0')
	{
		if (first)
			ac = auto_possibilities(0, env);
		else
			ac = auto_possibilities(1, env);
		if (input[pos - 1] != ' ')
			startfind(ac, env, 1);
	}
	else
	{
		if (first)
			ac = auto_possibilities(0, env);
		else
			ac = auto_possibilities(1, env);
		startfind(ac, env, 0);
	}
	return (ac);
}

char	**autocomplete(char *input, int pos, t_env *env)
{
	char	first;
	int		i;
	char	**ac;
	char	quote;

	quote = 0;
	i = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		++i;
	if (i > pos || input[i] == '\0')
		return (NULL);
	while (input[i] && (input[i] != ' ' || quote != 0))
	{
		if (input[i] == '\'' || input[i] == '"')
			quote = input[i] == quote ? 0 : quote;
		++i;
	}
	first = pos > i ? 0 : 1;
	env->find = finder(input, input[pos] == ' ' ? pos - 1 : pos);
	ac = forest(input, pos, env, first);
	free(env->find);
	env->find = NULL;
	return (ac);
}
