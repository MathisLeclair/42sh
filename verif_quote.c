/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 17:51:24 by mleclair          #+#    #+#             */
/*   Updated: 2017/02/22 15:38:57 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int	verif_quote_return(char *tmp, int i)
{
	if (i == 1)
	{
		free(tmp);
		ft_putstr("Unmatched \"\n");
	}
	else
	{
		free(tmp);
		ft_putstr("Unmatched '\n");
	}
	return (-1);
}

int	verif_quote2(char *tmp, int i, int quote, int dquote)
{
	while (tmp[++i])
	{
		if ((tmp[i] == '\'' && (quote = 1)) ||
			(tmp[i] == '"' && (dquote = 1)))
		{
			tmp[i] = 1;
			while (tmp[++i])
			{
				if ((tmp[i] == '\'' && quote == 1) ||
					(tmp[i] == '"' && dquote == 1))
				{
					dquote = 0;
					quote = 0;
					tmp[i] = 0;
					break ;
				}
			}
		}
		if (dquote == 1)
			return (verif_quote_return(tmp, 1));
		else if (quote == 1)
			return (verif_quote_return(tmp, 2));
	}
	return (0);
}

int	verif_quote(char *str, int p)
{
	int		i;
	int		quote;
	int		dquote;
	char	*tmp;

	tmp = ft_strdup(str);
	quote = 0;
	dquote = 0;
	i = -1;
	if (!tmp)
		return (0);
	p = verif_quote2(tmp, i, quote, dquote);
	return (p);
}
