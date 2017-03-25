/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 14:26:26 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/25 14:26:57 by mleclair         ###   ########.fr       */
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
