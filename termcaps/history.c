/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 15:26:16 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/03 17:30:46 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../42sh.h"

void	add_history(t_var *var)
{
	int i;
	char *tmp;
	char *num;

	i = 0;
	while (env()->history[i])
		++i;
	num = ft_itoa(i);
	if (ft_strlen(num) < 5)
	{
		tmp = malloc(6);
		i = -1;
		while (++i < 5 - (int)ft_strlen(num))
			tmp[i] = ' ';
		tmp[i] = 0;
		ft_strcat(tmp, num);
		free(num);
		num = tmp;
	}
	tmp = malloc(ft_strlen(var->ret) + ft_strlen(num) + 5);
	*tmp = 0;
	ft_strcat(tmp, num);
	ft_strcat(tmp, "  ");
	ft_strcat(tmp, var->ret);
	add_str_to_dstr(&env()->history, tmp);
	free(tmp);
	free(num);
}
