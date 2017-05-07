/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:08:14 by tgauvrit          #+#    #+#             */
/*   Updated: 2017/05/07 15:10:34 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

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
		{
			free(block->content);
		}
		else
		{
			destroy_condition(block->content);
		}
		tmp = block;
		block = block->block;
		free(tmp);
	}
	free(cond->content);
	free(cond);
}
