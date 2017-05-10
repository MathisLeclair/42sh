/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 16:16:33 by mleclair          #+#    #+#             */
/*   Updated: 2017/05/10 17:22:29 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

void	shlvl(t_env *env)
{
	char	*tmp;
	char	*tmp2;
	int		i;
	int		t;

	i = find_param(env->ev, "SHLVL");
	if (i > -1)
		t = ft_atoi(env->ev[i] + 6);
	else
		t = 0;
	++t;
	tmp2 = ft_itoa(t);
	tmp = ft_strjoin("SHLVL=", tmp2);
	add_var_to_env(env, tmp);
	free(tmp);
	free(tmp2);
}

t_env	*env(void)
{
	static t_env	*env = NULL;

	if (env == NULL)
		env = palloc(sizeof(t_env));
	return (env);
}

void	ft_sig(int i)
{
	if (env()->boolthing != 0)
	{
		kill(env()->boolthing, SIGKILL);
		env()->boolthing = 0;
	}
	else if (env()->booljob == 0 &&
	getpid() == ft_atoi(env()->loc->ev[find_param(env()->loc->ev, "UID=")] + 4))
	{
		i = tvar()->i;
		free_double_array(tvar()->his);
		free(tvar()->arr);
		initvar(tvar(), 0, 10, 0);
		write(1, "\n", 1);
		ft_printf("\e[1;32m%C\e[0;m \e[1;36m%s \e[0m%s", L'✈', env()->dir,
		PROMPT);
		ft_putstr(tgetstr("cd", NULL));
		env()->i = 0;
		env()->bool1 = 1;
		if (env()->cond != NULL)
			destroy_condition(env()->cond);
		env()->cond = NULL;
	}
}

void	signblock(int i)
{
	sigset_t *set;

	set = palloc(sizeof(sigset_t));
	sigemptyset(set);
	sigaddset(set, SIGTSTP);
	if (i == 1)
		sigprocmask(SIG_BLOCK, set, NULL);
	else
		sigprocmask(SIG_UNBLOCK, set, NULL);
	free(set);
}

int		main(int ac, char **av, char **ev)
{
	int i;

	i = 0;
	while(av[++i])
		if (ft_strstr(av[i], "/dev"))
			return (0);
	set_env(env(), ev);
	signal(SIGINT, ft_sig);
	signal(SIGCONT, ft_sig);
	signblock(1);
	shlvl(env());
	handle_file(ac, av, env());
	env()->name = ft_strdup(av[0]);
	while (1)
		if ((ft_read(env(), NULL, -1, 0)) == 0)
			continue ;
		else
		{
			env_free(env());
			break ;
		}
	ft_putstr("GOODBYE\n");
}
