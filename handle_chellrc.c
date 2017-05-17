/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_chellrc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 17:20:45 by tgauvrit          #+#    #+#             */
/*   Updated: 2017/05/17 21:10:48 by aridolfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

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

void		handle_chellrc(t_env *env)
{
	int		fd;
	char	*tmp;
	char	*input;

	tmp = ft_strdup(env->ev[find_param(env->ev, "HOME")] + 5);
	tmp = ft_strjoinfree(tmp, "/.chellrc", 1);
	if ((fd = open(tmp, O_RDONLY)) < 0)
		return (free(tmp));
	input = NULL;
	while (get_next_line(fd, &input))
	{
		strip_comments(input);
		if (ft_read(env, input, -1, 0) != 0)
			break ;
	}
	close(fd);
	free(tmp);
	return ;
}
