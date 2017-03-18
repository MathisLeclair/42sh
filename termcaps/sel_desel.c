/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sel_desel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 13:35:14 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/18 18:51:08 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../42sh.h"

void	desel(t_var *var)
{
	int j;

	ft_putstr(tgetstr("ei", NULL));
	j = var->i;
	while (j > 0)
	{
		ft_putstr(tgetstr("le", NULL));
		--j;
	}
	ft_putstr(var->ret);
	var->selmode = 0;
	var->i = var->sovi;
	var->sovi = 0;
	var->selstart = -1;
	var->selend = -1;
	ft_putstr(tgetstr("rc", NULL));
	ft_putstr(tgetstr("im", NULL));
}

void	select_left(t_var *var)
{
	int i;

	ft_putstr(tgetstr("mr", NULL));
	write(1, var->ret + var->i, 1);
	ft_putstr(tgetstr("me", NULL));
	if ((var->i + var->lenprompt) % tgetnum("co") != 0)
		ft_putstr(tgetstr("le", NULL));
	var->i -= 1;
	if (var->i + var->lenprompt % tgetnum("co") == 0)
	{
		ft_putstr(tgetstr("up", NULL));
		i = -1;
		while (++i < tgetnum("co"))
			ft_putstr(tgetstr("nd", NULL));
	}
	else
		ft_putstr(tgetstr("le", NULL));
	var->selstart = var->i < var->selstart ? var->i : var->selstart;
}

void	select_right(t_var *var)
{
	ft_putstr(tgetstr("mr", NULL));
	write(1, var->ret + var->i, 1);
	ft_putstr(tgetstr("me", NULL));
	var->i += 1;
	var->selend = var->i > var->selend ? var->i : var->selend;
}

void	select_mode(t_var *var)
{
	var->selmode = 1;
	if (var->sovi == 0)
	{
		var->sovi = var->i;
		ft_putstr(tgetstr("sc", NULL));
	}
	ft_putstr(tgetstr("ei", NULL));
	ft_putstr(tgetstr("ms", NULL));
	read(0, var->buff, 3);
	var->selstart = var->selstart == -1 ? var->i : var->selstart;
	var->selend = var->selend == -1 ? var->i : var->selend;
	if (var->buff[0] == 68 && var->i == (int)ft_strlen(var->ret))
		left_arrow(var);
	else if (var->buff[0] == 68 && var->i > 0 &&
		var->i < (int)ft_strlen(var->ret))
		select_left(var);
	else if (var->buff[0] == 67 && var->i < (int)ft_strlen(var->ret))
		select_right(var);
	ft_putstr(tgetstr("im", NULL));
}
