/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 13:34:17 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/10 11:49:26 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	error2(int i, char *str)
{
	if (i == -666)
	{
		ft_putstr("Malloc error! ABORT! ABORT!!!!!!!!\n");
		exit(EXIT_FAILURE);
	}
	else if (i == -9)
		ft_printf("shell: cd: no such file or directory: %s\n", str);
	else if (i == -10)
		ft_printf("shell: cd: string not in pwd: %s\n", str);
	else if (i == -11)
		ft_putstr("shell: No history to display");
	else if (i == -12)
	{
		ft_putstr("\n");
		exit(env()->lastret);
	}
	else if (i == -13)
	{
		ft_remstr(tvar()->ret, 0, ft_strlen(tvar()->ret));
		ft_putstr("\nshell: No such event");
	}
	else if (i == -14)
		ft_putstr("job: Number of job not found\n");
}

void	error(int i, char *str, char *str2)
{
	retvalue_into_loc(env(), 1);
	if (str2)
		free(str2);
	if (i == -1)
		ft_putstr("No such file or directory\n");
	else if (i == -2)
		ft_printf("shell: command not found : %s\n", str);
	else if (i == -3)
		ft_printf("shell error\n");
	else if (i == -4)
		ft_printf("shell: exec format error: %s\n", str);
	else if (i == -5)
		ft_printf("shell: permission denied: %s\n", str);
	else if (i == -6)
	{
		ft_putstr("\n");
		file_history(0, 0, 0);
		exit(EXIT_SUCCESS);
	}
	else if (i == -7)
		ft_putstr("shell: error too many arguments.\n");
	else if (i == -8)
		ft_putstr("shell: cd: HOME not set\n");
	else
		error2(i, str);
}

void	*palloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		error2(-666, NULL);
	return (ptr);
}
