/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 16:11:09 by mleclair          #+#    #+#             */
/*   Updated: 2017/05/02 13:08:08 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

char	*add_bs(char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\\' || str[i] == ' ' || str[i] == '\t' || str[i] == '>'
		|| str[i] == '<' || str[i] == '"' || str[i] == '\'' || str[i] == ';' ||
		str[i] == '|' || str[i] == '&' || str[i] == '$' || str[i] == '*'
		|| str[i] == '!' || str[i] == '(' || str[i] == ')')
		{
			tmp = palloc(ft_strlen(str) + 2);
			*tmp = 0;
			ft_strcat(tmp, str);
			tmp[i] = '\\';
			tmp[i + 1] = 0;
			ft_strcat(tmp, str + i);
			++i;
			free(str);
			str = tmp;
		}
	}
	return (str);
}

int		strstr_bool(char *find, char *search_in_lc, int i)
{
	int			j;
	long int	f_len;

	if ((f_len = ft_strlen(find)) == 0)
	{
		free(search_in_lc);
		return (1);
	}
	while (search_in_lc[i])
		if (search_in_lc[i] == find[0])
		{
			j = -1;
			while (search_in_lc[i] && search_in_lc[i] == find[++j])
				++i;
			if (f_len == j)
			{
				free(search_in_lc);
				return (1);
			}
		}
		else
			++i;
	free(search_in_lc);
	return (0);
}

char	*to_lwcase(char *str)
{
	int		i;
	char	*str_lc;

	str_lc = ft_strdup(str);
	i = -1;
	while (str_lc[++i])
		if (str_lc[i] >= 'A' && str_lc[i] <= 'Z')
			str_lc[i] = str_lc[i] - 'A' + 'a';
	return (str_lc);
}

void	add_str_to_dstr(char ***dstr, char *str)
{
	int		i;
	char	**new_dtr;

	i = 0;
	while ((*dstr)[i])
		++i;
	new_dtr = palloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((*dstr)[i])
	{
		new_dtr[i] = (*dstr)[i];
		++i;
	}
	new_dtr[i] = ft_strdup(str);
	new_dtr[i + 1] = 0;
	free(*dstr);
	*dstr = new_dtr;
}

void	ft_ac_cmd_build(char ***ac, char *find)
{
	if (strstr_bool(find, ft_strdup("cd"), 0))
		add_str_to_dstr(ac, "cd");
	if (strstr_bool(find, ft_strdup("aperture"), 0))
		add_str_to_dstr(ac, "aperture");
	if (strstr_bool(find, ft_strdup("unsetenv"), 0))
		add_str_to_dstr(ac, "unsetenv");
	if (strstr_bool(find, ft_strdup("setenv"), 0))
		add_str_to_dstr(ac, "setenv");
	if (strstr_bool(find, ft_strdup("exit"), 0))
		add_str_to_dstr(ac, "exit");
	if (strstr_bool(find, ft_strdup("Patate"), 0))
		add_str_to_dstr(ac, "Patate");
	if (strstr_bool(find, ft_strdup("env"), 0))
		add_str_to_dstr(ac, "env");
	if (strstr_bool(find, ft_strdup("local"), 0))
		add_str_to_dstr(ac, "local");
	if (strstr_bool(find, ft_strdup("unset"), 0))
		add_str_to_dstr(ac, "unset");
	if (strstr_bool(find, ft_strdup("export"), 0))
		add_str_to_dstr(ac, "export");
	if (strstr_bool(find, ft_strdup("set"), 0))
		add_str_to_dstr(ac, "set");
	if (strstr_bool(find, ft_strdup("history"), 0))
		add_str_to_dstr(ac, "history");
}
