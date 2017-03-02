/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 14:54:25 by aridolfi          #+#    #+#             */
/*   Updated: 2017/03/02 14:44:29 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	See if we are running interactively.
**	Loop until we are in the foreground.
**	Ignore interactive and job-control signals.
**	Put ourselves in our own process group.
**	Grab control of the terminal.
**	Save default terminal attributes for shell.
*/

void	 pidenv(int u)
{
	int i;

	i = -1;
	while (env()->PID[++i])
		;
	if (u == 0)
	{
		env()->PID[i] = env()->i;
		env()->PID[i + 1] = 0;
	}
	else if (i >= 1)
		env()->PID[i - 1] = 0;
}

void	retreive_ctrlz(int i)
{
	i = -1;
	while (env()->PID[++i])
		;
	--i;
	if (env()->PID[i] == env()->PID[0])
		return ;
	if (tcgetpgrp(env()->PID[0]) != env()->PID[0])
	{
		kill(SIGTSTP, env()->PID[i]);
		tcsetpgrp(env()->shell_terminal, env()->PID[0]);
		kill(SIGCONT, env()->PID[0]);
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
