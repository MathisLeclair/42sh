/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_adv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aridolfi <aridolfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 11:55:38 by aridolfi          #+#    #+#             */
/*   Updated: 2017/03/09 16:52:18 by aridolfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
** Here-String: command [n]<<< string
*/

/*static void	rd_here_string(t_env *env, char n)
{
	pid_t		child;
	int			fd;
	int			rsize;

	child = -1;
	fd = -1;
	rsize = -1;
	free_swap(&env->inp2, ft_strdup(env->inp2 + 1));
	if ((fd = open("/tmp/42sh-the-silence", O_WRONLY | O_CREAT | O_TRUNC, 0600)) == -1)
		perror("error");
	child = fork();
	if ((int)child == -1)
	{
		close(fd);
		perror("error");
	}
	else if ((int)child == 0)
	{
		write(fd, env->inp2, ft_strlen(env->inp2));
		close(fd);
		if ((fd = open("/tmp/42sh-the-silence", O_RDONLY)) == -1)
			perror("error");
		unlink("/tmp/42sh-the-silence");
		dup2(fd, (n == -1 ? STDIN_FILENO : (int)n));
		parse(env, env->inp1);
		exit(env->lastret);
	}
	wait(NULL);
	close(fd);
}*/

/*
** Here-Document:
**
** interactive-program [n]<< delimiter
** command 1
** command 2
** .........
** command n
** delimiter
**
** command [n]<<- delimiter
** 		here type your
**		input tabulation
**		will be ignored
** delimiter
**
*/

static void	rd_delimiter(char **str)
{
	int i;

	i = -1;
	while ((*str)[++i] == ' ' || (*str)[i] == '<')
		;
	*str[0] = 0;
	ft_strcat(*str, *str + i);
	ft_strcat(*str, "\n");
}

void		rd_here_doc(t_env *env)
{
	pid_t		child;
	int			fd;
	int			rsize;
	char		n;
	char		*buff;

	child = -1;
	fd = -1;
	rsize = -1;
	n = -1;
	if (ft_isdigit(env->inp1[ft_strlen(env->inp1) - 1]))
		n = (env->inp1[ft_strlen(env->inp1) - 2] == '\\' ? -1 : env->inp1[ft_strlen(env->inp1) - 1] - 48);
	if (n != -1)
		env->inp1[ft_strlen(env->inp1) - 1] = '\0';
	/*if (env->inp2[0] == '<')
	{
		rd_here_string(env, n);
		return ;
	}*/
	rd_delimiter(&env->inp2);
	if ((fd = open("/tmp/42sh-the-silence", O_WRONLY | O_CREAT | O_TRUNC, 0600)) == -1)
		perror("error");
	child = fork();
	if ((int)child == -1)
	{
		close(fd);
		perror("error");
	}
	else if ((int)child == 0)
	{
		while ((buff = ft_strjoin(termcaps(ft_sprintf("heredoc> ")), "\n")))
		{
			if (!ft_strcmp(buff, env->inp2))
				break;
			write(fd, buff, ft_strlen(buff));
			free(buff);
		}
		close(fd);
		if ((fd = open("/tmp/42sh-the-silence", O_RDONLY)) == -1)
			perror("error");
		unlink("/tmp/42sh-the-silence");
		dup2(fd, (n == -1 ? STDIN_FILENO : (int)n));
		parse(env, env->inp1);
		exit(env->lastret);
	}
	wait(NULL);
	close(fd);
}
