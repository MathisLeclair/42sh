/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sconv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 19:31:16 by bfrochot          #+#    #+#             */
/*   Updated: 2017/01/13 12:18:57 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprintf.h"

int		ft_scount(int len)
{
	if (len < 8)
		return (0);
	else if (len < 12)
		return (1);
	else if (len < 17)
		return (2);
	else
		return (3);
}

int		splus(int i)
{
	if (i == 3)
		return (240);
	else if (i == 2)
		return (224);
	else if (i == 1)
		return (192);
	else
		return (0);
}

int		sconv(int nb, char *new)
{
	char	*nbr;
	int		len;
	int		k;
	int		i;

	nbr = ft_itoa_base(nb, 2, 0);
	len = ft_strlen(nbr);
	if (len < 22)
	{
		k = 6;
		i = ft_scount(len);
		while (i > 0)
		{
			new[i] = ft_atoi_base_printf(nbr + len - k, 2, 0) + 128;
			nbr[len - k] = 0;
			--i;
			k += 6;
		}
		new[0] = ft_atoi_base_printf(nbr, 2, 0) + splus(k / 6 - 1);
	}
	else
		return (-1);
	free(nbr);
	return (ft_scount(len) + 1);
}
