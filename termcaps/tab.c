/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 14:20:22 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/18 17:42:51 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../chell.h"

void	put_ac2(t_var *var)
{
	ft_putstr(tgetstr("up", NULL));
	var->i -= tgetnum("co");
}

void	put_ac(t_var *var, int p)
{
	int		i;
	char	*tmp;

	i = var->i;
	while (var->i != (int)ft_strlen(var->ret))
		right_arrow(var);
	tmp = palloc(1);
	*tmp = 0;
	while ((var->i + var->lenprompt - 1) % tgetnum("co") != 0)
	{
		ft_join_spaces(&tmp, 1);
		var->i += 1;
	}
	ft_putstr(tmp);
	auto_prop(var, p);
	while (var->i / tgetnum("co") > 0)
		put_ac2(var);
	while (var->i != i)
	{
		var->i > i ? ft_putstr(tgetstr("le", NULL)) :
		ft_putstr(tgetstr("nd", NULL));
		var->i -= var->i > i ? 1 : -1;
	}
	var->lenligne = var->i + var->lenprompt;
}

void	tabu2(t_var *var, int *i)
{
	replace_w(var->ac[*i], var);
	put_ac(var, 0);
	++(*i);
}

void	tabu(t_var *var, int *j)
{
	static int	i;

	if (*j == 0)
	{
		*j = 1;
		var->ac = autocomplete(var->ret, var->i, env());
		if (var->ac == NULL || var->ac[0] == 0)
			return ;
		if (var->ac[1] == 0)
			replace_w(var->ac[0], var);
		if (var->ac[1] == 0)
			*j = 0;
		else
			put_ac(var, 1);
		i = 0;
	}
	else
	{
		if (var->ac == NULL || var->ac[0] == 0)
			return ;
		if (var->ac[i] == 0)
			i = 0;
		tabu2(var, &i);
	}
	var->buff[0] = 0;
}
