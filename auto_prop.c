/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_prop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 18:56:27 by bfrochot          #+#    #+#             */
/*   Updated: 2017/03/24 17:32:45 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

void			ft_join_spaces(char **tmp, int i)
{
	char	*str;
	int		j;

	str = palloc(ft_strlen(*tmp) + i + 1);
	j = -1;
	while ((*tmp)[++j])
		str[j] = (*tmp)[j];
	str[j] = 0;
	while (i--)
		str[j++] = ' ';
	str[j] = 0;
	free(*tmp);
	*tmp = str;
}

static void		auto_prop_core(t_var *var, int i, size_t (*ml)[4], char **tmp)
{
	int		k;
	size_t	j;

	(*ml)[3]++;
	j = ft_strlen(var->ac[i]);
	*tmp = ft_strjoinfree(*tmp, var->ac[i], 1);
	var->i += j;
	var->lenligne += 1;
	k = 0;
	while (j + k++ < (*ml)[0] + 2)
		var->i += 1;
	ft_join_spaces(tmp, k - 1);
	(*ml)[2] += (*ml)[0] + 2;
	if ((*ml)[2] - tgetnum("co") > -(*ml)[0])
	{
		k = 0;
		while ((*ml)[2]++ < (size_t)tgetnum("co") && ++k)
			var->i += 1;
		ft_join_spaces(tmp, k);
		(*ml)[2] = 0;
	}
}

void			auto_prop(t_var *var, int p)
{
	int			i;
	size_t		ml[4];
	char		*tmp;
	static int	m = -2;

	m = (p == 1 ? -2 : m);
	i = -1;
	ml[2] = 0;
	ml[1] = tgetnum("li");
	tmp = ft_strdup("");
	ml[0] = 0;
	while (var->ac[++i])
		ml[0] = ft_strlen(var->ac[i]) > ml[0] ? ft_strlen(var->ac[i]) : ml[0];
	m = m == i - 2 ? -1 : m + 1;
	i = (i - m) / (tgetnum("co") / (int)ml[0]) + 1 < (int)ml[1] - 1 - var->inputlen
	/ tgetnum("co") ? i - ((int)ml[1] - var->inputlen / tgetnum("co") - 2) * (tgetnum("co") / (int)ml[0]) : m;
	i = m == -1 ? m : i;
	i = i < -1 ? -1 : i;
	ml[3] = 1;
	while (var->ac[++i] && ml[3] / (tgetnum("co") / ml[0]) + 2 < (ml[1] - var->inputlen / tgetnum("co")))
		auto_prop_core(var, i, &ml, &tmp);
	ft_printf("%s ", tmp);
	var->i += 1;
	free(tmp);
}
