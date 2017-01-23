/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spart1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 11:52:29 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/13 12:18:47 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprintf.h"

int		ft_sc(va_list ap, int i, char c, char **str)
{
	wint_t t;

	if (c == 'C' || i == 1)
	{
		*str = malloc(4);
		sconv(t = va_arg(ap, wint_t), *str);
		if (t <= 0x7F)
			return (1);
		else if (t <= 0x7FF)
			return (2);
		else if (t <= 0xFFFF)
			return (3);
		else if (t <= 0x10FFFF)
			return (4);
		return (-1);
	}
	*str = malloc(2);
	*str[0] = (char)va_arg(ap, int);
	(*str)[1] = '\0';
	return (1);
}

int		ft_so(va_list ap, int i, char c, char **str)
{
	uintmax_t	d;
	char		*tmp;

	if (i == 1 || c == 'O')
		d = va_arg(ap, long unsigned int);
	else if (i == 2)
		d = va_arg(ap, unsigned long long int);
	else if (i == -2)
		d = (unsigned char)va_arg(ap, int);
	else if (i == 5)
		d = va_arg(ap, uintmax_t);
	else if (i == -1)
		d = (unsigned short)va_arg(ap, int);
	else if (i == 6)
		d = va_arg(ap, size_t);
	else
		d = va_arg(ap, unsigned int);
	tmp = ft_itoa_base(d, 8, 0);
	*str = malloc(ft_strlen(tmp));
	**str = 0;
	ft_strcat(*str, tmp);
	free(tmp);
	return (ft_strlen(*str));
}

int		ft_su(va_list ap, int i, char c, char **str)
{
	uintmax_t	d;
	char		*tmp;

	if (i == 1 || c == 'U')
		d = va_arg(ap, unsigned long int);
	else if (i == 2)
		d = va_arg(ap, unsigned long long int);
	else if (i == 5)
		d = va_arg(ap, uintmax_t);
	else if (i == 6)
		d = va_arg(ap, size_t);
	else if (i == -2)
		d = (unsigned char)va_arg(ap, int);
	else
		d = va_arg(ap, unsigned int);
	tmp = ft_itoa_base(d, 10, 0);
	*str = malloc(ft_strlen(tmp));
	**str = 0;
	ft_strcat(*str, tmp);
	free(tmp);
	return (ft_strlen(*str));
}
