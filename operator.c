/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 13:43:33 by aridolfi          #+#    #+#             */
/*   Updated: 2017/03/21 16:32:47 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

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
		error(-16, NULL, NULL);
	else if ((int)child == 0)
	{
		parse(env, &env->inp1, 1);
		exit(env->lastret);
	}
	waitpid(child, &status, 0);
	if (WEXITSTATUS(status) == 0)
	{
		parse(env, &env->inp2, 1);
		retvalue_into_loc(env, env->lastret);
	}
	else
		retvalue_into_loc(env, WEXITSTATUS(status));
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
		error(-16, NULL, NULL);
	else if ((int)child == 0)
	{
		parse(env, &env->inp1, 1);
		exit(env->lastret);
	}
	waitpid(child, &status, 0);
	if (WEXITSTATUS(status) != 0)
	{
		parse(env, &env->inp2, 1);
		env->isoperand = 0;
		retvalue_into_loc(env, env->lastret);
	}
	else
		retvalue_into_loc(env, WEXITSTATUS(status));
}
