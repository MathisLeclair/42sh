/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 11:43:42 by mleclair          #+#    #+#             */
/*   Updated: 2017/02/23 12:02:15 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_remstr(char *str, int start, int end)
{
	char *buf;

	buf = malloc(ft_strlen(str));
	ft_strncat(buf, str, start);
	printf("buf1= %s#\n", buf);
	ft_strcat(buf, str + end);
	printf("buf2= %s# str+end = %s\n", buf, str + end);
	free(str);
	str = buf;
}
