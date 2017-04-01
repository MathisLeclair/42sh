/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclam.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 15:08:29 by mleclair          #+#    #+#             */
/*   Updated: 2017/04/01 16:12:31 by aridolfi         ###   ########.fr       */
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

void	remove_exlam(t_var *var)
{
	int i;
	int u;

	i = -1;
	u = 0;
	while (var->ret[++i])
	{
		if (bs_str(var->ret, i, '\''))
			u = u == 0 ? 1 : 0;
		if (var->ret[i] == '!' && var->ret[i - 1] == '\\' && u == 1)
		{
			var->ret[i - 1] = 0;
			ft_strcat(var->ret, var->ret + i);
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
		if (bs_str(var->ret, i, '\''))
			u = u == 0 ? 1 : 0;
		if (var->ret[i] == '!' && u == 1)
		{
			ft_insertstr(&var->ret, "\\", i - 1);
			++i;
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
	verif_exlam(var);
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
