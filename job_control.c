/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aridolfi <aridolfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 14:54:25 by aridolfi          #+#    #+#             */
/*   Updated: 2017/03/02 13:02:03 by aridolfi         ###   ########.fr       */
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

void	jobctrl_init_shell(void)
{
	pid_t shell_pgid;
	struct termios shell_tmodes;
	int shell_terminal;
	int shell_is_interactive;

	shell_terminal = STDIN_FILENO;
	shell_is_interactive = isatty(shell_terminal);
	if (shell_is_interactive)
    {
		while (tcgetpgrp(shell_terminal) != (shell_pgid = getpgrp()))
	  		kill(- shell_pgid, SIGTTIN);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
		signal(SIGCHLD, SIG_IGN);
		shell_pgid = getpid();
		if (setpgid(shell_pgid, shell_pgid) < 0)
	  	{
			perror("Couldn't put the shell in its own process group");
			exit(EXIT_FAILURE);
	  	}
		tcsetpgrp(shell_terminal, shell_pgid);
		tcgetattr(shell_terminal, &shell_tmodes);
    }
}
