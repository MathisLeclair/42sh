/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 13:29:49 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/21 17:41:51 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../chell.h"

void	ft_asdf(t_var *var, int i, int *bg, int j)
{
	char	*tmp;
	char	*tmp2;

	var->ac = palloc(sizeof(char *));
	var->ac[0] = 0;
	while (env()->history[++i])
		if (strstr(env()->history[i], var->ret))
			add_str_to_dstr(&var->ac, env()->history[i] + 7);
	i = 0;
	while (var->ac[i])
	{
		tmp = ft_strdup(var->ac[i]);
		tmp2 = ft_strdup(var->ret);
		if (!ft_strcmp_beg(tmp, tmp2))
		{
			free(var->ac[i]);
			j = i;
			while (var->ac[j++])
				var->ac[j - 1] = var->ac[j];
		}
		else
			++i;
		ft_strdel2(&tmp, &tmp2);
	}
	*bg = i;
}

void	up_arrow(t_var *var, int *bg)
{
	char *tmp;

	if (env()->history[*bg] == 0)
	{
		free_double_array(var->ac);
		ft_asdf(var, -1, bg, 0);
	}
	if (var->arr == NULL)
		var->arr = ft_strdup(var->ret);
	if (var->ac[0])
	{
		while (var->i != 0)
			backspace(var);
		while (var->ret[0])
			deleteu(var);
		if (*bg > 0)
			(*bg)--;
		tmp = var->cpy;
		var->cpy = var->ac[*bg];
		paste(var);
		var->cpy = tmp;
	}
}

void	down_arrow(t_var *var, int *bg)
{
	char *tmp;

	if (var->ac[0])
	{
		while (var->i != 0)
			backspace(var);
		while (var->ret[0])
			deleteu(var);
		if (var->ac[*bg])
			(*bg)++;
		if (var->ac[*bg] == 0)
		{
			tmp = var->cpy;
			var->cpy = var->arr;
			paste(var);
			var->cpy = tmp;
		}
		else
		{
			tmp = var->cpy;
			var->cpy = var->ac[*bg];
			paste(var);
			var->cpy = tmp;
		}
	}
}

void	left_arrow(t_var *var)
{
	int i;

	--var->i;
	--var->lenligne;
	if (var->lenligne % tgetnum("co") == 0)
	{
		ft_putstr(tgetstr("up", NULL));
		i = -1;
		while (++i < tgetnum("co"))
			ft_putstr(tgetstr("nd", NULL));
	}
	else
		ft_putstr(tgetstr("le", NULL));
}

void	right_arrow(t_var *var)
{
	if (var->i < (int)ft_strlen(var->ret))
	{
		if (var->lenligne % tgetnum("co") == 0)
			ft_putstr(tgetstr("sf", NULL));
		else
			ft_putstr(tgetstr("nd", NULL));
		++var->i;
		++var->lenligne;
	}
}
