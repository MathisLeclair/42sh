/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 22:11:59 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/18 16:52:43 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strdel2(char **as, char **av)
{
	if (as == NULL)
		return ;
	free(*as);
	*as = NULL;
	if (av == NULL)
		return ;
	free(*av);
	*av = NULL;
}
