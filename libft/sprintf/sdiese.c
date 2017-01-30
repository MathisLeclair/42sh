/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdiese.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 18:53:34 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/13 12:18:54 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprintf.h"

char	*ft_s2long(int i, char **str)
{
	char *tmp;

	tmp = malloc(i + 3);
	tmp[0] = '0';
	tmp[1] = 'x';
	tmp[2] = '\0';
	ft_strcat(tmp, *str);
	return (tmp);
}

char	*ft_s2long2(int k, int i, char **str)
{
	char *tmp;

	tmp = NULL;
	if (k == 1)
		**str = '0';
	else if (k == 0)
	{
		tmp = malloc(i + 2);
		tmp[0] = '0';
		tmp[1] = '\0';
		ft_strcat(tmp, *str);
		if (tmp[i] == ' ')
			tmp[i] = 0;
	}
	else if ((*str)[0] == ' ')
		(*str)[k - 1] = '0';
	return (tmp);
}

int		ft_shastag(int k, int i, int bool, char **str)
{
	char *tmp;

	tmp = NULL;
	while ((*str)[k] == ' ' || (*str)[k] == '0')
		++k;
	if (bool == 1)
		tmp = ft_s2long(i, str);
	else
		tmp = ft_s2long2(k, i, str);
	if (tmp != NULL)
		free(*str);
	if (tmp != NULL)
		*str = tmp;
	return (ft_strlen(*str));
}
