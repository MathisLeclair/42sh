/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitquote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 16:58:49 by bfrochot          #+#    #+#             */
/*   Updated: 2017/02/06 17:56:46 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

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
		if (i != 0 && (s[i - 1] == '\'' || s[i - 1] == '"') && done == s[i - 1])
			done = 0;
		else if (i != 0 && (s[i - 1] == '\'' || s[i - 1] == '"') && done == 0)
			done = s[i - 1];
		if (s[i] != c && (i == 0 || s[i - 1] == c) && done == 0)
			nw++;
		++i;
	}
	return (nw);
}

static int	ft_wlen(const char *s, char c)
{
	int	l;
	int	done;

	l = 0;
	done = 0;
	while ((*s != c || (*s == c && done != 0)) && *s)
	{
		if (done == *s)
			done = 0;
		else if ((*s == '\'' || *s == '"') && done == 0)
			done = *s;
		l++;
		s++;
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
			else if ((ret[i] == '\'' || ret[i] == '"') && done == 0)
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

	i = -1;
	if (s == NULL)
		return (NULL);
	input = ft_tab_space(s, t);
	sv = input;
	nbw = ft_cnt_parts(input, c);
	a = palloc(sizeof(char *) * nbw + 1);
	while (nbw-- && ++i != -1)
	{
		while (*input == c && *input != '\0')
			input++;
		a[i] = ft_strsub(input, 0, ft_wlen(input, c));
		input += ft_wlen(input, c);
	}
	a[i + 1] = NULL;
	free(sv);
	return (a);
}
