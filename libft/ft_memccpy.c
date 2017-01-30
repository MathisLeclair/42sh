/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:09:23 by mleclair          #+#    #+#             */
/*   Updated: 2016/11/05 16:38:13 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t num)
{
	size_t i;

	i = 0;
	while (i < num)
	{
		if (((unsigned char *)src)[i] == (unsigned char)c)
		{
			((unsigned char *)dst)[i] = ((unsigned char*)src)[i];
			return (&dst[i + 1]);
		}
		((unsigned char *)dst)[i] = ((unsigned char*)src)[i];
		i++;
	}
	return (NULL);
}
