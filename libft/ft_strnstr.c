/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 15:19:56 by mleclair          #+#    #+#             */
/*   Updated: 2016/11/06 10:41:30 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *str1, const char *str2, size_t len)
{
	size_t	i;
	int		str2l;
	int		k;
	size_t	sv;

	i = 0;
	str2l = ft_strlen(str2);
	if (str2l == 0)
		return (str1);
	while (str1[i] && i < len)
	{
		k = 0;
		sv = i;
		while (str1[sv] == str2[k] && str2[k] != 0 && sv < len)
		{
			k++;
			sv++;
		}
		if (k == str2l)
			return (str1 + i);
		i++;
	}
	return (NULL);
}
