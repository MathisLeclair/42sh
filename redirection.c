/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aridolfi <aridolfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 12:54:31 by aridolfi          #+#    #+#             */
/*   Updated: 2017/02/15 15:58:02 by aridolfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
** Pipelines: command1 | command2
*/

void	rd_pipe(char *cmd1, char *cmd2, char *args1[], char *args2[])
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
		perror("error");
	}
	else if ((int)child == 0)
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		execve(cmd1, args1, NULL);
		perror("error");
	}
	dup2(fds[0], STDIN_FILENO);
	close(fds[1]);
	wait(NULL);
	execve(cmd2, args2, NULL);
}

/*
** Redirecting Output: command > output.txt
*/

void	rd_output(char *cmd, char *args[], char *filename)
{
	pid_t		child;
	int			fd;

	child = -1;
	fd = -1;
	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		perror("error");
	child = fork();
	if ((int)child == -1)
	{
		close(fd);
		perror("error");
	}
	else if ((int)child == 0)
	{
		dup2(fd, STDOUT_FILENO);
		execve(cmd, args, NULL);
		perror("error");
	}
	close(fd);
	wait(NULL);
}

/*
** Appending Redirected Output: command >> output.txt
*/

void	rd_output_apd(char *cmd, char *args[], char *filename)
{
	pid_t		child;
	int			fd;

	child = -1;
	fd = -1;
	if ((fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
		perror("error");
	child = fork();
	if ((int)child == -1)
	{
		close(fd);
		perror("error");
	}
	else if ((int)child == 0)
	{
		dup2(fd, STDOUT_FILENO);
		execve(cmd, args, NULL);
		perror("error");
	}
	close(fd);
	wait(NULL);
}

/*
** Redirecting Input: command < output.txt
*/

void	rd_input(char *cmd, char *args[], char *filename)
{
	pid_t		child;
	int			fd;

	child = -1;
	fd = -1;
	if ((fd = open(filename, O_RDONLY)) == -1)
		perror("error");
	child = fork();
	if ((int)child == -1)
	{
		close(fd);
		perror("error");
	}
	else if ((int)child == 0)
	{
		dup2(fd, STDIN_FILENO);
		execve(cmd, args, NULL);
		perror("error");
	}
	close(fd);
	wait(NULL);
}

/*
** Here-Document:
**
** command << delimiter
** 		Here you write the input you want for the command.
** delimiter
*/

// void	rd_here_doc(char *cmd, char *args[])