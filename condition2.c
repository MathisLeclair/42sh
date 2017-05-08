/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:08:14 by tgauvrit          #+#    #+#             */
/*   Updated: 2017/05/08 16:28:28 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

void	new_condition(int type, t_env *env, char *input)
{
	t_cond	*cond;

	cond = palloc(sizeof(t_cond));
	cond->type = type;
	cond->content = ft_strdup(input);
	cond->block = NULL;
	cond->has_block = 1;
	cond->parent = env->cond;
	env->cond = cond;
}

void	destroy_condition(t_cond *cond)
{
	t_cond	*block;
	t_cond	*tmp;

	block = cond->block;
	while (block != NULL)
	{
		if (block->type == IS_LINE)
			free(block->content);
		else
			destroy_condition(block->content);
		tmp = block;
		block = block->block;
		free(tmp);
	}
	free(cond->content);
	free(cond);
}
