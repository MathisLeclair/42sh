/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 16:13:00 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/23 14:03:09 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

char	**auto_possibilities3(char **ac, t_env *ev, DIR *dir)
{
	ev->find = add_bs(ev->find);
	ac = malloc(sizeof(char *) * 2);
	ac[0] = ft_strdup(ft_strcat(ev->find, "/"));
	ac[1] = 0;
	closedir(dir);
	return (ac);
}

char	**auto_possibilities2(char **ac, DIR *dir, t_env *ev)
{
	ac_target(ev->find, &ac);
	if (ac[0] == 0)
		ac[0] = ft_strdup(ev->find);
	if (dir)
		closedir(dir);
	return (ac);
}

char	**auto_possibilities(char pwd, t_env *ev)
{
	char	**ac;
	char	*find_lwc;
	DIR		*dir;

	dir = NULL;
	ac = 0;
	find_lwc = ev->input;
	ev->input = ev->find;
	ft_dollar(ev, -1, 0);
	ev->find = ev->input;
	ev->input = find_lwc;
	if (!bs_str(ev->find, ft_strlen(ev->find) - 1, '/')
		&& (dir = opendir(ev->find)))
		return (auto_possibilities3(ac, ev, dir));
	if (ev->find[0] == '/' || (ev->find[0] == '.' && ev->find[1] == '/') || (dir = opendir(ev->find)))
		return (auto_possibilities2(ac, dir, ev));
	find_lwc = to_lwcase(ev->find);
	if (pwd == 0)
		ac = ac_cmd(find_lwc, ev);
	else
		ac = ac_pwd(find_lwc, palloc(INPUT_SIZE));
	free(find_lwc);
	return (ac);
}

char	*finder(char *input, int pos)
{
	char	*find;
	int		i;
	int		j;

	while (pos != 0 && !bs_str(input, pos, ' ') && !bs_str(input, pos, '\t'))
		pos--;
	i = pos == 0 ? 0 : pos + 1;
	j = 0;
	while (input[i] && !bs_str(input, i++, ' '))
		++j;
	find = malloc(j + 2);
	find[j] = 0;
	find[j + 1] = 0;
	i = 0;
	pos = pos == 0 ? pos - 1 : pos;
	while (input[++pos] && !bs_str(input, pos, ' '))
		find[i++] = input[pos];
	return (find);
}

char	ft_strcmp_beg(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		++i;
	if (str1[i] && str2[i])
		return (0);
	return (1);
}
