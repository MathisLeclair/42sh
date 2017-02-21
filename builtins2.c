/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 16:03:36 by mleclair          #+#    #+#             */
/*   Updated: 2017/02/21 21:32:33 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	builtin_read(t_env *ev, char **split)
{
	char	*bufe;
	char	truc[INPUT_SIZE];
	int		r;
	int		i;

	r = 0;
	i = 1;
	truc[0] = 0;
	bufe = malloc(INPUT_SIZE);
	read(0, bufe, INPUT_SIZE);
	if (split[1] && split[1][0] == '-' && split[1][1] == 'r')
		r = 1;
	i = r == 1 ? 2 : 1;
	while (split[++r])
	{
		printf("pOPAWJOHDAW\n");
		ft_strcat(truc, split[i]);
		ft_strcat(truc, "=");
		ft_strcat(truc, bufe);
		printf("ll=%s\n", truc);
		add_var_to_env(ev->loc, split[i]);
		truc[0] = 0;
	}
}

void	history(t_env *env, char **split)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (split[0] && split[1] && split[2])
	{
		error(-7, NULL, NULL);
		return ;
	}
	if (!(env->history))
	{
		error(-11, 0 , 0);
		return ;
	}
	i = 0;
	if (split[0] && split[1][0] == '-' && split[1][1] == 'c')
	{
		free_double_array(env->history);
		env->history = 0;
	}
	else if (isnumber(split[1][0]))
		i = ft_atoi(split[1]);
	print_split(env->history + i);
}
