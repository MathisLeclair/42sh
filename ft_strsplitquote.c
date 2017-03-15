/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitquote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 16:58:49 by bfrochot          #+#    #+#             */
/*   Updated: 2017/03/15 17:43:17 by bfrochot         ###   ########.fr       */
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
		if (i != 0 && (bs_str(s, i - 1, '\'') || bs_str(s, i - 1, '"')) && done == s[i - 1])
			done = 0;
		else if (i != 0 && (bs_str(s, i - 1, '\'') || bs_str(s, i - 1, '"')) && done == 0)
			done = s[i - 1];
		if (s[i] != c && (i == 0 || bs_str(s, i - 1, c)) && done == 0)
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
		if (done == s[i])
			done = 0;
		else if ((bs_str(s, i, '\'') || bs_str(s, i, '"')) && done == 0)
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
			if (done == ret[i])
				done = 0;
			else if ((bs_str(ret, i, '\'') || bs_str(ret, i, '"')) && done == 0)
				done = ret[i];
			if (ret[i] == '\t' && done == 0)
				ret[i] = ' ';
		}
	return (ret);
}

char		**ft_strsplitquote(char const *s, char c, char t)
{
	char	**a;
	int		nbw;
	int		i;
	char	*input;
	char	*sv;
	int		j;

	i = -1;
	if (s == NULL)
		return (NULL);
	input = ft_tab_space(s, t);
	sv = input;
	nbw = ft_cnt_parts(input, c);
	a = palloc(sizeof(char *) * nbw + 1);
	j = 0;
	while (nbw-- && ++i != -1)
	{
		while (bs_str(input, j, c) && input[j] != '\0')
			j++;
		a[i] = ft_strsub(input + j, 0, ft_wlen(input + j, c));
		j += ft_wlen(input + j, c);
	}
	a[i + 1] = NULL;
	free(sv);
	return (a);
}
