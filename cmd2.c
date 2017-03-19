/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 16:36:23 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/18 16:36:46 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

void	ft_suppr_quotes(char **str, int i, int j)
{
	char	quote;
	char	*tmp;

	tmp = ft_strdup(*str);
	while ((*str)[i])
	{
		if (bs_str(*str, i, '\'') || bs_str(*str, i, '\"'))
		{
			quote = (*str)[i];
			while ((*str)[++i] && !bs_str(*str, i, quote))
				tmp[j++] = (*str)[i];
			if ((*str)[i])
				++i;
		}
		else
		{
			tmp[j] = (*str)[i];
			++i;
			++j;
		}
	}
	tmp[j] = 0;
	free(*str);
	*str = tmp;
}

void	ft_suppr_bs(char **str)
{
	int		i;
	int		j;
	char	*new;

	i = -1;
	j = 0;
	while ((*str)[++i])
		if ((*str)[i] == '\\' && (*str)[i + 1])
		{
			j++;
			i++;
		}
	new = palloc(ft_strlen(*str) - j + 1);
	i = 0;
	j = -1;
	while ((*str)[i])
	{
		if ((*str)[i] == '\\' && (*str)[i + 1])
			++i;
		new[++j] = (*str)[i];
		++i;
	}
	new[++j] = 0;
	free(*str);
	*str = new;
}

char	**ft_split_input(char *input)
{
	int		i;
	char	**a;

	i = -1;
	a = ft_strsplitquote(input, ' ', 1);
	i = -1;
	while (a[++i])
	{
		ft_suppr_quotes(a + i, 0, 0);
		ft_suppr_bs(a + i);
	}
	return (a);
}

void	extracredir(t_env *e, int i, int j)
{
	char	*temp;

	i = ft_strlen(e->input);
	while (e->input[--i] && i >= 0)
	{
		j = i;
		if (e->input[j] == '>')
		{
			if (j - 1 >= 0 && --j && e->input[j] == '>')
				--i;
			j += 2;
			if (i - 1 >= 0 && ft_isdigit(e->input[i - 1]) && i - 2 >= 0
				&& e->input[i - 2] == ' ')
				i--;
			while (e->input[j] && e->input[j] == ' ')
				++j;
			while (e->input[j] && ((e->input[j] >= 33 && e->input[j] <= 126)
				|| (e->input[j] == ' ' && j > 0 && e->input[j - 1] == '\\')))
				++j;
			temp = ft_strcdup(e->input + i, j - i);
			e->redir = temp;
			ft_remstr(e->input, i, j);
			return ;
		}
	}
}

int		isinquote(char *input, int i)
{
	int u;

	u = 0;
	while (input[i])
	{
		--i;
		if ((input[i] == '"' || input[i] == '\'') &&
			((i > 1 && input[i - 1] != '\\') || i < 1))
			u = -1;
	}
	return (u);
}
