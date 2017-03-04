/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 17:19:27 by bfrochot          #+#    #+#             */
/*   Updated: 2017/03/04 13:43:11 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	set_history(void)
{
	char	*line;
	int		fd;

	env()->history = malloc(sizeof(char *));
	env()->history[0] = 0;
	fd = open("/tmp/.42shhistory", O_RDONLY);
	if (fd == -1)
		return ;
	while (get_next_line(fd, &line))
		add_str_to_dstr(&env()->history, line);
	close(fd);
}

void	file_history(void)
{
	int		fd;
	int		i;
	int		j;
	int		k;
	char	*tmp;
	char	*num;

	fd = open("/tmp/.42shhistory", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	i = 0;
	while (env()->history[i])
		++i;
	i = i > 5000 ? i - 5000 : 0;
	j = 0;
	while (env()->history[i])
	{
		tmp = malloc(6);
		num = ft_itoa(j);
		k = -1;
		while (++k < 5 - (int)ft_strlen(num))
			tmp[k] = ' ';
		tmp[k] = 0;
		ft_strcat(tmp, num);
		free(num);
		write(fd, tmp, 5);
		write(fd, "  ", 2);
		write(fd, env()->history[i] + 7, ft_strlen(env()->history[i] + 7));
		write(fd, "\n", 1);
		++i;
		++j;
	}
	close(fd);
}
