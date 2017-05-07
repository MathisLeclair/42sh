/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 18:11:27 by bfrochot          #+#    #+#             */
/*   Updated: 2017/03/06 18:11:55 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_power(long long int value, int power)
{
	if (power == 0)
		return (1);
	while (power > 1)
		value *= value;
	return (value);
}
