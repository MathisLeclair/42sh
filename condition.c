/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 18:11:54 by tgauvrit          #+#    #+#             */
/*   Updated: 2017/05/08 17:51:54 by tgauvrit         ###   ########.fr       */
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

char	*join_split(char **split, char *glue)
{
	size_t	size;
	char	*str;
	char	**tmp;

	size = 0;
	tmp = split - 1;
	while (*(++tmp) != NULL)
		size += ft_strlen(*tmp) + ft_strlen(glue);
	str = palloc(sizeof(char) * (size + 1));
	str[0] = '\0';
	tmp = split - 1;
	while (*(++tmp) != NULL)
	{
		ft_strcat(str, *tmp);
		ft_strcat(str, glue);
	}
	str[size - 1] = '\0';
	return (str);
}

void	handle_condition(t_env *env, char *input)
{
	t_cond	*cond;

	cond = env->cond;
	if (cond->block == NULL && ft_strncmp(input, "do ", 3) != 0
		&& ft_strcmp(input, "do") != 0)
		cond->has_block = 0;
	else if (cond->block == NULL && (ft_strncmp(input, "do ", 3) == 0
		|| ft_strcmp(input, "do") == 0))
		input = input + 2;
	while (input[0] == ' ')
		input++;
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
