/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 15:10:00 by mleclair          #+#    #+#             */
/*   Updated: 2016/11/05 17:55:52 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int i, int fd)
{
	if (i >= 0)
		i *= -1;
	else
		ft_putchar_fd('-', fd);
	if (i < -9)
		ft_putnbr_fd(-(i / 10), fd);
	ft_putchar_fd(-(i % 10) + '0', fd);
}
