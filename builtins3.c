/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 15:47:09 by bfrochot          #+#    #+#             */
/*   Updated: 2017/03/11 15:52:56 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	builtin_hash(t_env *env, char **split)
{
	int i;

	i = -1;
	while (env->hash && env->hash[++i])
		ft_printf("%s\n", env->hash[i]);
	(void)split;
}
