/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 16:12:06 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/23 15:59:18 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

void	ft_ac_cmd_path(char **split_path, char *find, char ***ac)
{
	DIR			*dir;
	t_dirent	*dirent;
	int			i;
	char		*str;

	i = -1;
	while (split_path[++i])
		if ((dir = opendir(split_path[i])))
		{
			while ((dirent = readdir(dir)))
			{
				str = add_bs(ft_strdup(dirent->d_name));
				if (strstr_bool(find, to_lwcase(str), 0))
					add_str_to_dstr(ac, str);
				free(str);
			}
			closedir(dir);
		}
}

char	**ac_cmd(char *find, t_env *env)
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
	free_double_array(split_path);
	ft_ac_cmd_build(&ac, find);
	return (ac);
}

char	**ac_pwd(char *find, char *str)
{
	DIR			*dir;
	t_dirent	*td;
	char		**sug;
	char		*tmp;
	int			i;

	sug = palloc(sizeof(char *));
	*sug = 0;
	i = ft_strlen(find);
	while (i > 0 && !bs_str(find, i - 1, '/'))
		--i;
	getcwd(str, INPUT_SIZE);
	ft_strncat(ft_strcat(str, "/"), find, i);
	dir = opendir(str);
	while ((td = readdir(dir)))
		if (strstr_bool(find + i, add_bs(to_lwcase(td->d_name)), 0)
			&& td->d_name[0] != '.')
		{
			tmp = palloc(INPUT_SIZE);
			*tmp = 0;
			tmp = add_bs(ft_strcat(ft_strncat(tmp, find, i), td->d_name));
			add_str_to_dstr(&sug, tmp);
			free(tmp);
		}
	closedir(dir);
	free(str);
	return (sug);
}

void	ac_target2(char *after_path, t_dirent *td, char *find, char ***ac)
{
	int		i;
	int		len;
	char	**new;
	char	*tmp;

	len = 0;
	while ((*ac)[len])
		++len;
	find = add_bs(ft_strdup(find));
	tmp = add_bs(ft_strdup(td->d_name));
	if (strstr_bool(after_path, to_lwcase(tmp), 0) && td->d_name[0] != '.')
	{
		new = palloc(sizeof(char *) * (len + 2));
		i = -1;
		while ((*ac)[++i])
			new[i] = (*ac)[i];
		new[i] = malloc(ft_strlen(find) + ft_strlen(tmp) + 1);
		new[i][0] = 0;
		ft_strcat(new[i], find);
		ft_strcat(new[i], tmp);
		new[i + 1] = 0;
		free(*ac);
		*ac = new;
	}
	free(find);
	free(tmp);
	free(after_path);
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
	while (!bs_str(find, i, '/'))
		--i;
	after_path = palloc(ft_strlen(find) - i);
	j = -1;
	while (find[++i])
		after_path[++j] = find[i];
	after_path[j + 1] = 0;
	find[i - j - 1] = 0;
	if ((dir = opendir(find)))
		while ((dirent = readdir(dir)))
			ac_target2(to_lwcase(after_path), dirent, find, ac);
	free(after_path);
	if (dir)
		closedir(dir);
}
