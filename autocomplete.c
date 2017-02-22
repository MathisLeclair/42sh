/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 15:01:14 by aridolfi          #+#    #+#             */
/*   Updated: 2017/02/22 17:45:30 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		strstr_no_case(char *find, char *search_in_lc)
{
	int			i;
	int			j;
	long int	f_len;

	if ((f_len = ft_strlen(find)) == 0)
		return (1);
	i = 0;
	while (search_in_lc[i])
		if (search_in_lc[i] == find[0])
		{
			j = -1;
			while (search_in_lc[i] && search_in_lc[i] == find[++j])
				++i;
			if (f_len == j)
				return (1);
		}
		else
			++i;
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
	char	**new_dtr;

	i = 0;
	while ((*dstr)[i])
		++i;
	new_dtr = palloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((*dstr)[i])
	{
		new_dtr[i] = (*dstr)[i];
		++i;
	}
	new_dtr[i] = ft_strdup(str);
	new_dtr[i + 1] = 0;
	free(*dstr);
	*dstr = new_dtr;
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

	i = -1;
	while (split_path[++i])
		if ((dir = opendir(split_path[i])))
		{
			while ((dirent = readdir(dir)))
				if (strstr_no_case(find, to_lowercase(dirent->d_name)))
					add_str_to_dstr(ac, dirent->d_name);
			closedir(dir);
		}
}

char    **ac_cmd(char *find, t_env *env)
{
	char		**ac;
	char		**split_path;
	int			i;

	ac = palloc(sizeof(char *));
	ac[0] = NULL;
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

char    **ac_pwd(char *find, int count, char *str)
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
			new = palloc(sizeof(char *) * (count + 1));
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

void	ac_target2(char *after_path, t_dirent *dirent, char *find, char ***ac)
{
	int		i;
	int		len;
	char	**new;

	len = 0;
	while ((*ac)[len])
		++len;
	if (strstr_no_case(after_path, to_lowercase(dirent->d_name)) && dirent->d_name[0] != '.')
	{
		new = palloc(sizeof(char *) * (len + 2));
		i = -1;
		while ((*ac)[++i])
			new[i] = (*ac)[i];
		new[i] = malloc(ft_strlen(find) + ft_strlen(dirent->d_name) + 1);
		new[i][0] = 0;
		ft_strcat(new[i], find);
		ft_strcat(new[i], dirent->d_name);
		new[i + 1] = 0;
		free(*ac);
		(*ac) = new;
	}
}

void	ac_target(char *find, char ***ac)
{
	char		*after_path;
	int			i;
	int			j;
	DIR			*dir;
	t_dirent	*dirent;

	*ac = palloc(sizeof(char *) * 2);
	(*ac)[0] = 0;
	(*ac)[1] = 0;
	i = ft_strlen(find);
	while (find[i] != '/')
		--i;
	after_path = malloc(ft_strlen(find) - i);
	j = -1;
	while (find[++i])
		after_path[++j] = find[i];
	after_path[j + 1] = 0;
	find[i - j + 2] = 0;
	if ((dir = opendir(find)))
		while ((dirent = readdir(dir)))
			ac_target2(after_path, dirent, find, ac);
	if (dir)
		closedir(dir);
}

int		ft_len_arrow(char **t)
{
	int i;

	i = 0;
	while (t[i])
		++i;
	return (i);
}
char    **auto_possibilities(char pwd, t_env *env)
{
	char	**ac;
	char	*find_lwc;
	char	*save;

	find_lwc = env->input;
	env->input = env->find;
	ft_dollar(env, -1, 0);
	env->find = env->input;
	env->input = find_lwc;
	save = ft_strdup(env->find);
	if (env->find[0] == '/')
	{
		ac_target(save, &ac);
		if (ft_len_arrow(ac) == 0 && opendir(ft_strcat(env->find, "/")))
			ac[0] = ft_strdup(env->find);
		return (ac);
	}
	free(save);
	find_lwc = to_lowercase(env->find);
	if (pwd == 0)
		ac = ac_cmd(find_lwc, env);
	else
		ac = ac_pwd(find_lwc, 0, palloc(INPUT_SIZE));
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
	find = malloc(j + 2);
	find[j] = 0;
	find[j + 1] = 0;
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
		if (input[pos - 1] != ' ' && env->find[0] != '/')
			startfind(ac, env, 1);
	}
	else
	{
		if (first)
			ac = auto_possibilities(0, env);
		else
			ac = auto_possibilities(1, env);
		if (env->find[0] != '/')
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
