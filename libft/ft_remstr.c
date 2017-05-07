/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 11:43:42 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/22 13:51:02 by aridolfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_remstr(char *str, int start, int end)
{
	char *tmp;

	tmp = ft_strdup(str + end);
	str[start] = 0;
	ft_strcat(str, tmp);
	free(tmp);
}
