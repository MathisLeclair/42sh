/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 13:33:41 by mleclair          #+#    #+#             */
/*   Updated: 2017/05/15 17:40:18 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../chell.h"

void	paste(t_var *var)
{
	int i;

	if (var->selend != -1)
		return ;
	ft_putstr(var->cpy);
	i = ft_strlen(var->cpy);
	while (i--)
		add_car(var, 1, var->cpy[i]);
	var->i += ft_strlen(var->cpy);
	i = var->i;
	if ((var->i + var->lenprompt) % tgetnum("co") - 1 == 0)
		ft_putstr_fd(tgetstr("sf", NULL), env()->fdout);
	ft_putstr(tgetstr("cd", NULL));
	ft_putstr(var->ret + var->i);
	var->i = ft_strlen(var->ret);
	var->lenligne = ft_strlen(var->ret) + var->lenprompt;
	while (var->i > i)
		left_arrow(var);
	var->selend = -1;
	var->selstart = -1;
}

void	copy(t_var *var, int p)
{
	int i;
	int j;

	i = 0;
	j = 0;
	var->cpy[0] = 0;
	while (i < var->selstart)
		++i;
	while (i <= var->selend && var->ret[i])
		var->cpy[j++] = var->ret[i++];
	var->cpy[j] = 0;
	if (p != 1 && var->cpy[0])
		desel(var);
}

void	cut(t_var *var)
{
	int i;

	copy(var, 1);
	if (var->selstart == -1 || var->selend == -1)
		return ;
	i = var->i;
	while (var->i != var->selstart)
	{
		var->selend--;
		backspace(var);
	}
	while (var->i != var->selend)
	{
		var->selend--;
		deleteu(var);
	}
	deleteu(var);
	var->selstart = -1;
	var->selend = -1;
	var->selmode = 0;
}
