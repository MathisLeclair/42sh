/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclam.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 15:08:29 by mleclair          #+#    #+#             */
/*   Updated: 2017/05/15 16:56:28 by bfrochot         ###   ########.fr       */
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
		*k = ft_atoi(tvar()->ret + *i + 1);
		if (*u > 100000 || *k >= *u || *k < 0)
		{
			*k = -1;
			error(-13, NULL, NULL);
			return ;
		}
	}
}

int		ft_strfound(char *str, char c)
{
	int		i;
	char	done;

	i = -1;
	done = 0;
	while (str[++i])
	{
		if (str[i] == '\'')
			done = done == 0 ? 1 : 0;
		if (str[i] == c && done == 0 && str[i + 1] && str[i + 1] != '=')
			return (i);
	}
	return (-1);
}

int		exclam(t_var *var, int u)
{
	int		i;
	int		k;
	int		j;
	char	*tmp;

	i = ft_strfound(var->ret, '!');
	if (i == -1)
		return (0);
	while (env()->history[++u])
		;
	j = i;
	while (var->ret[j] && var->ret[j] != ' ' && var->ret[j] != '\t')
		++j;
	tmp = ft_strcdup(var->ret + i, j - i);
	exclam2(&k, &u, &i, &tmp);
	free(tmp);
	ft_remstr(var->ret, i, j);
	var->i = i;
	if (k == -1)
		return (1);
	i = ft_strlen(env()->history[k]);
	while (i-- > 7)
		add_car(var, 1, (env()->history[k])[i]);
	return (1);
}
