/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 14:59:10 by tgauvrit          #+#    #+#             */
/*   Updated: 2017/03/16 11:51:10 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

static void	ft_strcat2(char *dest, char *s1, char *s2)
{
	ft_strcat(dest, s1);
	ft_strcat(dest, s2);
}

void		handle_argv(int ac, char **av, t_env *loc, int i)
{
	int		size;
	char	*tmp;

	size = ac;
	while (++i < ac)
		size += ft_strlen(av[i]);
	tmp = palloc(size * sizeof(char));
	*tmp = '\0';
	if (ac > 1)
		ft_strcpy(tmp, av[1]);
	i = 1;
	while (++i < ac)
		ft_strcat2(tmp, " ", av[i]);
	add_pair_to_env(loc, "@", tmp);
	free(tmp);
	tmp = ft_itoa(ac);
	add_pair_to_env(loc, "#", tmp);
	free(tmp);
	i = -1;
	while (++i < ac)
	{
		tmp = ft_itoa(i);
		add_pair_to_env(loc, tmp, av[i]);
		free(tmp);
	}
}
