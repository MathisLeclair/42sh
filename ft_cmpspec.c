/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmpspec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 14:49:00 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/30 17:44:39 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		ft_cmpspec(char *input, char *tofind)
{
	size_t i;
	size_t k;

	i = 0;
	k = 0;
	while (input[i] == ' ' || input[i] == '\t')
		++i;
	while (tofind[k] && input[i + k] == tofind[k])
		++k;
	if (k == ft_strlen(tofind))
		return (1);
	return (0);
}

char	*ft_super_strstr(const char *str1, const char *str2)
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
		if (k == str2l && (str1[k + i] == 0 || str1[k + i] == '/'))
			return ((char *)str1 + i);
		i++;
	}
	return (NULL);
}
