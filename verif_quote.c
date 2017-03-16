/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 17:51:24 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/16 13:30:32 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

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
		tmp = ft_strjoin(tmp, "\n");
		tmp = ft_strjoinfree(tmp, tmp3, 3);
	}
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
		tmp = ft_strjoin(tmp, "\n");
		tmp = ft_strjoinfree(tmp, tmp3, 3);
	}
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
		if (((*str)[p] == '\'' || (*str)[p] == '"') && quote == 0 && dquote == 0
		&& ((p > 1 && (*str)[p - 1] != '\\') || p < 1))
			pos = p;
		if ((*str)[p] == '\'' && dquote == 0 &&
			((p > 1 && (*str)[p - 1] != '\\') || p < 1))
			quote = quote == 1 ? 0 : 1;
		if ((*str)[p] == '"' && quote == 0 &&
			((p > 1 && (*str)[p - 1] != '\\') || p < 1))
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
