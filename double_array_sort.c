/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_array_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 18:13:34 by mleclair          #+#    #+#             */
/*   Updated: 2017/02/06 18:39:47 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

void	double_array_sort(char **t)
{
	int		i;
	int		l;
	int		p;
	char	*tmp;

	l = 0;
	while (t[l])
		++l;
	p = 0;
	while (p != l - 1)
	{
		i = -1;
		p = 0;
		while (t[++i] && t[i + 1])
		{
			if (ft_strcmp(t[i], t[i + 1]) > 0)
			{
				tmp = t[i];
				t[i] = t[i + 1];
				t[i + 1] = tmp;
			}
			else
				++p;
		}
	}
}
