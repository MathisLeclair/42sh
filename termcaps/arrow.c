/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 13:29:49 by mleclair          #+#    #+#             */
/*   Updated: 2017/04/19 15:14:50 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../chell.h"

void	ft_asdf(t_var *var, int i, int *bg, int j)
{
	char	*tmp;
	char	*tmp2;

	var->his = palloc(sizeof(char *));
	var->his[0] = 0;
	while (env()->history[++i])
		if (ft_strstr(env()->history[i], var->ret))
			add_str_to_dstr(&var->his, env()->history[i] + 7);
	i = 0;
	while (var->his[i])
	{
		tmp = ft_strdup(var->his[i]);
		tmp2 = ft_strdup(var->ret);
		if (!ft_strcmp_beg(tmp, tmp2))
		{
			free(var->his[i]);
			j = i;
			while (var->his[j++])
				var->his[j - 1] = var->his[j];
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

	if (env()->bool3 == 1)
		return ;
	if (env()->history[*bg] == 0)
	{
		free_double_array(var->his);
		ft_asdf(var, -1, bg, 0);
	}
	if (var->arr == NULL)
		var->arr = ft_strdup(var->ret);
	if (var->his[0])
	{
		while (var->i != 0)
			backspace(var);
		while (var->ret[0])
			deleteu(var);
		if (*bg > 0)
			(*bg)--;
		tmp = var->cpy;
		var->cpy = var->his[*bg];
		paste(var);
		var->cpy = tmp;
	}
}

void	down_arrow(t_var *var, int *bg)
{
	char *tmp;

	if (var->his[0] && env()->bool3 == 0)
	{
		while (var->i != 0)
			backspace(var);
		while (var->ret[0])
			deleteu(var);
		if (var->his[*bg])
			(*bg)++;
		if (var->his[*bg] == 0)
		{
			tmp = var->cpy;
			var->cpy = var->arr;
			paste(var);
			var->cpy = tmp;
		}
		else
		{
			tmp = var->cpy;
			var->cpy = var->his[*bg];
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
		ft_putstr_fd(tgetstr("up", NULL), env()->fdout);
		i = -1;
		while (++i < tgetnum("co"))
			ft_putstr_fd(tgetstr("nd", NULL), env()->fdout);
	}
	else
		ft_putstr_fd(tgetstr("le", NULL), env()->fdout);
}

void	right_arrow(t_var *var)
{
	if (var->i < (int)ft_strlen(var->ret))
	{
		if (var->lenligne % tgetnum("co") == 0)
			ft_putstr_fd(tgetstr("sf", NULL), env()->fdout);
		else
			ft_putstr_fd(tgetstr("nd", NULL), env()->fdout);
		++var->i;
		++var->lenligne;
	}
}
