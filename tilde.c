/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 13:39:33 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/30 17:44:53 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	strreeplace(t_env *e, char *str, int start)
{
	char *newinp;

	newinp = palloc(ft_strlen(e->input) + ft_strlen(str));
	newinp[0] = 0;
	ft_strlcat(newinp, e->input, start + 1);
	ft_strcat(newinp, str);
	ft_strcat(newinp, e->input + start + 1);
	if (e->input)
		free(e->input);
	e->input = newinp;
}

void	ft_tilde(t_env *e, int i, char quote)
{
	int		k;
	int		l;
	char	str[INPUT_SIZE];

	*str = 0;
	while (++i != (int)ft_strlen(e->input) && (k = -1))
	{
		if (e->input[i] == '\'' && quote == 0)
			while (e->input[i + 1] && e->input[i + 1] != '\'')
				++i;
		if (e->input[i] == '~')
		{
			if ((l = find_param(e->ev, "HOME")) == -1)
				ft_strcat(str, "/");
			else
				ft_strcat(str, e->ev[l] + 5);
			strreeplace(e, str, i);
		}
		if (e->input[i] == '"' && quote == 0)
			quote = 1;
		else if (e->input[i] == '"')
			quote = 0;
	}
}
