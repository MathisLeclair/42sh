/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 13:44:16 by mleclair          #+#    #+#             */
/*   Updated: 2017/05/04 18:15:55 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../chell.h"

void	replace_w(char *word, t_var *var)
{
	char	*tmp;

	while (var->i && !bs_str(var->ret, var->i - 1, ' '))
		backspace(var);
	while (bs_str(var->ret, var->i, ' ') && var->ret[var->i])
		deleteu(var);
	tmp = var->cpy;
	var->cpy = ft_strdup(word);
	paste(var);
	free(var->cpy);
	var->cpy = tmp;
}

t_var	*tvar(void)
{
	static t_var	*var = NULL;

	if (var == NULL)
	{
		var = palloc(sizeof(t_var));
		var->cpy = palloc(INPUT_SIZE);
		*var->cpy = 0;
		var->ret = palloc(1);
		var->ret[0] = 0;
		var->buff = palloc(3);
		var->buff[0] = 0;
		var->buff[1] = 0;
		var->buff[2] = 0;
	}
	return (var);
}

void	initvar(t_var *var, int i, int u, int k)
{
	if (i == 1)
		bzero(var->buff, 3);
	var->lenprompt = u + (u == 10 ? ft_strlen(env()->dir) : 1);
	var->lenligne = var->lenprompt;
	var->i = 0;
	var->sovi = 0;
	var->del = 0;
	var->selmode = 0;
	var->selstart = -1;
	var->selend = -1;
	var->inputlen = 0;
	var->ac = NULL;
	var->termlvl = k;
	var->arr = 0;
	var->ret[0] = 0;
	var->his = NULL;
}

void	add_car(t_var *var, int boule, char c)
{
	char *tmp;

	var->inputlen += 1;
	tmp = palloc(ft_strlen(var->ret) + 2);
	*tmp = 0;
	ft_strncat(tmp, var->ret, var->i);
	tmp[var->i] = boule == 1 ? c : var->buff[0];
	tmp[var->i + 1] = 0;
	ft_strcat(tmp, var->ret + var->i);
	free(var->ret);
	var->ret = tmp;
}

void	rem_car(t_var *var)
{
	char *tmp;

	tmp = palloc(4096);
	if (var->ret[var->i])
		ft_strcpy(tmp, var->ret + var->i + 1);
	else
		tmp[0] = 0;
	var->ret[var->i] = 0;
	ft_strcat(var->ret, tmp);
	free(tmp);
}
