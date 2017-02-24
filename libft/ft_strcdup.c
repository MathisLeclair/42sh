/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 16:47:00 by mleclair          #+#    #+#             */
/*   Updated: 2017/02/24 14:43:34 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcdup(const char *src, int k)
{
	char	*cpy;
	int		i;

	i = 0;
	cpy = (char *)malloc(k + 1);
	if (cpy == NULL)
		return (NULL);
	while (src[i] && i < k)
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
