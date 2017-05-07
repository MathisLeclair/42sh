/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stableaupointeursurfonction.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 11:32:47 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/07 16:23:07 by aridolfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprintf.h"

t_fun	*ft_stype(void)
{
	static t_fun *fcts = NULL;

	if (fcts == NULL)
	{
		fcts = palloc(sizeof(t_fun *) * 14);
		fcts[0] = ft_s;
		fcts[1] = ft_d;
		fcts[2] = ft_o;
		fcts[3] = ft_u;
		fcts[4] = ft_x;
		fcts[5] = ft_c;
		fcts[6] = ft_i;
		fcts[7] = ft_p;
		fcts[8] = ft_israndom;
	}
	return (fcts);
}
