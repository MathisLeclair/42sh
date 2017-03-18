/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 16:39:32 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/18 16:39:59 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		cmprevtruc(t_env *env, char **input)
{
	int i;

	i = ft_strlen(*input);
	if (i <= 2)
		return (0);
	while ((*input)[--i])
	{
		if (((*input)[i] == '&' && (*input)[i - 1] == '&') ||
			((*input)[i] == '|' && (*input)[i - 1] == '|'))
		{
			env->inp1 = ft_strcdup((*input), i - 1);
			env->inp2 = ft_strdup((*input) + i + 1);
			if ((*input)[i] == '&')
			{
				oprt_and(env);
				return (1);
			}
			else
			{
				oprt_or(env);
				return (1);
			}
		}
	}
	return (0);
}

int		cmprev(char *str, char *tofind)
{
	int i;
	int k;

	i = ft_strlen(str);
	if (i < (int)ft_strlen(tofind))
		return (-1);
	while (str[--i])
	{
		k = ft_strlen(tofind);
		while (k - 1 >= 0 && i >= 0 && bs_str(str, i, tofind[k - 1])
			&& isinquote(str, i) == 0)
		{
			--k;
			--i;
		}
		if (k == 0 && ft_strchr(tofind, str[i]) == 0)
		{
			env()->inp1 = ft_strcdup(str, i + 1);
			env()->inp2 = ft_strdup(str + ft_strlen(tofind) + i + 1);
			return (i);
		}
	}
	return (-1);
}

void	extract_rd_output(t_env *env, char *input)
{
	int i;
	int j;
	int u;

	i = 0;
	while (input[i] && input[i] != '<')
		++i;
	j = i + 1;
	while (input[j] == ' ' || input[j] == '\t')
		++j;
	u = j;
	while (input[j] && ft_isascii(input[j]) && (input[j] != ' ' ||
		(input[j] == ' ' && input[j - 1] == '\\')))
		++j;
	free(env->inp2);
	env->inp2 = ft_strcdup(input + u, j - i);
	env->inp2[j - i] = 0;
	ft_remstr(input, i, j);
	free(env->inp1);
	env->inp1 = ft_strdup(input);
}

void	extract_heredoc(t_env *env, char *input)
{
	int i;
	int j;

	i = 0;
	while (input[i] && input[i] != '<')
		++i;
	j = i + 2;
	while (input[j] == ' ' || input[j] == '\t')
		++j;
	while (ft_isalpha(input[j]))
		++j;
	free(env->inp2);
	env->inp2 = ft_strcdup(input + i, j);
	ft_remstr(input, i, j);
	free(env->inp1);
	env->inp1 = ft_strdup(input);
}

int		parserror(t_env *env)
{
	int i;

	i = 0;
	if (strstr_bool("&&&", ft_strdup(env->input)) == 1)
		i = -1;
	if (strstr_bool("|||", ft_strdup(env->input)) == 1)
		i = -1;
	if (strstr_bool("|&|", ft_strdup(env->input)) == 1)
		i = -1;
	if (strstr_bool("&|&", ft_strdup(env->input)) == 1)
		i = -1;
	if (i == -1)
		error(-15, NULL, NULL);
	return (i);
}
