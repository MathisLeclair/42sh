/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 13:43:33 by aridolfi          #+#    #+#             */
/*   Updated: 2017/03/12 12:50:00 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
** AND Lists: command1 [&& command2] ...
*/

void	oprt_and(t_env *env)
{
	pid_t	child;
	int		status;

	child = -1;
	child = fork();
	if ((int)child == -1)
		perror("error");
	else if ((int)child == 0)
	{
		parse(env, env->inp1);
		exit(env->lastret);
	}
	waitpid(child, &status, 0);
	retvalue_into_loc(env, WEXITSTATUS(status));
	if (WEXITSTATUS(status) == 0)
	{
		parse(env, env->inp2);
	}
}

/*
** OR Lists: command1 [|| command2] ...
*/

void	oprt_or(t_env *env)
{
	pid_t	child;
	int		status;

	child = -1;
	child = fork();
	if ((int)child == -1)
		perror("error");
	else if ((int)child == 0)
	{
		parse(env, env->inp1);
		exit(env->lastret);
	}
	waitpid(child, &status, 0);
	retvalue_into_loc(env, WEXITSTATUS(status));
	if (WEXITSTATUS(status) == 0)
		return ;
	if (WEXITSTATUS(status) != 0)
	{
		parse(env, env->inp2);
		env->isoperand = 0;
	}
}
