/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 11:43:42 by mleclair          #+#    #+#             */
/*   Updated: 2017/02/23 13:25:31 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_remstr(char *str, int start, int end)
{
	char *buf;

	buf = malloc(ft_strlen(str));
	ft_strcat(buf, str + end);
	str[start] = 0;
	ft_strcat(str + start, buf);
	free(buf);
}
