/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_prop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 18:56:27 by bfrochot          #+#    #+#             */
/*   Updated: 2017/03/18 18:09:29 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

void	ft_join_spaces(char **tmp, int i)
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

void	auto_prop(t_var *var, int p)
{
	int			i;
	int			k;
	size_t		l;
	size_t		max;
	size_t		len;
	char		*tmp;
	static int	m = -1;

	m = p == 1 ? -1 : m;
	tmp = palloc(1);
	*tmp = 0;
	i = -1;
	max = 0;
	while (var->ac[++i])
		max = ft_strlen(var->ac[i]) > max ? ft_strlen(var->ac[i]) : max;
	if (tgetnum("li") - 2 < i / (tgetnum("co") / (int)max) && p == 0)
		m = m == i - 2 ? -1 : m + 1;
	i = (i - m) / (tgetnum("co") / (int)max) < tgetnum("li") - 1 ? i
	- (tgetnum("li") - 1) * (tgetnum("co") / (int)max) : m;
	i = m == -1 ? m : i;
	l = 0;
	while (var->ac[++i] && (i - m) / (tgetnum("co") / (int)max) + 1
			< (tgetnum("li") - var->lenligne / tgetnum("co")))
	{
		len = ft_strlen(var->ac[i]);
		tmp = ft_strjoinfree(tmp, var->ac[i], 1);
		var->i += len;
		var->lenligne += 1;
		k = 0;
		while (len + k++ < max + 2)
			var->i += 1;
		ft_join_spaces(&tmp, k - 1);
		l += max + 2;
		if (l - tgetnum("co") > -max)
		{
			k = 0;
			while (l++ < (size_t)tgetnum("co") && ++k)
				var->i += 1;
			ft_join_spaces(&tmp, k);
			l = 0;
		}
	}
	write(1, tmp, ft_strlen(tmp));
	write(1, " ", 1);
	var->i += 1;
	free(tmp);
}
