/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bquote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 16:12:42 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/19 17:46:31 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

void		remove_nl(char **str)
{
	int i;

	if (!(*str))
		return ;
	i = -1;
	while ((*str)[++i])
		if ((*str)[i] == '\n')
			(*str)[i] = ' ';
	(*str)[ft_strlen(*str) - 1] = 0;
}

void		realoc(char *str, char **tmp, int ret)
{
	char	*toto;

	str[ret] = 0;
	toto = malloc(ft_strlen(*tmp) + INPUT_SIZE);
	*toto = 0;
	if (*tmp)
		ft_strcat(toto, *tmp);
	ft_strcat(toto, str);
	free(*tmp);
	str[0] = 0;
	free(str);
	*tmp = toto;
}

void		bquote3(t_env *env, char *sav, int i, int k)
{
	char	*tmp;
	char	*buf;
	int		fd;
	int		ret;

	tmp = NULL;
	fd = open("/tmp/42sh_the_silence", O_RDONLY);
	unlink("/tmp/42sh_the_silence");
	buf = malloc(INPUT_SIZE);
	while ((ret = read(fd, buf, INPUT_SIZE - 1)))
		realoc(buf, &tmp, ret);
	close(fd);
	free(env->input);
	env->input = malloc(ft_strlen(tmp));
	env->input[0] = 0;
	if (tmp)
		remove_nl(&tmp);
	ft_strncat(env->input, sav, i);
	if (tmp)
		ft_strcat(env->input, tmp);
	ft_strcat(env->input, sav + k + i + 2);
}

void		bquote2(t_env *env, char *sav, int i, int k)
{
	pid_t	child;
	int		fd;

	ft_strncat(env->input, env->inp1 + i + 1, k);
	child = -1;
	fd = -1;
	if ((fd = open("/tmp/42sh_the_silence",
		O_WRONLY | O_CREAT | O_TRUNC, 0600)) == -1)
		error(-17, NULL, NULL);
	child = fork();
	if ((int)child == -1)
	{
		close(fd);
		error(-16, NULL, NULL);
	}
	else if ((int)child == 0)
	{
		dup2(fd, STDOUT_FILENO);
		parse(env, env->input);
		exit(EXIT_SUCCESS);
	}
	close(fd);
	wait(NULL);
	bquote3(env, sav, i, k);
}

void		verbquote(t_env *env)
{
	int i;
	int u;
	char *tmp;

	i = -1;
	u = 0;
	while (env->input[++i])
	{
		if (env->input[i] == '`')
			++u;
	}
	if (u % 2 == 1)
	{
		tmp = termcaps(ft_sprintf("bquote>"));
		env->input = ft_strjoin(env->input, " ");
		env->input = ft_strjoinfree(env->input, tmp, 2);
		verbquote(env);
	}
	return ;
}

void		bquote(t_env *env)
{
	int		i;
	int		k;
	char	*sav;

	i = -1;
	k = 0;
	verbquote(env);
	env->inp1 = ft_strdup(env->input);
	i = ft_strfind(env->inp1, '`');
	k = ft_strfind(env->inp1 + i + 1, '`');
	sav = ft_strdup(env->input);
	free(env->input);
	env->input = malloc(INPUT_SIZE);
	env->input[0] = 0;
	bquote2(env, sav, i, k);
}
