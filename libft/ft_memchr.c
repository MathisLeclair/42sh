/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:46:30 by mleclair          #+#    #+#             */
/*   Updated: 2016/11/05 18:21:31 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*truc;

	truc = (unsigned char *)s;
	i = 0;
	while (n--)
	{
		if (truc[i] == (unsigned char)c)
			return (&truc[i]);
		i++;
	}
	return (NULL);
}
