/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_backspace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 13:39:21 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/18 13:41:52 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../42sh.h"

void	deleteu(t_var *var)
{
	int j;

	if (var->del == 1)
		read(0, NULL, 3);
	if (var->del == 1)
		var->del = 0;
	rem_car(var);
	ft_putstr(tgetstr("cd", NULL));
	ft_putstr(var->ret + var->i);
	j = ft_strlen(var->ret + var->i);
	while (j-- > 0)
		if ((var->lenligne + j) % tgetnum("co") == 0 &&
			(var->inputlen + var->lenprompt) % tgetnum("co") == 2)
			;
		else
			ft_putstr(tgetstr("le", NULL));
	left_arrow(var);
	right_arrow(var);
	--var->inputlen;
}

void	backspace(t_var *var)
{
	if (var->i > 0)
	{
		left_arrow(var);
		deleteu(var);
	}
}
