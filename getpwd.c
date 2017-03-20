/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 13:26:35 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/20 14:09:28 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

void	getpwd(char *pwd)
{
	pwd[0] = 'P';
	pwd[1] = 'W';
	pwd[2] = 'D';
	pwd[3] = '=';
	getcwd(pwd + 4, INPUT_SIZE);
}

void	remove_nl(char **str)
{
	int i;

	if (!(*str))
		return ;
	i = -1;
	while ((*str)[++i])
		if ((*str)[i] == '\n')
			(*str)[i] = ' ';
	(*str)[ft_strlen(*str) - 1] = 0;
}
