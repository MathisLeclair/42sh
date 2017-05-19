/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 15:52:16 by mleclair          #+#    #+#             */
/*   Updated: 2017/05/19 16:57:35 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

void	alias(t_env *env, char **split)
{
	int i;
	int u;

	i = 0;
	if (!split[1])
	{
		print_split(env->alias);
		return ;
	}
	while (split[++i])
	{
		u = 0;
		if (find_param(env->alias, split[i]) == -1 &&
			ft_strfind(split[i], '=') != -1)
			add_str_to_dstr(&env->alias, split[i]);
		else
		{
			if ((u = ft_strfind(split[i], '=')) == -1)
				return (error(-4, split[i], NULL));
			u = find_param(env->alias, split[i]);
			free(env->alias[u]);
			env->alias[u] = ft_strdup(split[i]);
		}
	}
}
