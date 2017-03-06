/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_prop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 18:56:27 by bfrochot          #+#    #+#             */
/*   Updated: 2017/03/06 16:07:28 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	auto_prop(t_var *var)
{
	int		i;
	int		j;
	int		k;
	size_t	l;
	size_t	max;
	size_t	len;

	i = -1;
	max = 0;
	while (var->ac[++i])
		max = ft_strlen(var->ac[i]) > max ? ft_strlen(var->ac[i]) : max;
	j = tgetnum("co") / (max + 1);
	i = -1;
	l = 0;
	while (var->ac[++i])
	{
		len = ft_strlen(var->ac[i]);
		write(1, var->ac[i], len);
		var->i += len;
		var->lenligne += 1;
		k = 0;
		while (len + k++ < max + 1)
			var->i += 1;
		write(1, "                                                                                            ", k - 1);
		l += max + 1;
		if (l - tgetnum("co") > -max)
		{
			k = 0;
			while (l++ < (size_t)tgetnum("co"))
			{
				write(1, " ", 1);
				var->i += 1;
			}
			l = 0;
		}
	}
}
