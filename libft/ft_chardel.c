/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chardel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aridolfi <aridolfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 13:44:25 by aridolfi          #+#    #+#             */
/*   Updated: 2017/02/23 14:31:35 by aridolfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_chardel(char **s, char c)
{
	int		tmp;
	int		del;
	int		i;

	if (!c)
		return ;
	del = 0;
	i = -1;
	while (s[++i])
		if (s[i] == c)
		{
			s[i] = '\0';
			size++;
		}
	i = -1;
	while (del && s[++i])
	{
		tmp = i;
		while (s[i] == '\0')
			i++;
		s[tmp] = s[i];
		del--;
		i = tmp;
	}
}
