/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hijack_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 14:34:21 by tgauvrit          #+#    #+#             */
/*   Updated: 2017/05/07 14:37:53 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

t_ssprintf	*hijack_prompt(t_env *env)
{
	if (env->cond == NULL)
		return (ft_sprintf("\e[1;32m%C\e[0;m \e[1;36m%s \e[0m%s",
			L'✈', env->dir, PROMPT));
	else if (env->cond->type == COND_IF)
		return (ft_sprintf(PROMPT_IF));
	else if (env->cond->type == COND_WHILE)
		return (ft_sprintf(PROMPT_WHILE));
	else if (env->cond->type == COND_FOR)
		return (ft_sprintf(PROMPT_FOR));
	else
		return (ft_sprintf(PROMPT_COND));
}

int			hijack_prompt_size(t_env *env)
{
	if (env->cond == NULL)
		return (PROMPT_SIZE);
	else if (env->cond->type == COND_IF)
		return (PROMPT_SIZE_IF);
	else if (env->cond->type == COND_WHILE)
		return (PROMPT_SIZE_WHILE);
	else if (env->cond->type == COND_FOR)
		return (PROMPT_SIZE_FOR);
	else
		return (PROMPT_SIZE_COND);
}
