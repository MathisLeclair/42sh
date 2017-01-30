/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 12:15:45 by mleclair          #+#    #+#             */
/*   Updated: 2016/12/12 15:29:56 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_findmod(int i, char *str, int k)
{
	if (i > 1 && str[i - 2] == 'l')
	{
		k = 1;
		if (i > 2 && str[i - 3] == 'l')
			k = 2;
	}
	else if (i > 1 && str[i - 2] == 'h')
	{
		k = -1;
		if (i > 2 && str[i - 3] == 'h')
			k = -2;
	}
	else if (i > 1 && str[i - 2] == 'j')
		k = 5;
	else if (i > 1 && str[i - 2] == 'z')
		k = 6;
	return (k);
}

int			transfo(char *str, va_list ap, int j, char **machin)
{
	int		i;
	int		k;
	char	*pos[2];

	pos[0] = "sdouxcip";
	pos[1] = "SDOUXC\0\0";
	i = ft_strlen(str);
	while (str[i - 1] != pos[0][j] && str[i - 1] != pos[1][j] && pos[0][j])
		++j;
	k = ft_findmod(i, str, 0);
	i = ft_type()[j](ap, k, str[i - 1], machin);
	if (i == -1)
		return (-1);
	i = ft_opts(str, machin, i);
	ft_print(*machin, i, 0);
	free(*machin);
	return (0);
}

char		*ft_findpara(const char **str)
{
	char	*res;
	int		j;
	int		i;

	(*str) += 1;
	j = 0;
	while ((*str)[j] && (ft_isokay((*str)[j])))
		++j;
	if ((*str)[j])
		j++;
	res = malloc(j + 1);
	i = 0;
	while (i < j)
	{
		res[i] = **str;
		++i;
		++(*str);
	}
	res[i] = '\0';
	return (res);
}

const char	*troncage(const char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '%')
		i++;
	ft_print((char *)str, i, 0);
	return (str + i);
}

int			ft_printf(const char *str, ...)
{
	va_list	ap;
	char	*amod;
	char	*machin;
	int		i;

	machin = NULL;
	va_start(ap, str);
	while (str[0])
	{
		str = troncage(str);
		if (str[0] == 0)
			break ;
		amod = ft_findpara(&str);
		if (*amod != 0)
		{
			i = transfo(amod, ap, 0, &machin);
			free(amod);
		}
	}
	if (i == -1)
		return (-1);
	return (ft_print(0, 0, 1));
}
