/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_adv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 11:55:38 by aridolfi          #+#    #+#             */
/*   Updated: 2017/03/16 13:11:24 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

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

void		rd_here_doc2(t_env *env, int fd, int n)
{
	char		*buff;

	while ((buff = ft_strjoin(termcaps(ft_sprintf("heredoc> ")), "\n")))
	{
		if (!ft_strcmp(buff, env->inp2))
			break ;
		write(fd, buff, ft_strlen(buff));
		free(buff);
	}
	close(fd);
	if ((fd = open("/tmp/42sh-the-silence", O_RDONLY)) == -1)
		error(-17, NULL, NULL);
	unlink("/tmp/42sh-the-silence");
	dup2(fd, (n == -1 ? STDIN_FILENO : (int)n));
	parse(env, env->inp1);
	exit(env->lastret);
}

void		rd_here_doc(t_env *env, int child, int fd)
{
	char		n;
	int			status;

	n = -1;
	if (ft_isdigit(env->inp1[ft_strlen(env->inp1) - 1]))
		n = (env->inp1[ft_strlen(env->inp1) - 2] == '\\' ? -1 :
			env->inp1[ft_strlen(env->inp1) - 1] - 48);
	if (n != -1)
		env->inp1[ft_strlen(env->inp1) - 1] = '\0';
	rd_delimiter(&env->inp2);
	if ((fd = open("/tmp/42sh-the-silence", O_WRONLY | O_CREAT | O_TRUNC, 0600))
	== -1)
		error(-17, NULL, NULL);
	child = fork();
	if ((int)child == -1)
		error(-16, NULL, NULL);
	else if ((int)child == 0)
		rd_here_doc2(env, fd, n);
	wait(&status);
	retvalue_into_loc(env, WEXITSTATUS(status));
	close(fd);
}

void		rd_here_string2(t_env *env, int fd, int n)
{
	write(fd, env->inp2, ft_strlen(env->inp2));
	close(fd);
	if ((fd = open("/tmp/42sh-the-silence", O_RDONLY)) == -1)
		error(-17, NULL, NULL);
	unlink("/tmp/42sh-the-silence");
	dup2(fd, (n == -1 ? STDIN_FILENO : (int)n));
	parse(env, env->inp1);
	ft_putchar('\n');
	exit(env->lastret);
}

void		rd_here_string(t_env *env, int fd, int n, pid_t child)
{
	char		**s;
	int			status;

	if (ft_isdigit(env->inp1[ft_strlen(env->inp1) - 1]))
		n = (env->inp1[ft_strlen(env->inp1) - 2] == '\\' ? -1 :
			env->inp1[ft_strlen(env->inp1) - 1] - 48);
	if (n != -1)
		env->inp1[ft_strlen(env->inp1) - 1] = '\0';
	s = ft_strsplitquote(env->inp2, ' ', 1);
	ft_suppr_quotes(s[0], 0, 0);
	free_swap(&env->inp2, ft_strdup(s[0]));
	free_double_array(s);
	if ((fd = open("/tmp/42sh-the-silence", O_WRONLY | O_CREAT | O_TRUNC, 0600))
	== -1)
		error(-17, NULL, NULL);
	child = fork();
	if ((int)child == -1)
		error(-16, NULL, NULL);
	else if ((int)child == 0)
		rd_here_string2(env, fd, n);
	wait(&status);
	retvalue_into_loc(env, WEXITSTATUS(status));
	close(fd);
}
