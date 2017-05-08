/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_condition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 17:13:46 by mleclair          #+#    #+#             */
/*   Updated: 2017/05/08 17:37:15 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

int		exec_condition2(t_env *env, t_cond *cond, char **content)
{
	int		pid;
	char	*tmp;

	if ((pid = fork()) == 0)
	{
		tmp = ft_strdup(cond->content);
		parse(env, &tmp, 0);
		free(tmp);
		content = ft_split_input(env->input);
		exit(execve("/bin/test", content, env->ev));
	}
	else
	{
		waitpid(pid, &pid, WUNTRACED);
		if (WEXITSTATUS(pid) != 0)
			return (1);
	}
	return (0);
}

int		exec_condition3(t_env *env, t_cond *cond, char **content)
{
	char	*var_add_group[3];
	char	*tmp;

	content = ft_split_input(cond->content);
	if (content[0] == NULL || content[1] == NULL || content[2] == NULL
		|| ft_strcmp(content[0], "for") || !ft_strlen(content[1])
		|| ft_strcmp(content[2], "in"))
	{
		error(-4, "for condition format error", NULL);
		return (1);
	}
	if (content[3] == NULL && !free_double_array(content))
		return (1);
	var_add_group[0] = content[1];
	var_add_group[1] = content[3];
	var_add_group[2] = NULL;
	tmp = join_split(var_add_group, "=");
	add_var_to_env(env->loc, tmp);
	content[3][0] = '\0';
	free2(tmp, cond->content);
	cond->content = join_split(content, " ");
	free_double_array(content);
	return (0);
}

void	exec_condition4(t_cond *block, t_env *env)
{
	char	*tmp;

	if (block->type == IS_LINE)
	{
		tmp = ft_strdup(block->content);
		parse(env, &tmp, 1);
		free(tmp);
	}
	else
	{
		tmp = ft_strdup(((t_cond*)block->content)->content);
		exec_condition(env, block->content);
		free(((t_cond*)block->content)->content);
		((t_cond*)block->content)->content = tmp;
	}
}

void	exec_condition(t_env *env, t_cond *cond)
{
	t_cond	*block;
	char	*content;

	while (env->bool1 == 0)
	{
		if (cond->type == COND_IF || cond->type == COND_WHILE)
		{
			if (exec_condition2(env, cond, &content) == 1)
				return ;
		}
		else if (cond->type == COND_FOR)
			if (exec_condition3(env, cond, &content) == 1)
				return ;
		block = cond->block;
		while (block != NULL)
		{
			exec_condition4(block, env);
			block = block->block;
		}
		if (cond->type == COND_IF)
			return ;
	}
}
