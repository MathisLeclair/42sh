/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 15:01:14 by bfrochot          #+#    #+#             */
/*   Updated: 2017/03/23 15:58:16 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

void	startfind(char **ac, t_env *env, int boolean, int i)
{
	char	*tmp;
	char	*tmp2;

	while (ac[i])
	{
		tmp = to_lwcase(ac[i]);
		tmp2 = to_lwcase(env->find);
		if (!ft_strcmp_beg(tmp, tmp2))
		{
			free(ac[i]);
			boolean = i;
			while (ac[boolean++])
				ac[boolean - 1] = ac[boolean];
		}
		else
			++i;
		free(tmp);
		free(tmp2);
	}
}

char	**forest(char *s, int ps, t_env *env, char first)
{
	char	**ac;

	if (bs_str(s, ps, ' ') || s[ps] == '\0' || bs_str(s, ps + 1, ' ') ||
		s[ps + 1] == '\0')
	{
		if (first)
			ac = auto_possibilities(0, env);
		else
			ac = auto_possibilities(1, env);
		if ((ps == 0 || s[ps - 1] != ' ') && env->find[0] != '/')
			startfind(ac, env, 1, 0);
	}
	else
	{
		if (first)
			ac = auto_possibilities(0, env);
		else
			ac = auto_possibilities(1, env);
		if (env->find[0] != '/')
			startfind(ac, env, 0, 0);
	}
	return (ac);
}

char	**autocomplete(char *input, int pos, t_env *env)
{
	char	first;
	int		i;
	char	**ac;
	char	quote;

	quote = 0;
	i = 0;
	while (input[i] && (bs_str(input, i, ' ') || bs_str(input, i, '\t')))
		++i;
	if (i > pos || input[i] == '\0')
		return (NULL);
	while (input[i] && (!bs_str(input, i, ' ') || quote != 0))
	{
		if (bs_str(input, i, '\'') || bs_str(input, i, '"'))
			quote = input[i] == quote ? 0 : quote;
		++i;
	}
	first = pos > i ? 0 : 1;
	env->find = finder(input, bs_str(input, pos, ' ') ? pos - 1 : pos);
	ft_suppr_bs(&env->find);
	ft_tilde(&env->find, -1, 0);
	ac = forest(input, pos, env, first);
	free(env->find);
	env->find = NULL;
	return (ac);
}
