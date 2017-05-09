/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 16:40:58 by bfrochot          #+#    #+#             */
/*   Updated: 2017/05/09 18:30:23 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

void	ft_exit(char **split)
{
	int i;

	i = -1;
	if (split[1] && ft_isdigit(split[1][0]) && !split[2])
		i = ft_atoi(split[1]);
	else if ((split[1] && !ft_isdigit(split[1][0])) ||
		(split[1] && split[2]) || !split[0])
		error(-14, NULL, NULL);
	i = (i != -1 ? i : env()->lastret);
	free_double_array(split);
	ft_putstr("exit\n");
	file_history(0, 0, 0, 0);
	env_free(env());
	exit(i);
}

int		ft_cd_l3(char *pwd, char *oldpwd, struct stat *stats)
{
	error(-1, NULL, pwd);
	free2(pwd, oldpwd);
	free(stats);
	return (1);
}

int		ft_cd_l(t_env *e, char *oldpwd, char **split, size_t i)
{
	struct stat *stats;
	char		*pwd;

	stats = malloc(sizeof(struct stat));
	pwd = ft_strjoin("PWD=", e->ev[find_param(e->ev, "PWD")] + 4);
	pwd = ft_strjoinfree(pwd, "/", 1);
	pwd = ft_strjoinfree(pwd, split[2], 1);
	lstat(pwd + 4, stats);
	if (!S_ISLNK(stats->st_mode))
		return (ft_cd_l2(split, pwd, stats, oldpwd));
	if (chdir(pwd + 4) == -1)
		return (ft_cd_l3(pwd, oldpwd, stats));
	add_var_to_env(e, pwd);
	i = ft_strlen(pwd);
	while (pwd[i] != '/' && pwd[i] != '=')
		--i;
	if (e->dir)
		free(e->dir);
	e->dir = ft_strdup((pwd[i + 1] == 0 ? 0 : 1) + pwd + i);
	set_oldpwd(e, oldpwd);
	free2(pwd, oldpwd);
	free(stats);
	return (1);
}

int		ft_cd3(char **split, t_env *e, char *oldpwd)
{
	if (!split[1][1] && chdir(e->ev[find_param(e->ev, "OLDPWD")] + 7) == -1)
		error(-1, NULL, oldpwd);
	else if (split[1][1] == 'P' && !split[1][2])
	{
		if (!split[2] && chdir(e->ev[find_param(e->ev, "HOME")] + 5) == -1)
			error(-8, NULL, oldpwd);
		else if (split[2] && chdir(split[2]) == -1)
			return (ft_cd_mini(oldpwd));
		return (0);
	}
	else if (split[1][1] == 'L' && !split[1][2])
	{
		if (!split[2] && chdir(e->ev[find_param(e->ev, "HOME")] + 5) == -1)
			error(-8, NULL, oldpwd);
		else if (split[2])
			if (ft_cd_l(e, oldpwd, split, 0))
				return (1);
		return (0);
	}
	else if (split[1][1])
		error(-4, split[1], oldpwd);
	else
		return (0);
	return (1);
}

void	ft_cd(char **split, t_env *e, char *reg, char *oldpwd)
{
	getpwd(oldpwd);
	if (split[1] && split[2] && split[3])
		return (error(-7, NULL, oldpwd));
	else if (split[1] && split[1][0] == '-')
	{
		if (ft_cd3(split, e, oldpwd))
			return ;
	}
	else if (split[1] && split[2])
	{
		if (ft_cd2(split, reg, oldpwd))
			return ;
	}
	else if (split[1])
	{
		if (chdir(split[1]) == -1)
			return (error(-1, NULL, oldpwd));
	}
	else if (chdir(e->ev[find_param(e->ev, "HOME")] + 5) == -1)
		return (error(-8, NULL, oldpwd));
	ft_newpwd(e, oldpwd);
	free(oldpwd);
}
