/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 17:19:27 by bfrochot          #+#    #+#             */
/*   Updated: 2017/03/03 17:25:10 by bfrochot         ###   ########.fr       */
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
}