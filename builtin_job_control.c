/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_job_control.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 17:00:07 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/03 16:05:40 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"


void	builtin_fg(t_env *ev, char **split)
{
	// int i;

	(void)split;
	(void)ev;
	// i = -1;
	// while (ev->PID[++i])
	// 	;
	// i -= 1;
	// tcsetpgrp(env()->shell_terminal, env()->PID[i]);
	// kill(SIGCONT, env()->PID[i]);
}

void	builtin_bg(t_env *ev, char **split)
{
	(void)ev;
	(void)split;
}

void	builtin_jobs(t_env *ev, char **split)
{
	int i;

	(void)split;
	i = -1;
	while(ev->job->prev)
		ev->job = ev->job->prev;
	if (!ev->job->next)
		return ;
	while(ev->job->next)
	{
		ev->job = ev->job->next;
		ft_printf("[%d] %c %s %s\n", ev->job->num, ev->job->stat, ev->job->status ,ev->job->name);
	}
}
