/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bquote2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 11:58:01 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/22 12:06:22 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

int			ver_sub_2(t_env *env)
{
	int i;
	int u;

	i = -1;
	u = 0;
	while (env->input[++i])
	{
		if (env->input[i] == '(')
			u += 1;
		else if (env->input[i] == ')')
			u -= 1;
	}
	if (u != 0)
	{
		error(-15, NULL, NULL);
		return (-1);
	}
	return (0);
}
