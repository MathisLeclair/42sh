/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sopts1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 17:16:29 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/13 12:18:52 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprintf.h"

int		ft_sprecspe(char **str, char c, int k)
{
	if (((*str)[0] == 0 && c == 'c'))
		return (1);
	if ((*str)[2] == '0' && (*str)[3] == 0 && c == 'p' && k == 0)
	{
		(*str)[2] = 0;
		return (2);
	}
	if ((*str)[0] == '0' && (*str)[1] == 0 && k == 0 && c != 'c')
	{
		**str = 0;
		return (0);
	}
	return (-1);
}

int		ft_sprec(int i, int k, char c, char **str)
{
	char	neg;
	char	*tmp;
	int		j;

	if ((j = ft_sprecspe(str, c, k)) > -1)
		return (j);
	neg = ((*str)[0] == '-' ? 1 : 0);
	if (i >= k + neg)
		return (i);
	else
	{
		tmp = malloc(k + neg + 1);
		ft_memset(tmp, '0', k + neg - 1);
		while (i >= neg)
			tmp[k-- + neg] = (*str)[i--];
		if (neg == 1)
			tmp[0] = '-';
		free(*str);
		*str = tmp;
		return (ft_strlen(tmp));
	}
}

int		ft_snumber2(char *tmp, int i, int k, char **str)
{
	ft_smemlcat(tmp + i - k + 2, *str + 2, 0, k - 2);
	tmp[1] = 'x';
	free(*str);
	*str = tmp;
	return (i);
}

int		ft_snumber(int k, int i, int bool, char **str)
{
	char	*tmp;

	if (i < 0)
		i *= -1;
	if (k < i)
		tmp = malloc(i + 1);
	else
		return (k);
	tmp = ft_memset(tmp, (bool == 1 ? '0' : ' '), i);
	if ((*str)[1] == 'x' && (*str)[0] == '0' && bool == 1)
	{
		return (ft_snumber2(tmp, i, k, str));
	}
	tmp[i - k] = '\0';
	ft_smemlcat(tmp + i - k, *str, 0, k);
	k = -1;
	while (k++ < i)
		if ((tmp[k] == '-' || tmp[k] == '+') && k > 0 && tmp[k - 1] == '0')
		{
			tmp[0] = tmp[k];
			tmp[k] = '0';
		}
	free(*str);
	*str = tmp;
	return (i);
}

int		ft_sminus(int k, int i, int bool, char **str)
{
	char *tmp;

	i = 0;
	if ((*str)[i] == '-')
		++i;
	while ((*str)[i] == ' ' || ((*str)[i] == '0' && bool == -1))
		++i;
	if ((*str)[i] == 0 && (*str)[i - 1] == '0')
	{
		(*str)[i - 1] = ' ';
		(*str)[0] = '0';
		return (k);
	}
	tmp = malloc(k + 1);
	if ((*str)[0] == '-')
		tmp[0] = '-';
	tmp[((*str)[0] == '-' ? 1 : 0)] = 0;
	ft_strcat(tmp, *str + i + ((*str)[i] == 'x' ? -1 : 0));
	free(*str);
	*str = tmp;
	bool = k;
	while (i-- > ((*str)[1] == 'x' ? 0 : -1))
		(*str)[k--] = ' ';
	return (bool);
}
