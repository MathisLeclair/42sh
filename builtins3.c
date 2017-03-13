/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 15:47:09 by bfrochot          #+#    #+#             */
/*   Updated: 2017/03/13 15:12:18 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

char	*isbin(char *str)
{
	int			i;
	char		**split_path;
	DIR			*dir;
	t_dirent	*dirent;

	split_path = NULL;
	if ((i = find_param(env()->ev, "PATH")) == -1)
	{
		if ((i = find_param(env()->loc->ev, "PATH")) != -1)
			split_path = ft_strsplitquote(env()->loc->ev[i], ':', 0);
	}
	else
		split_path = ft_strsplitquote(env()->ev[i], ':', 0);
	i = -1;
	while (split_path && split_path[++i])
		if ((dir = opendir(split_path[i])))
		{
			while ((dirent = readdir(dir)))
				if (ft_strcmp(dirent->d_name, str) == 0)
				{
					str = ft_strjoin(split_path[i], "/");
					str = ft_strjoinfree(str, dirent->d_name, 1);
					closedir(dir);
					free_double_array(split_path);
					return (str);
				}
			closedir(dir);
		}
	free_double_array(split_path);
	return (NULL);
}

void	gthash(char *str)
{
	int i;
	int j;
	int k;

	if (!env()->hash)
	{
		env()->hash = malloc(sizeof(char *) * 2);
		env()->hash[1] = 0;
		env()->hash[0] = ft_strdup("hits\tcommand");
	}
	i = 0;
	while (env()->hash[++i])
		if (ft_strcmp(str, env()->hash[i] + 5) == 0)
		{
			free(str);
			str = ft_itoa(ft_atoi(env()->hash[i]) + 1);
			j = 3 - ft_strlen(str);
			k = -1;
			while (env()->hash[i][++j] && ++k + 1 && j != 4)
				env()->hash[i][j] = str[k];
			break ;
		}
	if (!env()->hash[i] && str)
		add_str_to_dstr(&env()->hash, (str = ft_strjoinfree("   1\t", str, 2)));
	free(str);
}

void	go_away(char *str)
{
	int i;

	i = 0;
	while (env()->hash[++i])
		if (ft_strcmp(str, env()->hash[i] + 8))
		{
			env()->hash[i][0] = ' ';
			env()->hash[i][1] = ' ';
			env()->hash[i][2] = ' ';
			env()->hash[i][3] = '0';
			return ;
		}
	ft_printf("hash: no such command: %s\n", str);
}

void	builtin_hash(t_env *env, char **split)
{
	int i;

	if (!env->hash)
	{
		ft_printf("hash: no command\n");
		return ;
	}
	i = -1;
	if (split[1] == 0)
		while (env->hash && env->hash[++i])
			ft_printf("%s\n", env->hash[i]);
	else
		while (split[++i])
			if (i == 0)
				continue ;
			else
				go_away(split[i]);
}
