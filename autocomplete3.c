/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 16:12:06 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/25 14:03:20 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

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

void	ac_pwd2(char ***sug, t_dirent *td, int i, char *find)
{
	char		*tmp;

	tmp = palloc(INPUT_SIZE);
	*tmp = 0;
	tmp = add_bs(ft_strcat(ft_strncat(tmp, find, i), td->d_name));
	add_str_to_dstr(sug, tmp);
	free(tmp);
}

char	**ac_pwd(char *find, char *str)
{
	DIR			*dir;
	t_dirent	*td;
	char		**sug;
	int			i;

	sug = palloc(sizeof(char *));
	*sug = 0;
	i = ft_strlen(find);
	while (i > 0 && !bs_str(find, i - 1, '/'))
		--i;
	getcwd(str, INPUT_SIZE);
	ft_strncat(ft_strcat(str, "/"), find, i);
	if (!(dir = opendir(str)))
		return (sug);
	while ((td = readdir(dir)))
	{
		if (strstr_bool(find + i, add_bs(to_lwcase(td->d_name)), 0)
			&& (td->d_name[0] != '.' || bs_str(find, ft_strlen(find) - 1, '.'))
			&& ft_strcmp(td->d_name, ".."))
			ac_pwd2(&sug, td, i, find);
	}
	closedir(dir);
	free(str);
	return (sug);
}

void	ac_target2(char *after_path, t_dirent *td, char *find, char ***ac)
{
	int		i[2];
	char	**new;
	char	*tmp;

	i[1] = 0;
	while ((*ac)[i[1]])
		++i[1];
	find = add_bs(ft_strdup(find));
	tmp = add_bs(ft_strdup(td->d_name));
	if (strstr_bool(after_path, to_lwcase(tmp), 0) && td->d_name[0] != '.')
	{
		new = palloc(sizeof(char *) * (i[1] + 2));
		i[0] = -1;
		while ((*ac)[++i[0]])
			new[i[0]] = (*ac)[i[0]];
		new[i[0]] = malloc(ft_strlen(find) + ft_strlen(tmp) + 1);
		new[i[0]][0] = 0;
		ft_strcat(new[i[0]], find);
		ft_strcat(new[i[0]], tmp);
		new[i[0] + 1] = 0;
		free(*ac);
		*ac = new;
	}
	free2(find, tmp);
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
	after_path = add_bs(after_path);
	find[i - j - 1] = 0;
	if ((dir = opendir(find)))
		while ((dirent = readdir(dir)))
			ac_target2(to_lwcase(after_path), dirent, find, ac);
	free(after_path);
	if (dir)
		closedir(dir);
}
