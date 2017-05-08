/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 15:10:15 by mleclair          #+#    #+#             */
/*   Updated: 2017/05/08 17:45:55 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

int		find_param(char **split, char *str)
{
	int i;
	int j;

	i = 0;
	while (split[i])
	{
		j = 0;
		while (str[j] && str[j] != '=' && str[j] == split[i][j])
			j++;
		if ((str[j] == '=' || str[j] == 0) && split[i][j] == '=')
			return (i);
		++i;
	}
	return (-1);
}

void	modif_var_env(t_env *env, char *str, int i)
{
	char	*new_para;
	int		j;

	j = 0;
	while (str[j] && str[j] != '=')
		++j;
	if (j != 0 && str[j] && str[j + 1])
	{
		new_para = ft_strdup(str);
		free(env->ev[i]);
		env->ev[i] = new_para;
	}
}

void	add_var_to_env(t_env *env, char *str)
{
	int		i;
	int		j;
	char	**new_env;

	i = find_param(env->ev, str);
	if (i == -1 && !(j = 0) && ft_isalpha(str[0]))
	{
		while (str[j] && str[j] != '=')
			++j;
		if (j != 0 && str[j] && str[j + 1] && !(i = 0))
		{
			while (env->ev[i])
				++i;
			new_env = palloc(sizeof(char *) * (i + 2));
			new_env[i + 1] = 0;
			i = -1;
			while (env->ev[++i])
				new_env[i] = env->ev[i];
			new_env[i] = ft_strdup(str);
			free(env->ev);
			env->ev = new_env;
		}
	}
	else if (i != -1)
		modif_var_env(env, str, i);
}

void	add_pair_to_env(t_env *env, char *key, char *val)
{
	char *tmp;

	tmp = palloc(ft_strlen(key) + ft_strlen(val) + 2);
	*tmp = '\0';
	ft_strcat(tmp, key);
	ft_strcat(tmp, "=");
	ft_strcat(tmp, val);
	add_var_to_env(env, tmp);
	free(tmp);
}

void	suppr_var_env(t_env *env, char *str)
{
	int i;

	i = find_param(env->ev, str);
	if (i != -1)
	{
		free(env->ev[i]);
		while (env->ev[i] && ++i)
			env->ev[i - 1] = env->ev[i];
	}
}
