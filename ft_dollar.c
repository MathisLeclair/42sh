/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 13:39:33 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/23 13:08:54 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	ft_replace(t_env *env, char *str, int sav, int i)
{
	char *newinp;

	newinp = palloc(ft_strlen(env->input) + ft_strlen(str));
	newinp[0] = 0;
	ft_strlcat(newinp, env->input, sav + 1);
	ft_strcat(newinp, str);
	ft_strcat(newinp, env->input + i);
	env->input = newinp;
}

int		ft_replacestr(t_env *env, int ret, int sav, int i)
{
	char	*str;
	int		j;

	if (ret == -1)
		ft_replace(env, "", sav, i);
	else
	{
		j = 0;
		while (env->ev[ret][j] != '=')
			++j;
		str = ft_strdup(env->ev[ret] + j + 1);
		ft_replace(env, str, sav, i);
		return (sav + ft_strlen(str) - 1);
	}
	return (sav - 1);
}

void	ft_dollar(t_env *e, int i, char quote)
{
	int		k;
	int		sav;
	char	*str;

	str = palloc(INPUT_SIZE);
	while (++i != (int)ft_strlen(e->input) && (k = -1))
	{
		if (e->input[i] == '\'' && quote == 0)
			while (e->input[i + 1] && e->input[i + 1] != '\'')
				++i;
		if (e->input[i] == '$')
		{
			sav = i;
			while (e->input[++i] && e->input[i] != ' ' && e->input[i] != '\t'
				&& e->input[i] != '"' && e->input[i] != '\'' && ++k != -1)
				str[k] = e->input[i];
			str[k + 1] = '\0';
			i = ft_replacestr(e, find_param(e->ev, str), sav, i);
		}
		if (e->input[i] == '"' && quote == 0)
			quote = 1;
		else if (e->input[i] == '"')
			quote = 0;
	}
	free(str);
}
