/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_prop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 18:56:27 by bfrochot          #+#    #+#             */
/*   Updated: 2017/03/25 13:46:08 by mleclair         ###   ########.fr       */
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

char			*ft_auto(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i])
		++i;
	while (i > 0 && !bs_str(str, i, '/'))
		--i;
	tmp = ft_strdup(str + (i == 0 ? 0 : i + 1));
	return (tmp);
}

static void		auto_prop_core(t_var *var, int i, size_t (*ml)[4], char **tmp)
{
	int		k;
	size_t	j;
	char	*new;

	(*ml)[3]++;
	new = ft_auto(var->ac[i]);
	j = ft_strlen(new);
	*tmp = ft_strjoinfree(*tmp, new, 1);
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
	free(new);
}

void			auto_prop(t_var *var, int p, int i)
{
	size_t		ml[4];
	char		*tmp;
	static int	m = -2;

	m = (p == 1 ? -2 : m);
	ml[2] = 0;
	ml[1] = tgetnum("li");
	tmp = ft_strdup("");
	ml[0] = 0;
	while (var->ac[++i])
		ml[0] = ft_strlen(var->ac[i]) > ml[0] ? ft_strlen(var->ac[i]) : ml[0];
	m = m == i - 2 ? -1 : m + 1;
	i = (i - m) / (tgetnum("co") / (int)ml[0]) + 1 < (int)ml[1] - 1 -
	var->inputlen / tgetnum("co") ? i - ((int)ml[1] - var->inputlen /
	tgetnum("co") - 2) * (tgetnum("co") / (int)ml[0]) : m;
	i = m == -1 ? m : i;
	i = i < -1 ? -1 : i;
	ml[3] = 1;
	while (var->ac[++i] && ml[3] / (tgetnum("co") / ml[0]) + 2 < (ml[1] -
		var->inputlen / tgetnum("co")))
		auto_prop_core(var, i, &ml, &tmp);
	ft_printf("%s ", tmp);
	var->i += 1;
	free(tmp);
}
