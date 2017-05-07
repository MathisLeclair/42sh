/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 11:31:41 by mleclair          #+#    #+#             */
/*   Updated: 2016/12/12 15:31:48 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_optsret2(char *tab, char *opt, char **str, int i)
{
	if (tab[0] == 1 && opt[ft_strlen(opt) - 1] != 'c' && ((*str)[0] != '0'
		|| (*str)[1] != 0 || (opt[ft_strlen(opt) - 1] != 'x'
	&& opt[ft_strlen(opt) - 1] != 'X'))
	&& (i != 0 || opt[ft_strlen(opt) - 1] != 'x'))
	{
		if (opt[ft_strlen(opt) - 1] == 'o' || opt[ft_strlen(opt) - 1] == 'O')
			i = ft_hastag(0, i, 0, str);
		else
			i = ft_hastag(0, i, 1, str);
		if (opt[ft_strlen(opt) - 1] == 'X')
			(*str)[1] = 'X';
	}
	return (i);
}

int		ft_optsret(char *tab, char *opt, char **str, int i)
{
	if (tab[5] != 0)
	{
		if (opt[ft_strlen(opt) - 1] != 's' && opt[ft_strlen(opt) - 1] != 'S')
			i = ft_prec(i, ft_atoi_base_printf(opt + tab[5], 10, 0),
			opt[ft_strlen(opt) - 1], str);
		else
		{
			if (ft_atoi_base_printf(opt + tab[5], 10, 0) < i)
				i = ft_atoi_base_printf(opt + tab[5], 10, 0);
		}
	}
	if (tab[1] == 1 && opt[ft_strlen(opt) - 1] != 'u'
		&& opt[ft_strlen(opt) - 1] != 'o' && opt[ft_strlen(opt) - 1] != 'O')
		i = ft_plus(i, 0, tab[5], str);
	i = ft_optsret2(tab, opt, str, i);
	if (tab[4])
		i = ft_number(i, ft_atoi_base_printf(opt, 10, 0), ((tab[5] == 0 ||
		!ft_fuckit(opt[ft_strlen(opt) - 1])) ? tab[3] : 0), str);
	if (tab[2])
		ft_minus(i, 0, (opt[ft_strlen(opt) - 1] == 'o' ||
			opt[ft_strlen(opt) - 1] == 'O') ? 1 : tab[5] - 1, str);
	if (tab[6])
		i = ft_moncul(opt, str, i);
	return (i);
}

void	ft_opts2(int k, char *opt, char *tab, int done)
{
	int len;

	len = ft_strlen(opt);
	while (++k < len)
	{
		if (opt[k] == '#' || opt[k] == 'p')
			tab[0] = 1;
		if (opt[k] == '+' && opt[len - 1] != 'x' && opt[len - 1] != 'p' &&
		opt[len - 1] != 'X')
			tab[1] = 1;
		if (opt[k] == '-')
			tab[2] = 1;
		if (ft_isdigit(opt[k]))
			if (opt[k] != '0' && (done = 1) && tab[5] == 0)
				tab[4] = 1;
		if (opt[k] == '.' && opt[len - 1] != 'c' && opt[len - 1] != 'C' &&
		opt[len - 1] != '%')
			tab[5] = k + 1;
		if (opt[k] == '0' && done == 0)
			tab[3] = 1;
		if (opt[k] == ' ')
			tab[6] = 1;
		if (tab[2] == 1)
			tab[3] = 0;
	}
}

int		ft_opts(char *opt, char **str, int i)
{
	char	done;
	int		k;
	int		len;
	char	tab[7];

	ft_memset(tab, 0, 7);
	len = ft_strlen(opt);
	done = 0;
	k = -1;
	ft_opts2(k, opt, tab, done);
	return (ft_optsret(tab, opt, str, i));
}
