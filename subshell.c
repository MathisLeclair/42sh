/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 11:51:57 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/21 16:03:58 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

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
	l = ft_strfind(input + i, ')');
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
		ft_remstr(input, i, ft_strfind(input + i, ')') + i + 1);
		ft_remstr(env->input, i, ft_strfind(env->input + i, ')') + i + 1);
	}
}

int		verif_par(char **str, int u, int t, int i)
{
	char *tmp;

	while ((*str)[++i])
	{
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
		*str = ft_strjoinfree(*str, " ", 1);
		*str = ft_strjoinfree(*str, tmp, 3);
		verif_par(str, 0, 0, -1);
	}
	ft_remstr(env()->input, ft_strfind(env()->input, '('),
		ft_strcfind(env()->input, ')'));
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

int		subshell(t_env *env, char **input)
{
	int		i;

	i = 0;
	if (verif_par(input, 0, 0, -1) == -1 ||
		verif_subshell(*input) == -1)
	{
		ft_printf("Wrong uses of parenthesis\n");
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
