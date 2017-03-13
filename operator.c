/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aridolfi <aridolfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 13:43:33 by aridolfi          #+#    #+#             */
/*   Updated: 2017/03/13 13:49:25 by aridolfi         ###   ########.fr       */
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
	// printf("POUETAN\n");
	child = fork();
	if ((int)child == -1)
		perror("error");
	else if ((int)child == 0)
	{
		parse(env, env->inp1);
		exit(env->lastret);
	}
	waitpid(child, &status, 0);
	if (WEXITSTATUS(status) == 0)
	{
		parse(env, env->inp2);
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
	// printf("POUET\n");
	child = fork();
	if ((int)child == -1)
		perror("error");
	else if ((int)child == 0)
	{
		// printf("%s\n", env->inp1);
		parse(env, env->inp1);
		exit(env->lastret);
	}
	waitpid(child, &status, 0);
	if (WEXITSTATUS(status) != 0)
	{
		parse(env, env->inp2);
		env->isoperand = 0;
		retvalue_into_loc(env, env->lastret);
	}
	else
		retvalue_into_loc(env, WEXITSTATUS(status));
}
