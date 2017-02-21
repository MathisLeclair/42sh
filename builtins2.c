/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 16:03:36 by mleclair          #+#    #+#             */
/*   Updated: 2017/02/20 17:25:22 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	history(t_env *env, char **split)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (split[0] && split[1] && split[2])
	{
		error(-7, NULL, NULL);
		return ;
	}
	if (!(env->history))
	{
		error(-11, 0 , 0);
		return ;
	}
	i = 0;
	if (split[0] && split[1][0] == '-' && split[1][1] == 'c')
	{
		free_double_array(env->history);
		env->history = 0;
	}
	else if (isnumber(split[1][0]))
		i = ft_atoi(split[1]);
	print_split(env->history + i);
}
