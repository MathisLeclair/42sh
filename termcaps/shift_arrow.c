/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_arrow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 13:32:34 by mleclair          #+#    #+#             */
/*   Updated: 2017/04/17 19:06:23 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../chell.h"

void	shift_arrow_l(t_var *var)
{
	if (!var->ret[var->i] && var->i != 0)
		left_arrow(var);
	while ((var->ret[var->i] == ' ' || var->ret[var->i] == '\t') && var->i > 0)
		left_arrow(var);
	while (var->i > 0 && var->ret[var->i] && var->ret[var->i] != ' '
		&& var->ret[var->i] != '\t')
		left_arrow(var);
}

void	shift_arrow_r(t_var *var)
{
	if (!var->ret[var->i] && var->i != 0)
		return ;
	while (var->ret[var->i] == ' ' || var->ret[var->i] == '\t')
		right_arrow(var);
	while (var->i >= 0 && var->ret[var->i] && var->ret[var->i] != ' '
		&& var->ret[var->i] != '\t')
		right_arrow(var);
}

void	shift_up(t_var *var)
{
	int i;

	i = -1;
	while (++i < tgetnum("co") && var->i > 0)
		left_arrow(var);
}

void	shift_down(t_var *var)
{
	int i;

	i = -1;
	while (++i < tgetnum("co"))
		right_arrow(var);
}
