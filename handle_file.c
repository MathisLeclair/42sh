/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 17:20:45 by tgauvrit          #+#    #+#             */
/*   Updated: 2017/03/06 15:06:44 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

static void	strip_comments(char *str)
{
	int i;
	int len;
	int quote;

	if (*str == '#')
		*str = 0;
	if (*str == '#')
		return ;
	i = 0;
	quote = 0;
	len = ft_strlen(str);
	while (++i < len)
	{
		if ((str[i] == '\'' || str[i] == '\"') && (quote % (str[i] % 6)) == 0)
			quote ^= str[i] % 6;
		if (str[i] == '#' && quote == 0 && str[i - 1] != '\\')
			str[i] = '\0';
		else if (str[i] == '#' && quote == 0 && str[i - 1] == '\\')
		{
			ft_strcpy(str + i - 1, str + i);
			--i;
		}
	}
}

void		handle_file(int ac, char **av, t_env *env)
{
	int		fd;
	char	*input;

	if (ac < 2)
		return ;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("shell: %s: no such file\n", av[1]);
		exit(EXIT_FAILURE);
	}
	handle_argv(ac, av, env);
	input = NULL;
	while (get_next_line(fd, &input))
	{
		strip_comments(input);
		if (ft_read(env, input) != 0)
		{
			env_free(env);
			break ;
		}
	}
	close(fd);
	exit(EXIT_SUCCESS);
}
