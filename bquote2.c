/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bquote2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 11:58:01 by mleclair          #+#    #+#             */
/*   Updated: 2017/05/07 16:35:41 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

void	ft_read3(char **input, t_env *env)
{
	env->bool1 = 0;
	env->bool2 = 0;
	if (*input == NULL)
		*input = termcaps(hijack_prompt(env), hijack_prompt_size(env), 0);
}

int		ft_read2(int u, char **input, t_env *env)
{
	env->bool1 = 0;
	if (env->bool1 == 1)
	{
		env->bool2 = 1;
		free(*input);
		return (0);
	}
	while ((u = verif_quote(input, -1, 0, 0)) != 0)
		if (u == -1)
		{
			parse(env, input, 1);
			free(*input);
			return (0);
		}
	if (env->bool2 == 1 && !ft_read(env, *input, -1, 0))
		return (0);
	return (666);
}

int		ver_dquote_t2(char *str)
{
	int o;
	int k;
	int i;

	o = 0;
	k = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '`')
			o = o == 1 ? 0 : 1;
		if (str[i] == '(')
			k += 1;
		if (str[i] == ')')
			k -= 1;
	}
	if (o == 1 || k != 0)
	{
		free(str);
		error(-15, NULL, NULL);
		return (-1);
	}
	return (0);
}

int		ver_sub_2(t_env *env, char **input)
{
	int i;
	int u;

	i = -1;
	u = 0;
	while (env->input[++i])
	{
		if (env->input[i] == ')' && u == 0)
			return (-1);
		if (env->input[i] == '(')
			u += 1;
		else if (env->input[i] == ')')
			u -= 1;
	}
	if (u != 0)
	{
		error(-15, NULL, NULL);
		return (-1);
	}
	*input[0] = 0;
	ft_strcat(*input, env->input);
	return (0);
}

void	retvalue_into_loc(t_env *env, int i)
{
	char *tmp;
	char *rmp2;

	env->lastret = i;
	tmp = palloc(300);
	tmp[0] = 0;
	ft_strcat(tmp, "?=");
	ft_strcat(tmp, rmp2 = ft_itoa(i));
	free(rmp2);
	add_var_to_env(env, tmp);
	free(tmp);
}
