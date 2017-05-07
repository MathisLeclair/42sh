/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saddprint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 14:40:26 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/06 14:56:19 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprintf.h"

void		ft_smemlcat(char *dst, const char *src, int start, int end)
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

char		*sstrresize(char *s, int len, int k)
{
	char	*tmp;

	tmp = palloc(sizeof(char) * (k + len + 1));
	tmp[0] = 0;
	ft_strcat(tmp, s);
	free(s);
	return (tmp);
}

t_ssprintf	*machin(char *bu, int rt)
{
	t_ssprintf	*raturn;

	raturn = palloc(sizeof(t_ssprintf));
	raturn->buf = bu;
	raturn->ret = rt;
	return (raturn);
}

t_ssprintf	*ft_sprint(char *str, int k, int bool)
{
	static int	i;
	static char *buff;
	int			u;

	if (buff == NULL)
	{
		buff = palloc(1);
		buff[0] = 0;
	}
	if (bool == 1)
	{
		u = i + k;
		i = 0;
		return (machin(buff, u));
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
