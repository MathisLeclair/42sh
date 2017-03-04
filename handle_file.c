/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 17:20:45 by tgauvrit          #+#    #+#             */
/*   Updated: 2017/03/04 18:42:22 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	handle_file(int ac, char **av, t_env *env)
{
	int		fd;
	char	*input;

	if (ac < 2)
		return ;
	// is file?
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("shell: %s: no such file\n", av[1]);
		exit(EXIT_FAILURE);
	}
	//argv
	handle_argv(ac, av, env);
	//pass file to input
	input = NULL;
	while (get_next_line(fd, &input))
	{
		if (ft_read(env, input) != 0)
		{
			env_free(env);
			break ;
		}
	}
	close(fd);
	exit(EXIT_SUCCESS);
}