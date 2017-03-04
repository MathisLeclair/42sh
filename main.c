/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 16:16:33 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/04 14:01:51 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

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
	if (env()->i == 0 && getpid() != env()->job->pid &&
		env()->job->killable == 1)
	{
			reset(tvar());
			kill(env()->job->pid, SIGINT);
	}
	else if (env()->i == 1)
	{
		i = tvar()->i;
		while (tvar()->i != tvar()->inputlen)
			right_arrow(tvar());
		initvar(tvar(), 0);
		write(1, "\n", 1);
		ft_printf("\e[1;32m%C\e[0;m \e[1;36m%s \e[0m%s", L'✈', env()->dir, PROMPT);
	}
}

void	signblock(int i)
{
	sigset_t *set;

	set = malloc(sizeof(sigset_t));
	sigemptyset(set);
	sigaddset(set, SIGINT);
	if (i == 1)
		sigprocmask(SIG_BLOCK, set, NULL);
	else
		sigprocmask(SIG_UNBLOCK, set, NULL);
}

int		main(int ac, char **av, char **ev)
{
	t_env *envi;

	envi = env();
	set_env(env(), ev);
	signal(SIGINT, ft_sig);
	signal(SIGCONT, ft_sig);
	signal(SIGTSTP, retreive_ctrlz);
	(void)av;
	(void)ac;
	shlvl(env());
	jobctrl_init_shell();
	while (1)
	{
		if ((ft_read(env())) == 0)
			continue ;
		else
		{
			env_free(env());
			break ;
		}
	}
	ft_putstr("GOODBYE\n");
}
