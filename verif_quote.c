/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 17:51:24 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/21 19:02:15 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

void	add_bs_q(char **str, int i, char c)
{
	int		j;
	int		k;
	char	*tmp;

	while ((*str)[++i])
	{
		if (bs_str(*str, i, c))
		{
			k = 0;
			j = 0;
			tmp = palloc(INPUT_SIZE);
			(*str)[i] = 0;
			while (!bs_str(*str, ++i, c))
			{
				tmp[j++] = '\\';
				tmp[j++] = (*str)[i];
			}
			k = j;
			while ((*str)[i])
				tmp[j++] = (*str)[i++];
			tmp[j] = 0;
			*str = ft_strjoinfree(*str, tmp, 3);
			i += k;
		}
	}
}

int		ft_strfind_bq(const char *s, int c)
{
	int		i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] && (s[i] != c || (i > 0 && s[i - 1] == '\\')))
		i++;
	return (s[i] == c ? i : -1);
}

void	complete_dquote(char **str, int pos)
{
	char *tmp;
	char *tmp3;

	tmp = ft_strdup(*str);
	while (ft_strfind_bq(tmp + pos + 1, '"') == -1)
	{
		tmp3 = termcaps(ft_sprintf("dquote>"));
		tmp = ft_strjoinfree(tmp, "\n", 1);
		tmp = ft_strjoinfree(tmp, tmp3, 3);
	}
	free(*str);
	*str = tmp;
}

void	complete_quote(char **str, int pos)
{
	char *tmp;
	char *tmp3;

	tmp = ft_strdup(*str);
	while (ft_strfind_bq(tmp + pos + 1, '\'') == -1)
	{
		tmp3 = termcaps(ft_sprintf("quote>"));
		tmp = ft_strjoinfree(tmp, "\n", 1);
		tmp = ft_strjoinfree(tmp, tmp3, 3);
	}
	free(*str);
	*str = tmp;
}

int		verif_quote(char **str, int p, int quote)
{
	int dquote;
	int pos;

	dquote = 0;
	pos = 0;
	while ((*str)[++p])
	{
		if ((bs_str((*str), p, '\'') || bs_str((*str), p, '"')) && quote == 0 
			&& dquote == 0)
			pos = p;
		if (bs_str((*str), p, '\'') && dquote == 0)
			quote = quote == 1 ? 0 : 1;
		if (bs_str((*str), p, '"') && quote == 0)
			dquote = dquote == 1 ? 0 : 1;
	}
	if (quote == 1)
		complete_quote(str, pos);
	else if (dquote == 1)
		complete_dquote(str, pos);
	else
		return (0);
	return (-1);
}
