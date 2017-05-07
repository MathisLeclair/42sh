/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 12:54:31 by aridolfi          #+#    #+#             */
/*   Updated: 2017/05/01 15:53:54 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

/*
** Redirecting Output: command [n]> output.txt
**					   command [n]>| output.txt
*/

int			verredir(t_env *env)
{
	int i;

	i = 0;
	while (env->input[i])
	{
		if (env->input[i] == '>')
			if (env->input[i + 1] && env->input[i + 1] == '>')
				if (env->input[i + 2] && env->input[i + 2] == '>')
				{
					error(-15, NULL, NULL);
					return (-1);
				}
		i++;
	}
	return (0);
}

void		rd_output(t_env *env, int fd, int n, pid_t child)
{
	char	**s;
	int		status;

	if (ft_isdigit(*(env->redir)))
		n = *(env->redir) - 48;
	if ((s = ft_strsplitquote(env->redir + (n == -1 ? 1 : 2), ' ', 1)) && !s[0])
		return (free(s));
	free_swap(&env->redir, ft_strdup(s[0]));
	free_double_array(s);
	if (env->redir[0] == '&')
		return (rd_dupoutput(env, n));
	if ((fd = open(env->redir, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		error(-17, NULL, NULL);
	child = fork();
	if ((int)child == -1)
		error(-16, NULL, NULL);
	else if ((int)child == 0)
	{
		dup2(fd, (n == -1 ? STDOUT_FILENO : (int)n));
		parse(env, &env->input, 1);
		exit(env->lastret);
	}
	close(fd);
	wait(&status);
	retvalue_into_loc(env, WEXITSTATUS(status));
}

/*
** Appending Redirected Output: command [n]>> output.txt
*/

void		rd_output_apd(t_env *env, int fd, pid_t child)
{
	char		n;
	char		**s;
	int			status;

	n = -1;
	if (ft_isdigit(*(env->redir)))
		n = *(env->redir) - 48;
	s = ft_strsplitquote(env->redir + (n == -1 ? 2 : 3), ' ', 1);
	free_swap(&env->redir, ft_strdup(s[0]));
	free_double_array(s);
	if ((fd = open(env->redir, O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
		error(-17, NULL, NULL);
	child = fork();
	if ((int)child == -1)
		error(-16, NULL, NULL);
	else if ((int)child == 0)
	{
		dup2(fd, (n == -1 ? STDOUT_FILENO : (int)n));
		parse(env, &env->input, 1);
		exit(env->lastret);
	}
	close(fd);
	wait(&status);
	retvalue_into_loc(env, WEXITSTATUS(status));
}

/*
** Redirecting Input: command [n]< output.txt
*/

int			rd_input2(t_env *env, char *n, int *fd)
{
	if (ft_isdigit(env->inp1[ft_strlen(env->inp1) - 1]))
		*n = (env->inp1[ft_strlen(env->inp1) - 2] == '\\' ? -1 :
			env->inp1[ft_strlen(env->inp1) - 1] - 48);
	if (*n != -1)
		env->inp1[ft_strlen(env->inp1) - 1] = '\0';
	if (env->inp2[0] == '&')
	{
		rd_dupinput(env, *n);
		return (0);
	}
	if ((*fd = open(env->inp2, O_RDONLY)) == -1)
	{
		error(-17, NULL, NULL);
		close(*fd);
		return (-1);
	}
	return (0);
}

void		rd_input(t_env *env, int fd)
{
	pid_t		child;
	char		n;
	int			status;
	char		**s;

	child = -1;
	n = -1;
	if ((s = ft_strsplitquote(env->inp2, ' ', 1)) && !s[0])
		return (free(s));
	free_swap(&env->inp2, ft_strdup(s[0]));
	free_double_array(s);
	if (rd_input2(env, &n, &fd) == -1)
		return ;
	child = fork();
	if ((int)child == -1)
		error(-16, NULL, NULL);
	else if ((int)child == 0)
	{
		dup2(fd, (n == -1 ? STDIN_FILENO : (int)n));
		parse(env, &env->inp1, 1);
		exit(env->lastret);
	}
	close(fd);
	wait(&status);
	retvalue_into_loc(env, WEXITSTATUS(status));
}
