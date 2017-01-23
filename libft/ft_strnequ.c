/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 10:35:52 by mleclair          #+#    #+#             */
/*   Updated: 2016/11/06 11:04:50 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t j;

	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (j < n)
	{
		if (s1[j] != s2[j])
			return (0);
		j++;
	}
	return (1);
}
