/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aridolfi <aridolfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 14:06:03 by aridolfi          #+#    #+#             */
/*   Updated: 2017/05/17 21:10:59 by aridolfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

static char		**parse_alias(char *str_alias)
{
	int		i;
	char	**ret;

	i = ft_strfind(str_alias, '=');
	ret = palloc(sizeof(char *) * 3);
	ret[0] = ft_strsub(str_alias, 0, i);
	ret[1] = ft_strsub(str_alias, (i + 1), ft_strlen(str_alias + (i + 1)));
	ret[2] = NULL;
	return (ret);
}

static void		rplc_alias(t_env *env, char **split_alias)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (ft_iswhitespace(env->input[i]))
		i++;
	while (env->input[i] && env->input[i] != split_alias[0][0])
		i++;
	tmp = ft_strcdup(env->input, i);
	free_swap(&tmp, ft_strjoin(tmp, split_alias[1]));
	free_swap(&tmp, ft_strjoin(tmp, env->input + i
		+ ft_strlen(split_alias[0])));
	free_swap(&(env->input), tmp);
}

void			sh_alias(t_env *env)
{
	int		i;
	char	**split;
	char	**split_alias;

	i = 0;
	if (*env->input == '\n')
		return ;
	split = ft_split_input(env->input);
	if (split[0] == NULL)
		return (free(split));
	while (env->alias[i])
	{
		split_alias = parse_alias(env->alias[i]);
		if (ft_strcmp(split[0], split_alias[0]) == 0)
		{
			rplc_alias(env, split_alias);
			free_double_array(split_alias);
			break ;
		}
		free_double_array(split_alias);
		i++;
	}
	free_double_array(split);
}
