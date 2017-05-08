/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 13:24:11 by mleclair          #+#    #+#             */
/*   Updated: 2017/05/08 15:21:05 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

/*
** Pipelines: command1 | command2
*/

void	frk_right(t_env *env, int *fds, int *st)
{
	dup2(fds[0], 0);
	close(fds[1]);
	parse(env, &env->inp2, 1);
	dup2(st[0], 0);
	close(st[0]);
	exit(env->lastret);
}

void	frk_left(t_env *env, int *fds, int *st)
{
	dup2(fds[1], 1);
	close(fds[0]);
	parse(env, &env->inp1, 1);
	dup2(st[1], 1);
	close(st[1]);
	exit(env->lastret);
}

void		rd_pipe2(int *frk, int *fds, int *st, t_env *env)
{
	if ((frk[0] = fork()) == -1)
	{
		error(-16, NULL, NULL);
		exit(EXIT_FAILURE);
	}
	else if (frk[0] == 0)
		frk_right(env, fds, st);
	if ((frk[1] =  fork()) == -1)
	{
		error(-16, NULL, NULL);
		exit(EXIT_FAILURE);
	}
	else if (frk[1] == 0)
		frk_left(env, fds, st);
}

void		rd_pipe(t_env *env)
{
	int fds[2];
	int st[2];
	int frk[2];

	pipe(fds);
	st[0] = dup(0);
	st[1] = dup(1);
	rd_pipe2(frk, fds, st, env);
	close(fds[0]);
	close(fds[1]);
	waitpid(frk[0], &fds[0], 0);
	retvalue_into_loc(env, WEXITSTATUS(fds[0]));
	waitpid(frk[1], &fds[1], 0);
	retvalue_into_loc(env, WEXITSTATUS(fds[1]));
}
