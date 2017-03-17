/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 11:51:57 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/17 17:25:21 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	retvalue_into_loc(t_env *env, int i)
{
	char *tmp;
	char *rmp2;

	env->lastret = i;
	tmp = malloc(300);
	tmp[0] = 0;
	ft_strcat(tmp, "?=");
	ft_strcat(tmp, rmp2 = ft_itoa(i));
	free(rmp2);
	add_var_to_env(env, tmp);
	free(tmp);
}

void	subshell2(t_env *env, int i, int l, char *input)
{
	int		child;
	int		status;
	char	*str;

	i = ft_strcfind(input, '(');
	l = ft_strcfind(input + i, ')');
	str = malloc(l);
	*str = 0;
	ft_strncat(str, input + i + 1, l - 1);
	child = fork();
	if (child == 0)
	{
		ft_read(env, str);
		exit(env->lastret);
	}
	else
	{
		free(str);
		waitpid(child, &status, 0);
		retvalue_into_loc(env, WEXITSTATUS(status));
		ft_remstr(input, i, ft_strfind(input, ')') + 1);
	}
}

int		verif_par(char *str, int u, int t)
{
	int i;
	int j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '(' && u == 0)
			u = 1;
		else if (str[i] == ')' && u == 1)
		{
			if (t == 1)
				return (i);
			u = 0;
		}
		else if (str[i] == ')' && u == 0)
			return (-1);
		else if (str[i] == '(' && u == 1)
			j = verif_par(str + i + 1, 1, 1);
		else if (j == -1)
			return (-1);
		i = j > i ? j + i + 1 : i;
	}
	if (u == 1)
		return (-1);
	return (0);
}

int		verif_subshell(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (bs_str(str, i, '(') && bs_str(str, i + 1, ')'))
			return (-1);
	return (0);
}

int		subshell(t_env *env, char *input)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strdup(input);
	if (verif_par(str, 0, 0) == -1 || verif_subshell(str) == -1)
	{
		free(str);
		ft_printf("Wrong uses of parenthesis\n");
		return (-1);
	}
	free(str);
	subshell2(env, 0, 0, input);
	while (ft_strfind(input, '(') != -1)
		subshell(env, input);
	return (0);
}
