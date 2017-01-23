/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:07:01 by mleclair          #+#    #+#             */
/*   Updated: 2016/11/07 12:15:06 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t num)
{
	size_t	i;
	char	*savdst;
	char	*savsrc;

	savsrc = (char *)src;
	savdst = dst;
	i = 0;
	while (i < num)
	{
		savdst[i] = savsrc[i];
		i++;
	}
	return (dst);
}
