/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 10:58:50 by exam              #+#    #+#             */
/*   Updated: 2017/03/06 18:19:50 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(uintmax_t value, int base, char neg)
{
	int			i;
	uintmax_t	save;
	char		*str;
	char		*slo;

	i = 0;
	if (value == 0)
		i++;
	save = value;
	while (value > 0 && ++i)
		value = value / base;
	str = "0123456789ABCDEF";
	slo = malloc(i + neg + 1);
	slo[i + neg] = '\0';
	if (neg == 1)
		slo[0] = '-';
	if (save == 0)
		slo[0] = '0';
	while (i + neg && i--)
	{
		slo[i + neg] = str[save % base];
		save = save / base;
	}
	return (slo);
}
