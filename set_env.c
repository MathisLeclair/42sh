/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 17:47:40 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/20 18:39:03 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	getpwd(char *pwd)
{
	pwd[0] = 'P';
	pwd[1] = 'W';
	pwd[2] = 'D';
	pwd[3] = '=';
	getcwd(pwd + 4, INPUT_SIZE);
}

void	set_oldpwd(t_env *env, char *str)
{
	char	oldpwd[INPUT_SIZE + 7];

	oldpwd[0] = 'O';
	oldpwd[1] = 'L';
	oldpwd[2] = 'D';
	oldpwd[3] = 'P';
	oldpwd[4] = 'W';
	oldpwd[5] = 'D';
	oldpwd[6] = '=';
	oldpwd[7] = '\0';
	ft_strcat(oldpwd, str + 4);
	add_var_to_env(env, oldpwd);
}

void	set_env(t_env *env, char **ev)
{
	size_t	i;
	char	pwd[INPUT_SIZE + 4];

	i = 0;
	env->i = 1;
	env->input = NULL;
	env->path = NULL;
	while (ev[i])
		++i;
	env->ev = palloc(sizeof(char *) * (i + 1));
	if (env->ev == NULL)
		error(-666, NULL);
	env->ev[i] = 0;
	while (i--)
		env->ev[i] = ft_strdup(ev[i]);
	getpwd(pwd);
	if (find_param(env->ev, "PWD") == -1)
		add_var_to_env(env, pwd);
	i = ft_strlen(pwd);
	while (pwd[i] != '/' && pwd[i] != '=')
		--i;
	env->dir = ft_strdup((pwd[i + 1] == 0 ? 0 : 1) + pwd + i);
	env->savev = 0;
}
