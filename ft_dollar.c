/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 13:39:33 by mleclair          #+#    #+#             */
/*   Updated: 2017/05/04 18:07:55 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

void	ft_replace(t_env *env, char *str, int sav, int i)
{
	char *newinp;

	newinp = palloc(ft_strlen(env->input) + ft_strlen(str));
	newinp[0] = 0;
	ft_strlcat(newinp, env->input, sav + 1);
	ft_strcat(newinp, str);
	ft_strcat(newinp, env->input + i);
	if (env->input)
		free(env->input);
	env->input = newinp;
}

int		ft_replacestr(t_env *e, char *str2, int sav, int i)
{
	char	str[INPUT_SIZE];
	int		j;
	int		ret;

	j = 0;
	*str = 0;
	ret = find_param(e->ev, str2) == -1 ? find_param(e->loc->ev, str2) :
	find_param(e->ev, str2);
	if (ret == -1)
		ft_replace(e, "", sav, i);
	else if (find_param(e->ev, str2) == -1)
	{
		while (e->loc->ev[ret][j] != '=')
			++j;
		ft_strcat(str, e->loc->ev[ret] + j + 1);
		ft_replace(e, str, sav, i);
	}
	else
	{
		while (e->ev[ret][j] != '=')
			++j;
		ft_strcat(str, e->ev[ret] + j + 1);
		ft_replace(e, str, sav, i);
	}
	return (sav + ft_strlen(str) - 1);
}

void	ft_dollar(t_env *e, int i, char quote)
{
	int		k;
	int		sav;
	char	*str;

	str = palloc(INPUT_SIZE);
	while (++i != (int)ft_strlen(e->input) && (k = -1))
	{
		if (bs_str(e->input, i, '\'') && quote == 0)
			while (e->input[i + 1] && e->input[i + 1] != '\'')
				++i;
		if (bs_str(e->input, i, '$'))
		{
			sav = i;
			while (e->input[++i] && e->input[i] != ' ' && e->input[i] != '\t'
				&& e->input[i] != '"' && e->input[i] != '\'' && ++k != -1)
				str[k] = e->input[i];
			str[k + 1] = '\0';
			i = ft_replacestr(e, str, sav, i);
		}
		if (e->input[i] == '"' && quote == 0)
			quote = 1;
		else if (e->input[i] == '"')
			quote = 0;
	}
	free(str);
}
