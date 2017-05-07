/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bs_eol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 15:52:12 by mleclair          #+#    #+#             */
/*   Updated: 2017/05/01 17:11:55 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

void	bs_eol(t_env *env)
{
	char	*tmp;
	int		i;

	if (bs_str(env->input, ft_strlen(env->input) - 1, '\\'))
	{
		tmp = termcaps(ft_sprintf(">"), 1, 0);
		env->input = ft_strjoinfree(env->input, tmp, 3);
		while (bs_str(env->input, ft_strlen(env->input) - 1, '\\'))
		{
			tmp = termcaps(ft_sprintf(">"), 1, 0);
			env->input = ft_strjoinfree(env->input, tmp, 3);
		}
		i = -1;
		while (env->input[++i])
			if (bs_str(env->input, i, '\\'))
				env->input[i] = '\n';
	}
}

int		bs_strstr(char *big, char *little)
{
	int i;
	int j;

	i = -1;
	while (++i < (int)ft_strlen(big) - (int)ft_strlen(little))
	{
		j = -1;
		while (++j != -1)
		{
			if (bs_str(big, i + j, little[j]) == 0)
				break ;
			if (j == (int)ft_strlen(little) - 1)
				return (i);
		}
	}
	return (-1);
}
