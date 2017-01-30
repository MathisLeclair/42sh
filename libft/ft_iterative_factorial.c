/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 16:18:30 by mleclair          #+#    #+#             */
/*   Updated: 2016/11/03 15:11:25 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_iterative_factorial(int nb)
{
	int bite;

	if (nb > 0 && nb <= 12)
	{
		bite = nb;
		while (nb > 1)
		{
			bite = bite * (nb - 1);
			nb = nb - 1;
		}
	}
	else if (nb == 0)
		return (1);
	else
		return (0);
	return (bite);
}
