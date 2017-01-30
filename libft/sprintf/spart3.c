/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spart3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 16:12:21 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/13 12:18:41 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprintf.h"

int		ft_swstrlen(wchar_t *str)
{
	wchar_t *tmp;

	tmp = str;
	while (*tmp != 0)
		tmp++;
	return (tmp - str);
}

int		ft_ss2(char **str, va_list ap)
{
	int		u;
	int		i;
	int		k;
	wchar_t *t;

	u = 0;
	i = -1;
	t = va_arg(ap, wchar_t *);
	if (t == NULL)
	{
		*str = malloc(7);
		**str = 0;
		ft_strcat(*str, "(null)");
		return (6);
	}
	*str = malloc((ft_swstrlen(t) + 1) * sizeof(wchar_t));
	ft_bzero(*str, (ft_swstrlen(t) + 1));
	while (t[++i])
	{
		k = sconv(t[i], *str + u);
		u += k;
	}
	return (u);
}

int		ft_s(va_list ap, int i, char c, char **str)
{
	char	*tmp;

	if (c == 'S' || i == 1)
		return (ft_ss2(str, ap));
	tmp = va_arg(ap, char *);
	tmp == NULL ? tmp = "(null)" : 0;
	*str = malloc(ft_strlen(tmp) + 1);
	i = -1;
	while (tmp[++i])
		(*str)[i] = tmp[i];
	(*str)[i] = '\0';
	return (i);
}
