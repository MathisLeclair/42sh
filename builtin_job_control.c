/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_job_control.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 17:00:07 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/03 18:16:19 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"


void	builtin_fg(t_env *ev, char **split, int boule)
{
	int i;

	while (ev->job->next)
		ev->job = ev->job->next;
	if (getpid() == ev->job->pid)
	{
		ft_putstr("fg: no current job\n");
		return ;
	}
	if (split[1] && split[2])
	{
		return(error(-7, NULL, NULL));
	}
	if (split[1])
	{
		i = ft_atoi(split[1]);
		while (ev->job->prev && ev->job->num != i)
			ev->job = ev->job->prev;
		if (ev->job->num == i)
		{
			tcsetpgrp(ev->shell_terminal, ev->job->pid);
			kill(ev->job->pid, SIGCONT);
		}
		else
			return(error(-14, NULL, NULL));
	}
	else
	{
		if (boule == 0)
			tcsetpgrp(ev->shell_terminal, ev->job->pid);
		kill(ev->job->pid, SIGCONT);
	}
}

void	builtin_bg(t_env *ev, char **split)
{
	builtin_fg(ev, split, 1);
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
