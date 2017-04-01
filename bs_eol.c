/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bs_eol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 15:52:12 by mleclair          #+#    #+#             */
/*   Updated: 2017/04/01 16:40:31 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

void	bs_eol(t_env *env)
{
	char	*tmp;
	int		i;

	if (bs_str(env->input, ft_strlen(env->input) - 1, '\\'))
	{
		tmp = termcaps(ft_sprintf(">"), 1);
		env->input = ft_strjoinfree(env->input, tmp, 3);
		while (bs_str(env->input, ft_strlen(env->input) - 1, '\\'))
		{
			tmp = termcaps(ft_sprintf(">"), 1);
			env->input = ft_strjoinfree(env->input, tmp, 3);
		}
		i = -1;
		while (env->input[++i])
			if (bs_str(env->input, i, '\\'))
				env->input[i] = '\n';
	}
}
