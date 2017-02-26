/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bquote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 16:12:42 by mleclair          #+#    #+#             */
/*   Updated: 2017/02/26 19:00:44 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void		remove_nl(char **str)
{
	int i;

	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == '\n')
			(*str)[i] = ' ';
	}
}

void		realoc(char *str, int size)
{
	char *tmp;

	tmp = malloc(size * 2);
	*tmp = 0;
	ft_strcat(tmp, str);
	free(str);
	str = tmp;
}

void		bquote3(t_env *env, char *sav, int i)
{
	char	*str;
	int		fd;

	fd = open("/tmp/42sh_the_silence", O_RDONLY);
	unlink("/tmp/42sh_the_silence");
	str = malloc(INPUT_SIZE);
	while (read(fd, str, INPUT_SIZE - 1))
	{
		str[INPUT_SIZE] = 0;
		realoc(str, INPUT_SIZE);
	}
	close(fd);
	free(env->input);
	env->input = malloc(ft_strlen(str));
	env->input[0] = 0;
	remove_nl(&str);
	ft_strncat(env->input, sav, i);
	ft_strcat(env->input, str);
	ft_strcat(env->input, sav + i);
}

void		bquote2(t_env *env)
{
	pid_t	child;
	int		fd;

	child = -1;
	fd = -1;
	if ((fd = open("/tmp/42sh_the_silence",
		O_WRONLY | O_CREAT | O_TRUNC, 0600)) == -1)
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
		parse(env, env->input);
		exit(EXIT_SUCCESS);
	}
	close(fd);
	wait(NULL);
}

void	bquote(t_env *env)
{
	int		i;
	int		k;
	char	*sav;

	i = -1;
	k = 0;
	env->inp1 = malloc(INPUT_SIZE);
	env->inp1[0] = 0;
	while (env->input[++i])
		if (env->input[i] == '`')
			++k;
	if (k % 2 == 1)
		while (!ft_strchr(env->inp1, '`'))
			env->inp1 = ft_strjoin(env->inp1, termcaps(ft_sprintf("bquote>")));
	else
		env->inp1 = ft_strdup(env->input);
	i = ft_strfind(env->inp1, '`');
	k = ft_strcfind(env->inp1, '`');
	sav = ft_strdup(env->input);
	free(env->input);
	env->input = malloc(INPUT_SIZE);
	ft_strncat(env->input, env->inp1 + i + 1, k);
	env->input[ft_strfind(env->input, '`')] = 0;
	bquote2(env);
	bquote3(env, sav, i);
}
