/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insertstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aridolfi <aridolfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 14:08:58 by aridolfi          #+#    #+#             */
/*   Updated: 2017/03/31 15:16:24 by aridolfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_insertstr(char **src, char *str, size_t n)
{
	char	*new;
	size_t	i;

	i = 0;
	new = ft_strnew(ft_strlen(*src) + ft_strlen(str));
	ft_strcat(new, ft_strsub(*src, 0, n + 1));
	ft_strcat(new, str);
	ft_strcat(new, *src + (n + 1));
	*src = new;
}
