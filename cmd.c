/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 13:28:38 by mleclair          #+#    #+#             */
/*   Updated: 2017/02/11 16:25:41 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	ft_suppr_quotes(char *str, int i, int j)
{
	char	quote;

	while (str[i] && (quote = str[i]))
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			while (str[++i] && str[i] != quote)
				str[j++] = str[i];
			if (str[i] && str[i + 1])
				++i;
			else
				break ;
		}
		if (str[i] != '\'' && str[i] != '\"')
		{
			str[j] = str[i];
			++i;
			++j;
		}
	}
	str[j] = 0;
}

char	**ft_split_input(char *input)
{
	int		i;
	char	**a;

	i = -1;
	a = ft_strsplitquote(input, ' ', 1);
	i = -1;
	while (a[++i])
		ft_suppr_quotes(a[i], 0, 0);
	return (a);
}

int		ft_reco_cmd2(char *input, t_env *env, char **split)
{
	if (ft_strcmp(input, "Patate") == 0)
		ft_putstr("[1]    35674 segmentation fault  ./minishell\n");
	else if (ft_strcmp(split[0], "exit") == 0)
	{
		free_double_array(split);
		return (0);
	}
	else if (ft_strcmp(split[0], "env") == 0)
		reco_env(env, split, 0, 0);
	else if (ft_strcmp(split[0], "history") == 0)
		history(env, split);
	else
		ft_fork(env, split);
	if (split)
		free_double_array(split);
	return (save_env(env));
}

int		ft_reco_cmd(t_env *env)
{
	char	**split;
	int		i;
	char	*reg;

	reg = 0;
	if (*env->input == '\n')
		return (1);
	split = ft_split_input(env->input);
	if (!(i = 0) && ft_strcmp(split[0], "cd") == 0)
		ft_cd(split, env, reg, ft_strnew(INPUT_SIZE + 4));
	else if (ft_strcmp(split[0], "echo") == 0)
		ft_echo(split);
	else if (ft_strcmp(split[0], "setenv") == 0)
		while (split[++i])
			add_var_to_env(env, split[i]);
	else if (ft_strcmp(split[0], "unsetenv") == 0)
		while (split[++i])
			suppr_var_env(env, split[i]);
	else if (ft_strcmp(split[0], "aperture") == 0)
		ft_aperture();
	else
		return (ft_reco_cmd2(env->input, env, split));
	if (split)
		free_double_array(split);
	return (save_env(env));
}

int		ft_read(t_env *env)
{
	char	*input;
	char	**inputspl;
	int		i;

	if (get_next_line(1, &input) == 0)
		error(-6, NULL, NULL);
	if (verif_quote(input, 0) == -1)
		return (0);
	inputspl = ft_strsplitquote(input, ';', 0);
	free(input);
	i = -1;
	while (inputspl && inputspl[++i])
	{
		env->input = ft_strdup(inputspl[i]);
		if (ft_strchr(env->input, '$'))
			ft_dollar(env, -1, 0);
		if (ft_strchr(env->input, '~'))
			ft_tilde(env, -1, 0);
		if (!ft_reco_cmd(env) && (env->input = NULL) == NULL
		&& free_double_array(inputspl))
			ft_exit();
		free(env->input);
		env->input = NULL;
	}
	free_double_array(inputspl);
	ft_printf("\e[1;32m%C\e[0;m \e[1;36m%s \e[0m%s", L'✈', env->dir, PROMPT);
	return (0);
}
