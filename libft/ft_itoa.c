/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 18:44:07 by mleclair          #+#    #+#             */
/*   Updated: 2016/11/05 19:45:04 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		i;
	int		a;
	int		neg;
	char	*str;

	i = 1;
	neg = (n < 0) ? 1 : 0;
	if (n > 0)
		n = n * -1;
	a = n;
	while ((a = a / 10) < 0)
		i++;
	str = (char *)malloc((sizeof(char) * i) + neg + 1);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, i + neg + 1);
	if (neg == 1)
		str[0] = '-';
	i -= 1 - neg;
	while (i-- >= neg)
	{
		str[i + 1] = (-(n % 10) + '0');
		n = n / 10;
	}
	return (str);
}
