/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addprint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 14:40:26 by mleclair          #+#    #+#             */
/*   Updated: 2016/12/12 15:31:15 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_memlcat(char *dst, const char *src, int start, int end)
{
	int i;

	i = 0;
	while (start < end)
	{
		dst[start] = src[i];
		++i;
		++start;
	}
}

char	*strresize(char *s, int len, int k)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * (k + len + 1));
	tmp[0] = 0;
	ft_strcat(tmp, s);
	free(s);
	return (tmp);
}

int		ft_print(char *str, int k, int bool)
{
	static int	i;
	static char *buff;
	int			u;

	if (buff == NULL)
	{
		buff = malloc(1);
		buff[0] = 0;
	}
	if (bool == 1)
	{
		u = i + k;
		write(1, buff, u);
		ft_bzero(buff, u);
		i = 0;
		return (u);
	}
	else
	{
		buff = strresize(buff, i, i + k);
		ft_memlcat(buff, str, i, i + k + 1);
		i = i + k;
		buff[i] = 0;
	}
	return (i);
}
