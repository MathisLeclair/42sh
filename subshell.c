/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 11:51:57 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/25 14:26:59 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

int		verif_par2(char **str, char *tmp)
{
	free(*str);
	*str = tmp;
	free(env()->input);
	env()->input = NULL;
	env()->bool2 = 1;
	return (-2);
}

int		verif_par3(char **str, int *i, int *u, int *t)
{
	if (bs_str(*str, *i, ')') && *u == 0)
		return (-1);
	if (bs_str(*str, *i, '('))
		++*u;
	else if (bs_str(*str, *i, ')'))
		++*t;
	return (0);
}

int		verif_par(char **str, int u, int t, int i)
{
	char *tmp;

	while ((*str)[++i])
		if (verif_par3(str, &i, &u, &t) == -1)
			return (-1);
	if (t > u)
		return (-1);
	else if (t == u)
		return (0);
	else
	{
		tmp = termcaps(ft_sprintf("subshell>"), 9);
		if (env()->bool1 == 1)
			return (verif_par2(str, tmp));
		*str = ft_strjoinfree(*str, " ", 1);
		*str = ft_strjoinfree(*str, tmp, 3);
		if (verif_par(str, 0, 0, -1) == -2)
			return (-2);
	}
	ft_remstr(env()->input, ft_strfind(env()->input, '('),
	ft_strcfind(env()->input, ')') == -1 ? ft_strlen(env()->input) :
	ft_strcfind(env()->input, ')'));
	return (0);
}

int		verif_subshell(char *str)
{
	int i;
	int u;
	int k;
	int w;

	i = -1;
	u = 0;
	w = 0;
	k = 0;
	while (str[++i])
	{
		if (bs_str(str, i, '(') && bs_str(str, i + 1, ')'))
			return (-1);
		if (bs_str(str, i, '`'))
			u = u == 0 ? 1 : 0;
		if (bs_str(str, i, '"'))
			k = k == 0 ? 1 : 0;
		if (bs_str(str, i, '\''))
			w = w == 0 ? 1 : 0;
	}
	if (u != 0 || k != 0 || w != 0)
		return (-2);
	return (0);
}

int		subshell(t_env *env, char **input)
{
	int		i;

	i = verif_par(input, 0, 0, -1);
	if (i == -1 || verif_subshell(*input) == -1)
	{
		error(-19, NULL, NULL);
		return (-1);
	}
	if (i == -2)
		return (0);
	if (verif_subshell(*input) == -2)
	{
		error(-15, NULL, NULL);
		return (-1);
	}
	subshell2(env, 0, 0, *input);
	if (verif_par(input, 0, 0, -1) == -1)
		return (-1);
	i = 0;
	while (ft_strfind(*input, '(') != -1 && i != -1)
		i = subshell(env, input);
	return (i);
}
