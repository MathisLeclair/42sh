/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 16:03:36 by mleclair          #+#    #+#             */
/*   Updated: 2017/02/11 16:23:13 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	history(t_env *env, char **split)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (split[i])
		if (split[i][0] == '-' && split[i][1] == 'c')
				env->history = 0;
	i = 0;
	while (env->history[i])
		++i;
	if (i == 0)
		ft_putstr("No history to display\n");
	print_split(env->history);
}
