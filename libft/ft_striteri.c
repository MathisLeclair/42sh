/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 10:16:27 by mleclair          #+#    #+#             */
/*   Updated: 2016/11/07 14:21:14 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int i;
	int y;

	if (!s || !f)
		return ;
	i = 0;
	y = ft_strlen(s);
	if (s != NULL)
	{
		while (i < y)
		{
			f(i, s);
			s++;
			i++;
		}
	}
}
