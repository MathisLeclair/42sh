/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saddprint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 14:40:26 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/13 12:18:59 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprintf.h"

void	ft_smemlcat(char *dst, const char *src, int start, int end)
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

char	*sstrresize(char *s, int len, int k)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * (k + len + 1));
	tmp[0] = 0;
	ft_strcat(tmp, s);
	free(s);
	return (tmp);
}

char	*ft_sprint(char *str, int k, int bool)
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
		return (buff);
	}
	else
	{
		buff = sstrresize(buff, i, i + k);
		ft_smemlcat(buff, str, i, i + k + 1);
		i = i + k;
		buff[i] = 0;
	}
	return (NULL);
}
