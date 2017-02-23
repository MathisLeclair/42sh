/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 12:54:31 by aridolfi          #+#    #+#             */
/*   Updated: 2017/02/22 17:07:22 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
** Pipelines: command1 | command2
*/

void	rd_pipe(void)
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
		ft_reco_cmd(env());
	}
	dup2(fds[0], STDIN_FILENO);
	close(fds[1]);
	wait(NULL);
	ft_reco_cmd(env());
}

/*
** Redirecting Output: command > output.txt
*/

void	rd_output(char *filename)
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
		ft_reco_cmd(env());
	}
	close(fd);
	wait(NULL);
}

/*
** Appending Redirected Output: command >> output.txt
*/

void	rd_output_apd(char *filename)
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
		ft_reco_cmd(env());
	}
	close(fd);
	wait(NULL);
}

/*
** Redirecting Input: command < output.txt
*/

void	rd_input(char *filename)
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
		ft_reco_cmd(env());
	}
	close(fd);
	wait(NULL);
}

/*
** Here-Document:
**
** interactive-program << delimiter
** command 1
** command 2
** .........
** command n
** delimiter
**
** command <<- delimiter
** 		here type your
**		input tabulation
**		will be ignored
** delimiter
**
*/

void	rd_here_doc(char *delimiter)
{
	pid_t		child;
	int			fd;
	int			rsize;
	char		buff[INPUT_SIZE];

	child = -1;
	fd = -1;
	rsize = -1;
	if ((fd = open("/tmp/42sh-thd-silence", O_WRONLY | O_CREAT | O_TRUNC, 0600)) == -1)
		perror("error");
	child = fork();
	if ((int)child == -1)
	{
		close(fd);
		perror("error");
	}
	else if ((int)child == 0)
	{
		termcaps(ft_sprintf("heredoc> "));
		while ((rsize = read(0, buff, INPUT_SIZE)) != -1)
		{
			buff[rsize] = '\0';
			if (!ft_strcmp(buff, delimiter))
				break;
			write(fd, buff, rsize);
			termcaps(ft_sprintf("heredoc> "));
		}
		close(fd);
		if ((fd = open("/tmp/42sh-thd-silence", O_RDONLY)) == -1)
			perror("error");
		unlink("/tmp/42sh-thd-silence");
		dup2(fd, STDIN_FILENO);
		ft_reco_cmd(env());
	}
	wait(NULL);
	close(fd);
}
