/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 13:33:41 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/18 13:34:48 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../42sh.h"

void	paste(t_var *var)
{
	int i;

	ft_putstr(var->cpy);
	i = ft_strlen(var->cpy);
	while (i--)
		add_car(var, 1, var->cpy[i]);
	var->i += ft_strlen(var->cpy);
	i = var->i;
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
	while (i <= var->selend)
		var->cpy[j++] = var->ret[i++];
	var->cpy[i + 1] = 0;
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
