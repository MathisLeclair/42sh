/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 18:11:54 by tgauvrit          #+#    #+#             */
/*   Updated: 2017/05/07 15:10:29 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

int		do_if_condition(t_env *env, char *input)
{
	if (!ft_strncmp(input, "if ", 3))
		new_condition(COND_IF, env, input);
	else if (!ft_strncmp(input, "while ", 6))
		new_condition(COND_WHILE, env, input);
	else if (!ft_strncmp(input, "for ", 4) && ft_strstr(input, " in ") != NULL)
		new_condition(COND_FOR, env, input);
	else
	{
		return (0);
	}
	return (1);
}

t_cond	*new_block_part(int type, void *content)
{
	t_cond *part;

	part = palloc(sizeof(t_cond));
	part->type = type;
	part->content = content;
	part->block = NULL;
	return (part);
}

void	add_to_block(t_cond *cond, t_env *env, char *input)
{
	t_cond	*block;

	block = cond;
	while (block->block != NULL)
		block = block->block;
	if (do_if_condition(env, input))
	{
		block->block = new_block_part(IS_COND, env->cond);
	}
	else
	{
		block->block = new_block_part(IS_LINE, ft_strdup(input));
	}
}

void	exec_condition(t_env *env, t_cond *cond)
{
	t_cond	*block;
	char	*tmp;
	char	**content;
	int		pid;
	char	*var_add_group[3];

	env->bool1 = 0;
	while (env->bool1 == 0)
	{
		if (cond->type == COND_IF || cond->type == COND_WHILE)
		{
			if ((pid = fork()) == 0)
			{
				tmp = ft_strdup(cond->content);
				parse(env, &tmp, 0);
				free(tmp);
				content = ft_split_input(env->input);
				exit(execve("/bin/test", content, env->ev));
				free_double_array(content);
			}
			else
			{
				waitpid(pid, &pid, WUNTRACED);
				if (WEXITSTATUS(pid) != 0)
					return ;
			}
		}
		else if (cond->type == COND_FOR)
		{
			content = ft_split_input(cond->content);
			if (content[0] == NULL || content[1] == NULL || content[2] == NULL
				|| ft_strcmp(content[0], "for") || !ft_strlen(content[1])
				|| ft_strcmp(content[2], "in"))
			{
				error(-4, "for condition format error", NULL);
				return ;
			}
			if (content[3] == NULL)
				return ;
			var_add_group[0] = content[1];
			var_add_group[1] = content[3];
			var_add_group[2] = NULL;
			tmp = join_split(var_add_group, "=");
			add_var_to_env(env->loc, tmp);
			free(tmp);
			content[3][0] = '\0';
			free(cond->content);
			cond->content = join_split(content, " ");
			free_double_array(content);
		}
		block = cond->block;
		while (block != NULL)
		{
			if (block->type == IS_LINE)
			{
				parse(env, (char**)(&(block->content)), 1);
			}
			else
			{
				exec_condition(env, block->content);
			}
			block = block->block;
		}
		if (cond->type == COND_IF)
			return ;
	}
}

void	handle_condition(t_env *env, char *input)
{
	t_cond	*cond;

	cond = env->cond;
	if (cond->block == NULL && ft_strncmp(input, "do ", 3) != 0)
		cond->has_block = 0;
	else if (cond->block == NULL && ft_strncmp(input, "do ", 3) == 0)
		input = input + 3;
	if (ft_strcmp(input, "done") == 0)
		cond->has_block = 0;
	else
		add_to_block(cond, env, input);
	while (env->cond->has_block == 0 && env->cond->parent != NULL)
		env->cond = env->cond->parent;
	if (env->cond->has_block == 0)
	{
		cond = env->cond;
		env->cond = env->cond->parent;
		exec_condition(env, cond);
		destroy_condition(cond);
	}
}
