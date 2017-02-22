/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aridolfi <aridolfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 13:43:33 by aridolfi          #+#    #+#             */
/*   Updated: 2017/02/22 14:30:44 by aridolfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
** AND Lists: command1 [&& command2] ...
*/

void	oprt_and(char *cmd1, char *cmd2, char *args1[], char *args2[])
{
	pid_t		child;

	child = -1;
	if ((int)child == -1)
		perror("error");
	else if ((int)child == 0)
	{
		execve(cmd1, args1, NULL);
		perror("error");
	}
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
	{
		execve(cmd2, args2, NULL);
		perror("error");
		exit(EXIT_FAILURE);
	}
}

/*
** OR Lists: command1 [|| command2] ...
*/

void	oprt_or(char *cmd1, char *cmd2, char *args1[], char *args2[])
{
	pid_t		child;

	child = -1;
	if ((int)child == -1)
		perror("error");
	else if ((int)child == 0)
	{
		execve(cmd1, args1, NULL);
		perror("error");
	}
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		if (WEXITSTATUS(status) != 0)
		{
			execve(cmd2, args2, NULL);
			perror("error");
			exit(EXIT_FAILURE);
		}
}
