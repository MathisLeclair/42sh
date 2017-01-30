/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 17:55:44 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/30 17:44:36 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	ft_child2(t_env *env, char **input, char *pwd, char *tmp)
{
	struct stat	buf[INPUT_SIZE];
	size_t		t;

	t = ft_strlen(*input);
	while (t != 0 && (*input)[t] != '/')
		--t;
	if (tmp && tmp[0] == '/' && (*input += t + 1))
		execve(tmp, input, env->ev);
	*input = tmp;
	if (ft_cmpspec(*input, "./") == 1)
	{
		tmp = ft_strjoin(pwd + 4, *input + 1);
		execve(tmp, input, env->ev);
		if (lstat(tmp, buf) == -1)
			error(-1, NULL, NULL);
		else if (!(buf->st_mode & S_IXUSR) || !(buf->st_mode & S_IROTH))
			error(-5, *input, NULL);
		else
			error(-4, *input, NULL);
		free(tmp);
		exit(0);
	}
	error(-2, *input, NULL);
	env_free(env);
	exit(0);
}

void	ft_child(t_env *env, char **input, char *pwd)
{
	int			i;
	char		*tmp;
	char		*tmp2;

	if ((i = find_param(env->ev, "PATH")) != -1)
		env->path = ft_strsplit(env->ev[i] + 5, ':');
	else if (env->savev && (i = find_param(env->savev, "PATH")) != -1)
		env->path = ft_strsplit(env->savev[i] + 5, ':');
	i = 0;
	while (env->path && env->path[i] && ft_strchr(*input, '/') == 0)
	{
		tmp = ft_strjoin(env->path[i], "/");
		tmp2 = ft_strjoin(tmp, *input);
		execve(tmp2, input, env->ev);
		free(tmp);
		free(tmp2);
		++i;
	}
	tmp = *input;
	ft_child2(env, input, pwd, tmp);
}

void	ft_fork(t_env *env, char **input)
{
	int			status;
	size_t		t;
	char		pwd[INPUT_SIZE + 4];

	getpwd(pwd);
	t = 0;
	env->i = fork();
	if (env->i == 0)
		ft_child(env, input, pwd);
	else
	{
		if (wait(&status) == -1)
			error(-3, NULL, NULL);
		env->i = 1;
	}
}
