/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 16:39:32 by mleclair          #+#    #+#             */
/*   Updated: 2017/04/30 18:59:07 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

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

int		bs_strstr(char *big, char *little)
{
	int i;
	int j;

	i = -1;
	while (++i < (int)ft_strlen(big) - (int)ft_strlen(little))
	{
		j = -1;
		while (++j != -1)
		{
			if (bs_str(big, i + j, little[j]) == 0)
				break ;
			if (j == (int)ft_strlen(little) - 1)
				return (i);
		}
	}
	return (-1);
}

int		cmprev(char *str, char *tofind)
{
	int cut;

	cut = bs_strstr(str, tofind);
	if (cut == -1)
		return (-1);
	env()->inp1 = ft_strsub(str, 0, cut);
	env()->inp2 = ft_strdup(str + cut + ft_strlen(tofind));
	return (1);
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

void	extract_heredoc(t_env *env)
{
	int i;
	int j;

	i = 0;
	while (env->input[i] && env->input[i] != '<')
		++i;
	j = i + 2;
	while (env->input[j] == ' ' || env->input[j] == '\t')
		++j;
	while (ft_isalpha(env->input[j]))
		++j;
	free(env->inp2);
	env->inp2 = ft_strcdup(env->input + i, j);
	ft_remstr(env->input, i, j);
	free(env->inp1);
	env->inp1 = ft_strdup(env->input);
}

int		parserror(t_env *env)
{
	int i;

	i = 0;
	if (strstr_bool("&&&", ft_strdup(env->input), 0) == 1)
		i = -1;
	if (strstr_bool("|||", ft_strdup(env->input), 0) == 1)
		i = -1;
	if (strstr_bool("|&|", ft_strdup(env->input), 0) == 1)
		i = -1;
	if (strstr_bool("&|&", ft_strdup(env->input), 0) == 1)
		i = -1;
	if (i == -1)
		error(-15, NULL, NULL);
	return (i);
}
