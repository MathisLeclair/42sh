/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 13:36:51 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/23 13:08:59 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		whereis(char *buff)
{
	int i;

	i = 0;
	while (buff[i])
	{
		if (buff[i] == '\n')
			return (i + 1);
		++i;
	}
	return (-1);
}

char	*strresizee(char *s, int add)
{
	int		len;
	char	*tmp;

	len = ft_strlen(s);
	tmp = palloc(sizeof(char) * (add + len + 1));
	ft_strcpy(tmp, s);
	ft_bzero(tmp + len, add + 1);
	free(s);
	return (tmp);
}

void	ft_filltruc(char **line, char *buff, int line_len)
{
	line_len = whereis(buff);
	if (line_len == -1)
		line_len = ft_strlen(buff) + 1;
	*line = palloc(sizeof(char) * line_len);
	ft_strncpy(*line, buff, line_len);
	(*line)[line_len - 1] = 0;
	ft_strcpy(buff, buff + line_len);
}

int		get_next_line(const int fd, char **line)
{
	static char	*buff;
	int			where;
	int			ret;
	int			len;

	if (buff == NULL)
		buff = ft_strnew(BUFF_SIZE);
	where = -1;
	while (where < 0)
	{
		buff = strresizee(buff, BUFF_SIZE);
		len = ft_strlen(buff);
		ret = read(fd, buff + len, BUFF_SIZE);
		if (ret == -1)
			return (-1);
		buff[len + ret] = 0;
		if (ret != 0)
			where = whereis(buff);
		else
			where = 0;
	}
	if (ft_strlen(buff) == 0 && ret == 0)
		return (0);
	ft_filltruc(line, buff, 0);
	return (1);
}
