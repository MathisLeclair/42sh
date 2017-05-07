/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bs_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 17:31:16 by bfrochot          #+#    #+#             */
/*   Updated: 2017/03/17 17:31:39 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	bs_str(const char *str, int i, char c)
{
	char t;

	t = 0;
	if (str[i] != c)
		return (0);
	else
		while (i-- != 0 && str[i] == '\\')
			t = t == 0 ? 1 : 0;
	if (t == 1)
		return (0);
	return (1);
}
