/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 13:39:33 by mleclair          #+#    #+#             */
/*   Updated: 2017/04/18 16:20:48 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

int		add_bs_q2(char **str, char c, int i)
{
	int u;

	u = -1;
	while ((*str)[i] != c)
	{
		if ((*str)[i] == c)
			u = 1;
		++i;
	}
	return (u);
}

void	strreeplace(char **s, char *str, int start)
{
	char *newinp;

	newinp = palloc(ft_strlen(*s) + ft_strlen(str));
	newinp[0] = 0;
	ft_strlcat(newinp, *s, start + 1);
	ft_strcat(newinp, str);
	ft_strcat(newinp, *s + start + 1);
	free(*s);
	*s = newinp;
}

void	ft_tilde(char **s, int i, char quote)
{
	int		k;
	int		l;
	char	str[INPUT_SIZE];

	while (++i != (int)ft_strlen(*s) && (k = -1))
	{
		if ((*s)[i] == '\'' && quote == 0)
			while ((*s)[i + 1] && (*s)[i + 1] != '\'')
				++i;
		if ((*s)[i] == '~')
		{
			*str = 0;
			if ((l = find_param(env()->ev, "HOME")) == -1)
				ft_strcat(str, "/");
			else
				ft_strcat(str, env()->ev[l] + 5);
			strreeplace(s, str, i);
		}
		if (((*s)[i] == '"' || (*s)[i] == '\'') && quote == 0)
			quote = (*s)[i];
		else if ((*s)[i] == quote)
			quote = 0;
	}
}
