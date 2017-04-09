/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 14:59:59 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/29 18:59:25 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../chell.h"

void	touch6(t_var *var)
{
	add_car(var, 0, 0);
	++var->i;
	++var->lenligne;
}

void	touch5(t_var *var)
{
	int j;

	if (var->buff[0] == 4 && ft_strlen(var->ret) == 0)
	{
		reset(var);
		error(-6, NULL, NULL);
	}
	else if (var->buff[1] == 0 && ft_isprint(var->buff[0]))
	{
		write(env()->fdout, &var->buff[0], 1);
		touch6(var);
		if (var->lenligne % tgetnum("co") == 1)
			ft_putstr_fd(tgetstr("sf", NULL), env()->fdout);
		ft_putstr_fd(tgetstr("cd", NULL), env()->fdout);
		ft_putstr_fd(var->ret + var->i, env()->fdout);
		if ((var->inputlen + var->lenprompt - 1) % tgetnum("co") == 0)
			ft_putstr_fd(" ", env()->fdout);
		j = ft_strlen(var->ret + var->i);
		while (j-- > 0)
			ft_putstr_fd(tgetstr("le", NULL), env()->fdout);
		if ((var->inputlen + var->lenprompt - 1) % tgetnum("co") == 0)
			ft_putstr_fd(tgetstr("le", NULL), env()->fdout);
	}
	var->buff[1] = 0;
	var->buff[2] = 0;
}
