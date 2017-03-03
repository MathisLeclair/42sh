/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 14:54:25 by aridolfi          #+#    #+#             */
/*   Updated: 2017/03/03 17:54:28 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	free_last_job(t_env *env)
{
	while (env->job->next)
		env->job = env->job->next;
	if (env->job->prev)
		env->job = env->job->prev;
	else
		return ;
	free(env->job->next->status);
	free(env->job->next);
	env->job->next = NULL;

}

void	add_job(int u)
{
	t_job *new;
	// char **tmp;

	new = malloc(sizeof(t_job));
	env()->job->next = new;
	env()->job->stat = '-';
	if (env()->job->prev)
		env()->job->prev->stat = ' ';
	new->prev = env()->job;
	new->pid = u;
	new->next = NULL;
	new->status = ft_strdup("suspend");
	new->stat = '+';
	new->num = env()->job->num + 1;
	// tmp = ft_strsplitquote(env()->input, ' ', 0);
	new->name = ft_strdup(env()->input);
	env()->job = env()->job->next;
	// free(tmp);
}

void	retreive_ctrlz(int i)
{
	env()->booljob = 1;
	tcsetpgrp(env()->shell_terminal, i);
	kill(SIGCONT, i);
	printf("\nsuspend\n");
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
