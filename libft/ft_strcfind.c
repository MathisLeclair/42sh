/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcfind.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 12:20:21 by aridolfi          #+#    #+#             */
/*   Updated: 2017/03/17 17:41:21 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcfind(const char *s, int c)
{
	int		i;

	i = ft_strlen(s);
	while (!bs_str(s, i, c) && i > 0)
		i--;
	return (s[i] == c ? i : -1);
}
