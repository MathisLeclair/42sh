/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aridolfi <aridolfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 12:54:31 by aridolfi          #+#    #+#             */
/*   Updated: 2017/03/10 12:06:17 by aridolfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
** Pipelines: command1 | command2
*/

static void	frk_pipe(t_env *env)
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
		parse(env, env->inp1);
		exit(env->lastret);
	}
	dup2(fds[0], STDIN_FILENO);
	close(fds[1]);
	parse(env, env->inp2);
	wait(NULL);
}

void	rd_pipe(t_env *env)
{
	pid_t	child;

	child = -1;
	child = fork();
	if ((int)child == -1)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
	else if ((int)child == 0)
	{
		env->isoperand = 1;
		frk_pipe(env);
		env->isoperand = 0;
		exit(env->lastret);
	}
	wait(NULL);
}

/*
** Redirecting Output: command [n]> output.txt
**					   command [n]>| output.txt
*/

void		rd_output(t_env *env, int i)
{
	pid_t	child;
	int		fd;
	char	n;
	char	**s;

	child = -1;
	fd = -1;
	n = -1;
	if (ft_isdigit(env->inp1[ft_strlen(env->inp1) - 1]))
		n = (env->inp1[ft_strlen(env->inp1) - 2] == '\\' ? -1 : env->inp1[ft_strlen(env->inp1) - 1] - 48);
	if (n != -1)
		env->inp1[ft_strlen(env->inp1) - 1] = '\0';
	if (env->inp2[0] == '&')
	{
		rd_dupoutput(env, n);
		return ;
	}
	s = ft_strsplitquote(env->redir[i], ' ', 0);
	if ((fd = open(s[1] == 0 ? s[0] + 1 : s[1], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		perror("error");
	free_double_array(s);
	child = fork();
	if ((int)child == -1)
	{
		close(fd);
		perror("error");
	}
	else if ((int)child == 0)
	{
		dup2(fd, (n == -1 ? STDOUT_FILENO : (int)n));
		parse(env, env->input);
		exit(env->lastret);
	}
	close(fd);
	wait(NULL);
}

/*
** Appending Redirected Output: command [n]>> output.txt
*/

void		rd_output_apd(t_env *env, int i)
{
	pid_t		child;
	int			fd;
	char		n;
	char		**s;

	child = -1;
	fd = -1;
	n = -1;
	if (ft_isdigit(env->inp1[ft_strlen(env->inp1) - 1]))
		n = (env->inp1[ft_strlen(env->inp1) - 2] == '\\' ? -1 : env->inp1[ft_strlen(env->inp1) - 1] - 48);
	if (n != -1)
		env->inp1[ft_strlen(env->inp1) - 1] = '\0';
	s = ft_strsplitquote(env->redir[i], ' ', 0);
	if ((fd = open(s[1] == 0 ? s[0] + 2 : s[1], O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
		perror("error");
	free_double_array(s);
	child = fork();
	if ((int)child == -1)
	{
		close(fd);
		perror("error");
	}
	else if ((int)child == 0)
	{
		dup2(fd, (n == -1 ? STDOUT_FILENO : (int)n));
		parse(env, env->input);
		exit(env->lastret);
	}
	close(fd);
	wait(NULL);
}

/*
** Redirecting Input: command [n]< output.txt
*/

void		rd_input(t_env *env)
{
	pid_t		child;
	int			fd;
	char		n;

	child = -1;
	fd = -1;
	n = -1;
	if (ft_isdigit(env->inp1[ft_strlen(env->inp1) - 1]))
		n = (env->inp1[ft_strlen(env->inp1) - 2] == '\\' ? -1 : env->inp1[ft_strlen(env->inp1) - 1] - 48);
	if (n != -1)
		env->inp1[ft_strlen(env->inp1) - 1] = '\0';
	if (env->inp2[0] == '&')
	{
		rd_dupinput(env, n);
		return ;
	}
	if ((fd = open(env->inp2, O_RDONLY)) == -1)
		perror("error");
	child = fork();
	if ((int)child == -1)
	{
		close(fd);
		perror("error");
	}
	else if ((int)child == 0)
	{
		dup2(fd, (n == -1 ? STDIN_FILENO : (int)n));
		parse(env, env->inp1);
		exit(env->lastret);
	}
	close(fd);
	wait(NULL);
}
