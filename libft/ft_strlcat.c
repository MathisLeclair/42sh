/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 19:08:02 by mleclair          #+#    #+#             */
/*   Updated: 2016/11/06 10:31:15 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t i;
	size_t size_s1;

	i = 0;
	while (dst[i] && i < n)
		i++;
	size_s1 = i;
	while (src[i - size_s1] && i < n - 1)
	{
		dst[i] = src[i - size_s1];
		i++;
	}
	if (size_s1 < n)
		dst[i] = 0;
	return (size_s1 + ft_strlen(src));
}
