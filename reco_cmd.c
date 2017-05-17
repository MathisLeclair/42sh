/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reco_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 16:31:37 by mleclair          #+#    #+#             */
/*   Updated: 2017/05/17 15:57:31 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

int		ft_reco_cmd4(t_env *env, char **split)
{
	if (ft_strcmp(split[0], "local") == 0)
		print_split(env->loc->ev);
	else if (ft_strcmp(split[0], "aperture") == 0)
		ft_aperture();
	else
	{
		gthash(isbin(split[0]));
		ft_fork(env, split);
	}
	if (split)
		free_double_array(split);
	return (save_env(env));
}

int		ft_reco_cmd3(t_env *env, char **split)
{
	int i;

	i = -1;
	if (ft_strcmp(split[0], "unset") == 0)
	{
		if (split[0] && split[1] && split[1][0] == '-' && split[1][1] == 'v')
			++i;
		while (split[++i])
			suppr_var_env(env->loc, split[i]);
	}
	else if (ft_strcmp(split[0], "export") == 0)
		builtin_export(env, split);
	else if (ft_strcmp(split[0], "hash") == 0)
		builtin_hash(env, split);
	else if (ft_strcmp(split[0], "alias") == 0)
		alias(env, split);
	else if (ft_strfind(split[0], '=') != -1)
		add_local(env, split);
	else
		return (ft_reco_cmd4(env, split));
	if (split)
		free_double_array(split);
	return (save_env(env));
}

int		ft_reco_cmd2(t_env *env, char **split)
{
	if (ft_strcmp(split[0], "Patate") == 0)
	{
		ft_printf("[1]    %s segmentation fault  ./42sh\n",
			env->loc->ev[find_param(env->loc->ev, "UID")] + 4);
		exit(0);
	}
	else if (ft_strcmp(split[0], "exit") == 0)
		ft_exit(split);
	else if (ft_strcmp(split[0], "env") == 0)
		reco_env(env, split, 0, 0);
	else if (ft_strcmp(split[0], "history") == 0)
		history(env, split);
	else if (ft_strcmp(split[0], "read") == 0)
		builtin_read(env, split);
	else
		return (ft_reco_cmd3(env, split));
	if (split)
		free_double_array(split);
	return (save_env(env));
}

int		ft_reco_cmd(t_env *env, int i)
{
	char	**split;

	if (*env->input == '\n')
		return (1);
	split = ft_split_input(env->input);
	if (split[0] == NULL)
	{
		free(split);
		return (0);
	}
	if (ft_strcmp(split[0], "cd") == 0)
		ft_cd(split, env, NULL, ft_strnew(INPUT_SIZE + 4));
	else if (ft_strcmp(split[0], "echo") == 0)
		ft_echo(split);
	else if (ft_strcmp(split[0], "setenv") == 0)
		while (split[++i])
			add_var_to_env(env, split[i]);
	else if (ft_strcmp(split[0], "unsetenv") == 0)
		while (split[++i])
			suppr_var_env(env, split[i]);
	else
		return (ft_reco_cmd2(env, split));
	if (split)
		free_double_array(split);
	return (save_env(env));
}
