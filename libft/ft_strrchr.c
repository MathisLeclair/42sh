/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 22:04:42 by mleclair          #+#    #+#             */
/*   Updated: 2016/11/06 10:39:12 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int i;

	i = ft_strlen(s);
	if (i == 0)
		return (NULL);
	while (s[i] != (char)c && s[i - 1])
		i--;
	if (s[i] == c)
		return (&((char *)s)[i]);
	else
		return (0);
}
