/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 17:00:31 by mleclair          #+#    #+#             */
/*   Updated: 2016/11/05 19:16:47 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t i;
	size_t dwa;

	i = 0;
	dwa = ft_strlen(src);
	while (src[i] && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	if (dwa < len)
		ft_bzero(&dst[i], len - i);
	return (dst);
}
