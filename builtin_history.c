/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 11:45:37 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/22 19:33:17 by aridolfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

void	history3(char **split, t_env *env)
{
	int i;
	int j;

	i = ft_atoi(split[1]);
	j = 0;
	while (env->history[j])
		++j;
	while (i-- > 0)
		ft_printf("%s\n", env->history[j - i - 1]);
	retvalue_into_loc(env, 0);
}

void	history2(char **split, t_env *env)
{
	char	*tmp;

	tmp = palloc(INPUT_SIZE);
	*tmp = 0;
	if (split[1][1] == 'c')
	{
		free_double_array(env->history);
		ft_strcat(ft_strcat(tmp, env->ev[find_param(env->ev, "HOME")]
		+ 5), "/.42shistory");
		unlink(tmp);
		set_history();
		retvalue_into_loc(env, 0);
	}
	else
	{
		ft_putstr("Wrong argument, only -c accepted.\n");
		retvalue_into_loc(env, 1);
	}
	free(tmp);
}

void	history(t_env *env, char **split)
{
	if (split[0] && split[1] && split[2])
		error(-7, NULL, NULL);
	else if (!(env->history))
		error(-11, 0, 0);
	else if (split[1])
	{
		if (split[1][0] == '-')
			history2(split, env);
		else if (split[1] && ft_isdigit(split[1][0]))
			history3(split, env);
		else
		{
			ft_putstr("Is not a number.\n");
			retvalue_into_loc(env, 1);
		}
	}
	else
	{
		print_split(env->history);
		retvalue_into_loc(env, 0);
	}
}
