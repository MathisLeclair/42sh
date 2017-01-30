/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 18:41:52 by mleclair          #+#    #+#             */
/*   Updated: 2016/11/06 13:34:27 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str1, const char *str2)
{
	int i;
	int str2l;
	int k;
	int sv;

	i = 0;
	str2l = ft_strlen(str2);
	if (ft_strlen(str2) == 0)
		return ((char *)str1);
	while (str1[i])
	{
		k = 0;
		sv = i;
		while (str1[sv] == str2[k] && str2[k] != 0)
		{
			k++;
			sv++;
		}
		if (k == str2l)
			return ((char *)str1 + i);
		i++;
	}
	return (NULL);
}
