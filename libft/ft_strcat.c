/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 17:23:43 by mleclair          #+#    #+#             */
/*   Updated: 2017/02/23 13:40:50 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int i;
	int size_s1;
	int sizs_s2;

	size_s1 = ft_strlen(s1);
	sizs_s2 = ft_strlen(s2);
	i = 0;
	while (i <= sizs_s2)
	{
		s1[size_s1 + i] = s2[i];
		i++;
	}
	s1[size_s1 + 1] = 0;
	return (s1);
}
