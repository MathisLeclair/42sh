/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 21:39:38 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/20 16:01:16 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int i;
	int tu;

	tu = ft_strlen(s);
	i = 0;
	while (!bs_str(s, i, c) && i < tu)
		i++;
	if (s[i] == c)
		return (&((char *)s)[i]);
	else
		return (0);
}
