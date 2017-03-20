/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_prop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 18:56:27 by bfrochot          #+#    #+#             */
/*   Updated: 2017/03/20 16:04:16 by mleclair         ###   ########.fr       */
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

static void		auto_prop_core(t_var *var, int *i, size_t (*ml)[3], char **tmp)
{
	int			k;

	(*ml)[1] = ft_strlen(var->ac[*i]);
	*tmp = ft_strjoinfree(*tmp, var->ac[*i], 1);
	var->i += (*ml)[1];
	var->lenligne += 1;
	k = 0;
	while ((*ml)[1] + k++ < (*ml)[0] + 2)
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
	size_t		ml[3];
	char		*tmp;
	static int	m = -1;

	m = (p == 1 ? -1 : m);
	i = -1;
	ml[2] = 0;
	tmp = ft_strdup("");
	while (var->ac[++i])
		ml[0] = ft_strlen(var->ac[i]) > ml[0] ? ft_strlen(var->ac[i]) : ml[0];
	if (tgetnum("li") - 2 < i / (tgetnum("co") / (int)ml[0]) && p == 0)
		m = m == i - 2 ? -1 : m + 1;
	i = (i - m) / (tgetnum("co") / (int)ml[0]) < tgetnum("li") - 1 ? i
		- (tgetnum("li") - 1) * (tgetnum("co") / (int)ml[0]) : m;
	i = m == -1 ? m : i;
	while (var->ac[++i] && (i - m) / (tgetnum("co") / (int)ml[0]) + 1
			< (tgetnum("li") - var->lenligne / tgetnum("co")))
		auto_prop_core(var, &i, &ml, &tmp);
	ft_printf("%s ", tmp);
	var->i += 1;
	free(tmp);
}
