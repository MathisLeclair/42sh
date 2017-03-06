/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 17:19:27 by bfrochot          #+#    #+#             */
/*   Updated: 2017/03/06 15:09:01 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	set_history(void)
{
	char	*line;
	char	*tmp;
	int		fd;

	env()->history = malloc(sizeof(char *));
	env()->history[0] = 0;
	tmp = malloc(INPUT_SIZE);
	*tmp = 0;
	if (find_param(env()->loc->ev, "HOME") != -1)
		ft_strcat(ft_strcat(tmp, env()->ev[find_param(env()->ev,
		"HOME")] + 5), "/.42shistory");
	fd = open(tmp, O_RDONLY);
	if (fd == -1)
		return ;
	while (get_next_line(fd, &line))
		add_str_to_dstr(&env()->history, line);
	close(fd);
}

void	file_history2(int fd, char *tmp, int *i, char *num)
{
	ft_strcat(tmp, num);
	free(num);
	write(fd, tmp, 5);
	write(fd, "  ", 2);
	write(fd, env()->history[*i] + 7, ft_strlen(env()->history[*i] + 7));
	write(fd, "\n", 1);
	*i += 1;
}

void	file_history(int i, int j, int k)
{
	int		fd;
	char	*tmp;
	char	*num;

	tmp = malloc(INPUT_SIZE);
	*tmp = 0;
	if (find_param(env()->loc->ev, "HOME") != -1)
		ft_strcat(ft_strcat(tmp, env()->ev[find_param(env()->ev,
		"HOME")] + 5), "/.42shistory");
	fd = open(tmp, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	while (env()->history[i])
		++i;
	i = i > 5000 ? i - 5000 : 0;
	while (env()->history[i])
	{
		tmp = malloc(6);
		num = ft_itoa(j);
		k = -1;
		while (++k < 5 - (int)ft_strlen(num))
			tmp[k] = ' ';
		tmp[k] = 0;
		file_history2(fd, tmp, &i, num);
		++j;
	}
	close(fd);
}

void	add_history(t_var *var)
{
	int		i;
	char	*tmp;
	char	*num;

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
	i = 0;
	while (env()->history[i])
		++i;
	if (i != 0 && ft_strcmp(tmp + 7, env()->history[i - 1] + 7))
		add_str_to_dstr(&env()->history, tmp);
	if (i == 0)
		add_str_to_dstr(&env()->history, tmp);
	free(tmp);
	free(num);
}
