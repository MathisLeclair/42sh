/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_job_control.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 17:00:07 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/04 16:53:45 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	supressoldstat(t_env *e, char c)
{
	t_job *sav;

	sav = e->job;
	while (e->job->prev)
	{
		e->job = e->job->prev;
		if (e->job->stat == c)
			e->job->stat = ' ';
	}
	e->job = sav;
	while (e->job->next)
	{
		e->job = e->job->next;
		if (e->job->stat == c)
			e->job->stat = ' ';
	}
	e->job = sav;
}

void	fg_minus(t_env *e)
{
	t_job *sav;

	sav = e->job;
	while (e->job->prev)
		e->job = e->job->prev;
	while (e->job->next)
	{
		if (e->job->stat == '+')
		{
			e->job->stat = '-';
			return ;
		}
		e->job = e->job->next;
	}
	e->job = sav;
}

void	builtin_fg(t_env *ev, char **split, int boule)
{
	int i;

	if (getpid() == ev->job->pid)
		return ft_putstr("fg: no current job\n");
	if (split[1] && split[2])
		return(error(-7, NULL, NULL));
	if (split[1])
	{
		i = ft_atoi(split[1]);
		supressoldstat(ev, '-');
		while (ev->job->prev && ev->job->num != i)
			ev->job = ev->job->prev;
		if (ev->job->num == i)
		{
			tcsetpgrp(ev->shell_terminal, ev->job->pid);
			kill(ev->job->pid, SIGCONT);
			ev->job->killable = 1;
			fg_minus(ev);
			ev->job->stat = '+';
		}
		else
		{
			ev->job->stat = '+';
			return(error(-14, NULL, NULL));
		}
	}
	else
	{
		if (boule == 0)
		{
			tcsetpgrp(ev->shell_terminal, ev->job->pid);
			ev->job->killable = 1;
		}
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
