/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 15:26:16 by mleclair          #+#    #+#             */
/*   Updated: 2017/02/22 14:07:09 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../42sh.h"

void	add_history(t_var *var)
{
	int i;
	char *tmp;
	char *num;

	i = 0;
	if (env()->history == NULL)
	{
		env()->history = malloc(sizeof(char *));
		env()->history[0] = 0;
	}
	while (env()->history[i])
		++i;
	num = ft_itoa(i);
	tmp = malloc(ft_strlen(var->ret) + ft_strlen(num) + 5);
	*tmp = 0;
	ft_strcat(tmp, num);
	ft_strcat(tmp, "    ");
	ft_strcat(tmp, var->ret);
	add_str_to_dstr(&env()->history, tmp);
	free(tmp);
	tmp = NULL;
	free(num);
	num = NULL;
}
