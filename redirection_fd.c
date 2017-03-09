/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aridolfi <aridolfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 18:38:45 by aridolfi          #+#    #+#             */
/*   Updated: 2017/03/09 16:51:39 by aridolfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
** Duplicating an Input File Descriptor: command [n]<&word
*/

static void	rd_closeinput(t_env *env, char n)
{
	pid_t		child;
	int			std_tmp;

	child = -1;
	if (n == -1 || (n >= 0 && n <= 2))
		std_tmp = dup(n == -1 ? STDIN_FILENO : (int)n);
	close(n == -1 ? STDIN_FILENO : (int)n);
	child = fork();
	if ((int)child == -1)
		perror("error");
	else if ((int)child == 0)
	{
		parse(env, env->inp1);
		exit(env->lastret);
	}
	wait(NULL);
	if (n == -1 || (n >= 0 && n <= 2))
		dup2(std_tmp, (n == -1 ? STDIN_FILENO : (int)n));
}

void		rd_dupinput(t_env *env, char n)
{
	pid_t		child;
	char		word;

	child = -1;
	word = env->inp2[1] - 48;
	if (word == ('-' - 48))
	{
		rd_closeinput(env, n);
		return ;
	}
	if (fcntl((int)word, F_GETFD) == -1)
		perror("error");
	child = fork();
	if ((int)child == -1)
		perror("error");
	else if ((int)child == 0)
	{
		dup2(word, (n == -1 ? STDIN_FILENO : n));
		parse(env, env->inp1);
		exit(env->lastret);
	}
	wait(NULL);
}

/*
** Duplicating an Output File Descriptor: command [n]>&word
*/

static void	rd_closeoutput(t_env *env, char n)
{
	pid_t		child;
	int			std_tmp;

	child = -1;
	if (n == -1 || (n >= 0 && n <= 2))
		std_tmp = dup(n == -1 ? STDOUT_FILENO : (int)n);
	close(n == -1 ? STDOUT_FILENO : (int)n);
	child = fork();
	if ((int)child == -1)
		perror("error");
	else if ((int)child == 0)
	{
		parse(env, env->inp1);
		exit(env->lastret);
	}
	wait(NULL);
	if (n == -1 || (n >= 0 && n <= 2))
		dup2(std_tmp, (n == -1 ? STDOUT_FILENO : (int)n));
}

void		rd_dupoutput(t_env *env, char n)
{
	pid_t		child;
	char		word;

	child = -1;
	word = env->inp2[1] - 48;
	if (word == ('-' - 48))
	{
		rd_closeoutput(env, n);
		return ;
	}
	if (fcntl((int)word, F_GETFD) == -1)
		perror("error");
	child = fork();
	if ((int)child == -1)
		perror("error");
	else if ((int)child == 0)
	{
		dup2(word, (n == -1 ? STDOUT_FILENO : n));
		parse(env, env->inp1);
		exit(env->lastret);
	}
	wait(NULL);
}
