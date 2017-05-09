/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 18:02:42 by mleclair          #+#    #+#             */
/*   Updated: 2017/05/09 18:05:54 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

char	*ft_cd_regex(char **split, int k)
{
	char pwd[INPUT_SIZE + 5];
	char *sav;
	char *reg;

	getpwd(pwd);
	if (!(sav = ft_super_strstr(pwd + 4, split[1])))
		error(-10, split[1], NULL);
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

int		ft_cd2(char **split, char *reg, char *oldpwd)
{
	if (!(reg = ft_cd_regex(split, -1)))
	{
		free(oldpwd);
		return (1);
	}
	if (chdir(reg) == -1)
	{
		error(-9, reg, oldpwd);
		if (reg)
			free(reg);
		return (1);
	}
	free(reg);
	return (0);
}

int		ft_cd_l2(char **split, char *pwd, struct stat *stats, char *oldpwd)
{
	if (chdir(split[2]) == -1)
	{
		error(-1, NULL, oldpwd);
		free(pwd);
		free(stats);
		return (1);
	}
	free(pwd);
	free(stats);
	return (0);
}
