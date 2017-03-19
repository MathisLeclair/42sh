/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 17:47:40 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/27 19:29:39 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

void	set_e3(t_env *e)
{
	e->job->status = NULL;
	e->job->stat = 0;
	e->job->next = NULL;
	e->job->prev = NULL;
	e->job->num = 0;
	e->boolthing = 0;
	e->job->killable = -1;
	e->lastret = 0;
	e->hash = NULL;
	e->bool1 = 0;
	e->bool2 = 0;
	e->bool3 = 0;
	e->fdout = dup(1);
	e->pid = getpid();
}

void	set_evloc2(t_env *e)
{
	struct stat		*buf;
	struct passwd	*truc;
	char			*tmp;

	buf = palloc(sizeof(struct stat));
	add_var_to_env(e->loc, "HISTFILE=/private/tmp/.42sh_history");
	add_var_to_env(e->loc, "HISTSIZE=500");
	add_var_to_env(e->loc, "PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	add_var_to_env(e, "?=0");
	stat("./.", buf);
	truc = getpwuid(buf->st_uid);
	tmp = ft_strjoinfree("LOGNAME=", truc->pw_name, 0);
	add_var_to_env(e->loc, tmp);
	free(tmp);
	double_array_sort(e->loc->ev);
	free(buf);
	e->redir = NULL;
	e->isoperand = 0;
	set_history();
	e->job = palloc(sizeof(t_job));
	e->job->name = "shell";
	e->job->pid = getpid();
	set_e3(e);
}

void	set_evloc(t_env *e)
{
	int		i;
	char	*tmp;

	e->loc = palloc(sizeof(t_env));
	i = 0;
	while (e->ev[i])
		++i;
	e->loc->ev = palloc(sizeof(char *) * i + 1);
	e->loc->ev[i] = 0;
	i = -1;
	while (e->ev[++i])
		e->loc->ev[i] = ft_strdup(e->ev[i]);
	tmp = ft_strjoinfree("UID=", ft_itoa(getpid()), 2);
	add_var_to_env(e->loc, tmp);
	free(tmp);
	tmp = ft_strjoinfree("PPID=", ft_itoa(getppid()), 2);
	add_var_to_env(e->loc, tmp);
	free(tmp);
	tmp = ft_strjoinfree("EUID=", ft_itoa(getpid()), 2);
	add_var_to_env(e->loc, tmp);
	free(tmp);
	tmp = ft_strjoinfree("COLUMNS=", ft_itoa(tgetnum("co")), 2);
	add_var_to_env(e->loc, tmp);
	free(tmp);
	set_evloc2(e);
}

void	set_oldpwd(t_env *env, char *str)
{
	char	oldpwd[INPUT_SIZE + 7];

	oldpwd[0] = 'O';
	oldpwd[1] = 'L';
	oldpwd[2] = 'D';
	oldpwd[3] = 'P';
	oldpwd[4] = 'W';
	oldpwd[5] = 'D';
	oldpwd[6] = '=';
	oldpwd[7] = '\0';
	ft_strcat(oldpwd, str + 4);
	add_var_to_env(env, oldpwd);
}

void	set_env(t_env *env, char **ev)
{
	size_t	i;
	char	pwd[INPUT_SIZE + 4];

	i = 0;
	env->i = 1;
	env->input = NULL;
	env->path = NULL;
	env->history = NULL;
	env->cond = NULL;
	while (ev[i])
		++i;
	env->ev = palloc(sizeof(char *) * (i + 1));
	if (env->ev == NULL)
		error(-666, NULL, NULL);
	env->ev[i] = 0;
	while (i--)
		env->ev[i] = ft_strdup(ev[i]);
	getpwd(pwd);
	if (find_param(env->ev, "PWD") == -1)
		add_var_to_env(env, pwd);
	i = ft_strlen(pwd);
	while (pwd[i] != '/' && pwd[i] != '=')
		--i;
	env->dir = ft_strdup((pwd[i + 1] == 0 ? 0 : 1) + pwd + i);
	env->savev = NULL;
	set_evloc(env);
}
