/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 13:42:58 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/18 16:45:39 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../chell.h"

void	home(t_var *var)
{
	while (var->i > 0)
		left_arrow(var);
}

void	end(t_var *var)
{
	int lenret;

	lenret = ft_strlen(var->ret);
	while (var->i < lenret)
		right_arrow(var);
}
