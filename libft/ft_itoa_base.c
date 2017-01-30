/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 10:58:50 by exam              #+#    #+#             */
/*   Updated: 2016/11/28 18:21:38 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		ft_power(long long int value, int power)
{
	if (power == 0)
		return (1);
	while (power > 1)
		value *= value;
	return (value);
}

char	*sol(int i, char neg, uintmax_t save, int base)
{
	char	*str;
	char	*slo;
	int		j;

	str = "0123456789ABCDEF";
	slo = malloc(i + neg + 1);
	slo[i + neg] = '\0';
	if (neg == 1)
		slo[0] = '-';
	if (save == 0)
		slo[0] = '0';
	while (save > 0)
	{
		j = (save % base);
		slo[i + neg - 1] = str[j];
		save = save / base;
		i--;
	}
	return (slo);
}

char	*ft_itoa_base(uintmax_t value, int base, char neg)
{
	int				i;
	uintmax_t		save;

	i = 0;
	if (value == 0)
		i++;
	save = value;
	while (value > 0)
	{
		value = value / base;
		i++;
	}
	return (sol(i, neg, save, base));
}
