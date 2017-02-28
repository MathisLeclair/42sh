/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 11:51:57 by mleclair          #+#    #+#             */
/*   Updated: 2017/02/28 19:15:53 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	retvalue_into_loc(t_env *env, int i)
{
	char *tmp;

	env->lastret = i;
	tmp = malloc(300);
	tmp[0] = 0;
	ft_strcat(tmp, "?=");
	ft_strcat(tmp, ft_itoa(i));
	add_var_to_env(env, tmp);
	free(tmp);
}

void	subshell2(t_env *env, int i, int l, char *input)
{
	int		child;
	int		status;
	char	*str;

	i = ft_strfind(input, '(');
	l = ft_strfind(input + i, ')');
	str = malloc(l);
	*str = 0;
	str = ft_strncat(str, input + i + 1, l - i - 1);
	child = fork();
	if (child == 0)
	{
		parse(env, str);
		exit(env->lastret);
	}
	else
	{
		waitpid(child, &status, 0);
		retvalue_into_loc(env, WEXITSTATUS(status));
		ft_remstr(env->input, i, l + 1);
		ft_remstr(input, i, l + 1);
	}
}

int		verif_par(char *str)
{
	int i;
	int u;

	i = -1;
	u = 0;
	while (str[++i])
	{
		if (str[i] == '(' && u == 0)
			u = 1;
		else if (str[i] == ')' && u == 1)
		{
			str[i] = '~';
			u = 0;
		}
		else if (str[i] == ')' && u == 0)
			return (-1);
		else if (str[i] == '(' && u == 1 && verif_par(str + i) == -1)
			return (-1);
	}
	if (u == 1)
		return (-1);
	return (0);
}

int		verif_subshell(char *input)
{
	int i;
	int ok;
	int u;

	ok = -1;
	u = -1;
	i = ft_strfind(input, '(');
	while (input[++u])
		if (input[u] == '&' || input[u] == '|' ||
		input[u] == '>' ||input[u] == '<')
			ok = 0;
	return (ok);
}

int		subshell(t_env *env, char *input)
{
	char *str;

	if (verif_subshell(input) == -1)
	{
		ft_putstr("Wrong use of '()'\n");
		return(-1);
	}
	str = ft_strdup(input);
	if (verif_par(str) == -1)
	{
		free(str);
		ft_printf("Wrong numbers of parenthesis\n");
		return (-1);
	}
	free(str);
	subshell2(env, 0, 0, input);
	return (0);
}
