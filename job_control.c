/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 14:54:25 by aridolfi          #+#    #+#             */
/*   Updated: 2017/03/05 18:16:30 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	free_current_job(t_env *env)
{
	t_job *sav;

	if (env->job->pid == getpid())
		return ;
	sav = env->job->prev;
	env->job->prev->next = env->job->next;
	if (env->job->next)
		env->job->next->prev = env->job->prev;
	free(env->job->status);
	free(env->job);
	env->job = sav;
}

void	add_job(int u)
{
	t_job *new;

	new = malloc(sizeof(t_job));
	env()->job->next = new;
	env()->job->stat = '-';
	if (env()->job->prev)
		env()->job->prev->stat = ' ';
	new->prev = env()->job;
	new->pid = u;
	new->killable = 0;
	new->next = NULL;
	new->status = ft_strdup("suspend");
	new->stat = '+';
	new->num = env()->job->num + 1;
	new->name = ft_strdup(env()->input);
	env()->job = env()->job->next;
}

void	retreive_ctrlz(int i)
{
	(void)i;

	if (getpid() != env()->job->pid)
	{
		kill(env()->job->pid, SIGTSTP);
		env()->booljob = 1;
		env()->job->killable = 0;
		tcsetpgrp(env()->shell_terminal, i);
		kill(getpid(), SIGCONT);
		printf("\nSuspended\n");
	}
}

void	jobctrl_init_shell(void)
{
	pid_t shell_pgid;
	struct termios shell_tmodes;
	int shell_is_interactive;

	env()->shell_terminal = STDIN_FILENO;
	shell_is_interactive = isatty(env()->shell_terminal);
	if (shell_is_interactive)
    {
		while (tcgetpgrp(env()->shell_terminal) != (shell_pgid = getpgrp()))
	  		kill(- shell_pgid, SIGTTIN);
		shell_pgid = getpid();
		if (setpgid(shell_pgid, shell_pgid) < 0)
	  	{
			perror("Couldn't put the shell in its own process group");
			exit(EXIT_FAILURE);
	  	}
		tcsetpgrp(env()->shell_terminal, shell_pgid);
		tcgetattr(env()->shell_terminal, &shell_tmodes);
    }
}
