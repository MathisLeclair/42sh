/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclam.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 15:08:29 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/30 18:41:49 by mleclair         ###   ########.fr       */
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

void	exclam(t_var *var)
{
	int		i;
	int		u;
	int		k;
	int		j;
	char	*tmp;

	u = -1;
	i = ft_strfind(var->ret, '!');
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
