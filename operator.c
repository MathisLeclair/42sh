/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 13:43:33 by aridolfi          #+#    #+#             */
/*   Updated: 2017/02/26 14:15:30 by mleclair         ###   ########.fr       */
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
		parse(env, env->inp1);
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
	{
		parse(env, env->inp2);
		perror("error");
		exit(EXIT_FAILURE);
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
		perror("error");
	}
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		if (WEXITSTATUS(status) != 0)
		{
			parse(env, env->inp2);
			perror("error");
			exit(EXIT_FAILURE);
		}
}
