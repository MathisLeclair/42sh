/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 11:51:57 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/23 14:41:50 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

void	subshell2(t_env *env, int i, int l, char *input)
{
	int		child;
	int		status;
	char	*str;

	i = ft_strcfind(input, '(');
	l = ft_strfind(input + i, ')');
	str = malloc(l);
	*str = 0;
	ft_strncat(str, input + i + 1, l - 1);
	child = fork();
	if (child == 0)
	{
		ft_read(env, str, -1, 0);
		exit(env->lastret);
	}
	else
	{
		free(str);
		waitpid(child, &status, 0);
		retvalue_into_loc(env, WEXITSTATUS(status));
		ft_remstr(input, i, ft_strfind(input + i, ')') + i + 1);
		ft_remstr(env->input, i, ft_strfind(env->input + i, ')') + i + 1);
	}
}

int		verif_par2(char **str, char *tmp)
{
	free(*str);
	*str = tmp;
	free(env()->input);
	env()->input = NULL;
	env()->bool2 = 1;
	return (-2);
}

int		verif_par(char **str, int u, int t, int i)
{
	char *tmp;

	while ((*str)[++i])
	{
		if (bs_str(*str, i, ')') && u == 0)
			return (-1);
		if (bs_str(*str, i, '('))
			++u;
		else if (bs_str(*str, i, ')'))
			++t;
	}
	if (t > u)
		return (-1);
	else if (t == u)
		return (0);
	else
	{
		tmp = termcaps(ft_sprintf("subshell>"));
		if (env()->bool1 == 1)
			return (verif_par2(str, tmp));
		*str = ft_strjoinfree(*str, " ", 1);
		*str = ft_strjoinfree(*str, tmp, 3);
		if (verif_par(str, 0, 0, -1) == -2)
			return (-2);
	}
	ft_remstr(env()->input, ft_strfind(env()->input, '('),
	ft_strcfind(env()->input, ')') == -1 ? ft_strlen(env()->input) :
	ft_strcfind(env()->input, ')'));
	return (0);
}

int		verif_subshell(char *str)
{
	int i;
	int u;
	int k;
	int w;

	i = -1;
	u = 0;
	w = 0;
	k = 0;
	while (str[++i])
	{
		if (bs_str(str, i, '(') && bs_str(str, i + 1, ')'))
			return (-1);
		if (bs_str(str, i, '`'))
			u = u == 0 ? 1 : 0;
		if (bs_str(str, i, '"'))
			k = k == 0 ? 1 : 0;
		if (bs_str(str, i, '\''))
			w = w == 0 ? 1 : 0;
	}
	if (u != 0 || k != 0 || w != 0)
		return (-2);
	return (0);
}

int		subshell(t_env *env, char **input)
{
	int		i;

	i = verif_par(input, 0, 0, -1);
	if (i == -1 || verif_subshell(*input) == -1)
	{
		error(-19, NULL, NULL);
		return (-1);
	}
	if (i == -2)
		return (0);
	if (verif_subshell(*input) == -2)
	{
		error(-15, NULL, NULL);
		return (-1);
	}
	subshell2(env, 0, 0, *input);
	if (verif_par(input, 0, 0, -1) == -1)
		return (-1);
	i = 0;
	while (ft_strfind(*input, '(') != -1 && i != -1)
		i = subshell(env, input);
	return (i);
}
