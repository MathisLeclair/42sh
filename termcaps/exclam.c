/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclam.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 15:08:29 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/31 15:30:06 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../chell.h"

void	exlam1(int *k, int *u, char **tmp)
{
	*k = *u;
	while (*k > 0 && env()->history[--*k])
		if (ft_strcmp_beg(env()->history[*k] + 7, *tmp + 1))
			break ;
	if (*k == 0 && !ft_strcmp_beg(env()->history[*k] + 7, *tmp + 1))
		error(-13, NULL, NULL);
	if (*k == 0 && !ft_strcmp_beg(env()->history[*k] + 7, *tmp + 1))
		return ;
}

void	exclam2(int *k, int *u, int *i, char **tmp)
{
	if (!ft_isdigit(tvar()->ret[*i + 1]) && !bs_str(tvar()->ret, *i + 1, '!'))
		exlam1(k, u, tmp);
	else if (bs_str(tvar()->ret, *i + 1, '!'))
		*k = (env()->history[*u] == NULL ? *u - 1 : *u);
	else
	{
		while (ft_isdigit(tvar()->ret[++*u]))
			;
		*k = ft_atoi(tvar()->ret + *i + 1);
		if (*u > 100000 || k > u)
		{
			error(-13, NULL, NULL);
			return ;
		}
	}
}

void	verif_exlam(t_var *var)
{
	int i;
	int u;

	i = -1;
	u = 0;
	while (var->ret[++i])
	{
		if (bs_str(var->ret, i,'\''))
			u = u == 0 ? 1 : 0;
		if (bs_str(var->ret, i, '!') && u == 1)
			ft_insertstr(&var->ret, "\\", i - 1);
	}
}

void	exclam(t_var *var)
{
	int		i;
	int		u;
	int		k;
	int		j;
	char	*tmp;

	verif_exlam(var);
	u = -1;
	i = ft_strfind(var->ret, '!');
	if (i == -1)
		return ;
	while (env()->history[++u])
		;
	j = i;
	while (var->ret[j] && var->ret[j] != ' ')
		++j;
	tmp = ft_strcdup(var->ret + i, j - i);
	exclam2(&k, &u, &i, &tmp);
	free(tmp);
	ft_remstr(var->ret, i, j);
	var->i = i;
	i = ft_strlen(env()->history[k]);
	while (i-- > 7)
		add_car(var, 1, (env()->history[k])[i]);
}
