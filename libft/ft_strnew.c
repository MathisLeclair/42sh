/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 22:06:54 by mleclair          #+#    #+#             */
/*   Updated: 2016/11/05 18:04:25 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *str;

	str = (char *)malloc(size + 1);
	if (str == NULL)
		return (NULL);
	while (size)
	{
		str[size] = 0;
		size--;
	}
	str[0] = 0;
	return (str);
}
