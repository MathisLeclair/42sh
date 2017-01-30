/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 13:31:47 by mleclair          #+#    #+#             */
/*   Updated: 2016/12/12 15:29:41 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_plus2(char **str, int k, char *tmp)
{
	(*str)[k] = '\0';
	tmp = malloc(k + 2);
	tmp = ft_memset(tmp, '\0', 2);
	ft_strcat(tmp + 1, *str);
	if ((*str)[ft_strlen(*str) - 1] == ' ' && --k)
		tmp[k + 1] = 0;
	tmp[0] = '+';
	free(*str);
	*str = tmp;
	return (k + 1);
}

int		ft_plus(int k, int i, int bool, char **str)
{
	char *tmp;

	i = bool;
	if ((*str)[0] == '0' && (*str)[1] != 0 && bool == 0)
		(*str)[0] = '+';
	if (k == 1 && *str[0] >= '0' && *str[0] <= '9')
	{
		tmp = malloc(3);
		tmp[0] = '+';
		tmp[1] = *str[0];
		tmp[2] = '\0';
		free(*str);
		*str = tmp;
		return (2);
	}
	if (ft_isdigit((*str)[0]))
	{
		tmp = 0;
		return (ft_plus2(str, k, tmp));
	}
	return (k);
}

int		ft_moncul2(char *tmp, size_t k, char **str, int i)
{
	tmp[0] = ' ';
	k = -1;
	while (str[++k])
		tmp[k + 1] = (*str)[k];
	tmp[k + 1] = 0;
	free(*str);
	*str = tmp;
	return (i + 1);
}

int		ft_moncul(char *opt, char **str, int i)
{
	size_t	k;
	char	*tmp;

	tmp = malloc(i + 2);
	if (opt[ft_strlen(opt) - 1] == 'd' || opt[ft_strlen(opt) - 1] == 'i')
	{
		k = 0;
		while (ft_isdigit((*str)[k]))
			++k;
		if ((*str)[ft_strlen(*str) - 1] == ' ' || k == ft_strlen(*str))
		{
			if ((*str)[0] == '0' && k == ft_strlen(*str))
			{
				(*str)[0] = ' ';
				return (i);
			}
			else
				return (ft_moncul2(tmp, k, str, i));
		}
	}
	return (i);
}
