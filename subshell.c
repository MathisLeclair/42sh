/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 11:51:57 by mleclair          #+#    #+#             */
/*   Updated: 2017/02/28 15:28:04 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	subshell2(t_env *env, int i, int l, char *input)
{
	int		child;
	int		status;
	char	ret;
	char	*str;

	i = ft_strfind(input, '(');
	l = ft_strfind(input + i, ')');
	str = malloc(l - i + 1);
	*str = 0;
	str = ft_strncat(str, input + i + 1, l - i - 1);
	printf("env->input=%s# str=%s# i=%d# l=%d#\n", input, str, i, l);
	child = fork();
	if (child == 0)
	{
		parse(env, str);
		exit(0);
	}
	else
	{
		waitpid(child, &status, 0);
		ret = WEXITSTATUS(status);
		ft_remstr(env->input, i, l + 1);
		ft_remstr(input, i, l + 1);
		printf("env->input after=%s#\n input=%s#\n", env->input, input);
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

int		subshell(t_env *env, char *input)
{
	char *str;
	
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
