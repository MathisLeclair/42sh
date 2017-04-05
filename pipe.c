/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 13:24:11 by mleclair          #+#    #+#             */
/*   Updated: 2017/04/05 15:29:59 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

/*
** Pipelines: command1 | command2
*/

static void	frk_pipe(t_env *env)
{
	pid_t		child;
	int			fds[2];

	child = -1;
	pipe(fds);
	child = fork();
	if ((int)child == -1)
	{
		close(fds[1]);
		close(fds[0]);
		error(-16, NULL, NULL);
	}
	else if ((int)child == 0)
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		parse(env, &env->inp1);
		exit(env->lastret);
	}
	dup2(fds[0], STDIN_FILENO);
	close(fds[1]);
	parse(env, &env->inp2);
}

void		rd_pipe(t_env *env)
{
	pid_t	child;
	int		status;

	child = -1;
	child = fork();
	if ((int)child == -1)
	{
		error(-16, NULL, NULL);
		exit(EXIT_FAILURE);
	}
	else if ((int)child == 0)
	{
		env->isoperand = 1;
		frk_pipe(env);
		env->isoperand = 0;
		exit(env->lastret);
	}
	wait(&status);
	retvalue_into_loc(env, WEXITSTATUS(status));
}
