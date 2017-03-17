/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitquote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 16:58:49 by bfrochot          #+#    #+#             */
/*   Updated: 2017/03/17 15:31:03 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

char		bs_str(const char *str, int i, char c)
{
	char t;

	t = 0;
	if (str[i] != c)
		return (0);
	else
		while (i-- != 0 && str[i] == '\\')
			t = t == 0 ? 1 : 0;
	if (t == 1)
		return (0);
	return (1);
}

static int	ft_cnt_parts(const char *s, char c)
{
	int i;
	int nw;
	int	done;

	i = 0;
	nw = 0;
	done = 0;
	while (s[i])
	{
		if (i != 0 && bs_str(s, i - 1, done == '(' ? ')' : done))
			done = 0;
		else if (i != 0 && (bs_str(s, i - 1, '\'') || bs_str(s, i - 1, '"') || bs_str(s, i - 1, '(')) && done == 0)
			done = s[i - 1];
		if (!bs_str(s, i, c) && (i == 0 || bs_str(s, i - 1, c)) && done == 0)
			nw++;
		++i;
	}
	return (nw);
}

static int	ft_wlen(const char *s, char c)
{
	int	l;
	int	done;
	int i;

	i = 0;
	l = 0;
	done = 0;
	while ((!bs_str(s, i, c) || (bs_str(s, i, c) && done != 0)) && s[i])
	{
		if (bs_str(s, i, done == '(' ? ')' : done))
			done = 0;
		else if ((bs_str(s, i, '\'') || bs_str(s, i, '"') || bs_str(s, i, '(')) && done == 0)
			done = s[i];
		l++;
		i++;
	}
	return (l);
}

char		*ft_tab_space(const char *str, char t)
{
	char	*ret;
	int		i;
	int		done;

	ret = ft_strdup(str);
	if (ret == NULL)
		return (NULL);
	i = -1;
	done = 0;
	if (t)
		while (ret[++i])
		{
			if (bs_str(ret, i, done == '(' ? ')' : done))
				done = 0;
			else if ((bs_str(ret, i, '\'') || bs_str(ret, i, '"') || bs_str(ret, i, '(')) && done == 0)
				done = ret[i];
			if (bs_str(ret, i, '\t') && done == 0)
				ret[i] = ' ';
		}
	return (ret);
}

char		**ft_strsplitquote(char const *s, char c, char t)
{
	char	**a;
	int		nbw;
	int		i[2];
	char	*input;
	char	*sv;

	i[0] = -1;
	if (s == NULL)
		return (NULL);
	input = ft_tab_space(s, t);
	sv = input;
	nbw = ft_cnt_parts(input, c);
	a = palloc(sizeof(char *) * nbw + 1);
	i[1] = 0;
	while (nbw-- && ++i[0] != -1)
	{
		while (bs_str(input, i[1], c) && input[i[1]] != '\0')
			i[1]++;
		a[i[0]] = ft_strsub(input + i[1], 0, ft_wlen(input + i[1], c));
		i[1] += ft_wlen(input + i[1], c);
	}
	a[i[0] + 1] = NULL;
	free(sv);
	return (a);
}
