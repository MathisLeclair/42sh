/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 16:40:58 by bfrochot          #+#    #+#             */
/*   Updated: 2017/01/23 13:08:27 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	ft_exit(void)
{
	env_free(env());
	ft_putstr("exit\n");
	exit(1);
}

char	*ft_cd_regex(char **split, int k)
{
	char pwd[INPUT_SIZE + 5];
	char *sav;
	char *reg;

	getpwd(pwd);
	if (!(sav = ft_super_strstr(pwd + 4, split[1])))
		error(-10, split[1]);
	if (!sav)
		return (NULL);
	reg = palloc(ft_strlen(pwd + 4) + ft_strlen(split[2])
	- ft_strlen(split[1]) + 1);
	while (pwd + 4 + ++k < sav)
		reg[k] = pwd[4 + k];
	reg[k] = 0;
	ft_strcat(reg + k, split[2]);
	ft_strcat(reg + k, sav + ft_strlen(split[1]));
	return (reg);
}

void	ft_newpwd(t_env *env, char *oldpwd)
{
	char	pwd[INPUT_SIZE + 5];
	size_t	i;

	set_oldpwd(env, oldpwd);
	getpwd(pwd);
	add_var_to_env(env, pwd);
	i = ft_strlen(pwd);
	while (pwd[i] != '/' && pwd[i] != '=')
		--i;
	if (env->dir)
		free(env->dir);
	env->dir = ft_strdup((pwd[i + 1] == 0 ? 0 : 1) + pwd + i);
}

void	ft_cd(char **split, t_env *env, char *reg, char *oldpwd)
{
	getpwd(oldpwd);
	if (split[1] && split[2] && split[3])
		return (error(-7, NULL));
	else if (split[1] && split[1][0] == '-' && !split[1][1])
	{
		if (chdir(env->ev[find_param(env->ev, "OLDPWD")] + 7) == -1)
			return (error(-1, NULL));
	}
	else if (split[1] && split[2])
	{
		if (!(reg = ft_cd_regex(split, -1)))
			return ;
		if (chdir(reg) == -1)
			return (error(-9, reg));
		free(reg);
	}
	else if (split[1])
	{
		if (chdir(split[1]) == -1)
			return (error(-1, NULL));
	}
	else if (chdir(env->ev[find_param(env->ev, "HOME")] + 5) == -1)
		return (error(-8, NULL));
	ft_newpwd(env, oldpwd);
}

void	ft_echo(char **split)
{
	int i;

	i = 0;
	while (split[++i])
	{
		ft_putstr(split[i]);
		if (split[i + 1])
			ft_putchar(' ');
	}
	ft_putchar('\n');
}
