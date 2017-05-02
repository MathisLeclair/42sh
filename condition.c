/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 18:11:54 by tgauvrit          #+#    #+#             */
/*   Updated: 2017/04/01 18:03:12 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

// # define IS_LINE 0
// # define IS_COND 1
// # define COND_IF 2
// # define COND_WHILE 4
// # define COND_FOR 8

// typedef struct	s_cond
// {
// 	int				type;
// 	char			*content;
// 	struct s_cond	*block;
// 	struct s_cond	parent;
// }				t_cond

char	**dup_split(char **split)
{
	size_t	i;
	char	**new;

	i = 0;
	while (split[i] != NULL)
		i++;
	new = palloc(sizeof(char*) * (i + 1));
	new[i] = NULL;
	while (i-- != 0)
		new[i] = ft_strdup(split[i]);
	return (new);
}

char	*join_split(char **split, char *glue)
{
	size_t	size;
	char	*str;
	char	**tmp;

	// ft_putendl("join_split 1");
	size = 0;
	tmp = split - 1;
	while (*(++tmp) != NULL)
		size += ft_strlen(*tmp) + ft_strlen(glue);
	// ft_putendl("join_split 2");
	str = palloc(sizeof(char) * (size + 1));
	str[0] = '\0';
	tmp = split - 1;
	// ft_putendl("join_split 3");
	while (*(++tmp) != NULL)
	{
		ft_strcat(str, *tmp);
		ft_strcat(str, glue);
	}
	str[size - 1] = '\0';
	// ft_putendl("join_split 4");
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
	// ENV CURRENT CONDITION IS MODIFIED HERE!!!
	cond->parent = env->cond;
	env->cond = cond;
}

void	destroy_condition(t_cond *cond)
{
	t_cond	*block;
	t_cond	*tmp;

	// ft_putendl("destroy_condition 1");
	block = cond->block;
	while (block != NULL)
	{
		// ft_putendl("destroy_condition 2");
		if (block->type == IS_LINE)
		{
			// ft_putendl("destroy_condition 3.1");
			free(block->content);
			// ft_putendl("destroy_condition 4.1");
		}
		else
		{
			// ft_putendl("destroy_condition 3.2");
			destroy_condition(block->content);
			// ft_putendl("destroy_condition 4.2");
		}
		tmp = block;
		block = block->block;
		free(tmp);
	}
	free(cond->content);
	free(cond);
}

int		do_if_condition(t_env *env, char *input)
{
	// ft_putendl("do_if_condition 1");
	if (!ft_strncmp(input, "if ", 3))
		new_condition(COND_IF, env, input);
	else if (!ft_strncmp(input, "while ", 6))
		new_condition(COND_WHILE, env, input);
	else if (!ft_strncmp(input, "for ", 4))
		new_condition(COND_FOR, env, input);
	else
	{
		// ft_putendl("do_if_condition 2.1");
		return (0);
	}
	// ft_putendl("do_if_condition 2.2");
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

void	add_to_block(t_cond *cond, t_env *env, char **split)
{
	t_cond	*block;

	// ft_putendl("add_to_block 1");
	block = cond;
	// ft_putendl("add_to_block 2");
	while (block->block != NULL)
		block = block->block;
	// ft_putendl("add_to_block 3");
	if (do_if_condition(env, split))
	{
		// ft_putendl("add_to_block 4.1");
		block->block = new_block_part(IS_COND, env->cond);
		// ft_putendl("add_to_block 5.1");
	}
	else
	{
		// ft_putendl("add_to_block 4.2");
		block->block = new_block_part(IS_LINE, join_split(split, " "));
		// ft_putendl("add_to_block 5.2");
	}
	// ft_putendl("add_to_block 6");
}

void	exec_condition(t_env *env, t_cond *cond)
{
	t_cond	*block;
	char	*tmp;
	char	**content;
	int		pid;

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
				// ft_printf("Out: %d\n", WEXITSTATUS(pid));
				if (WEXITSTATUS(pid) != 0)
					return ;
			}
		}
		// ft_putendl("exec_condition 1");
		block = cond->block;
		while (block != NULL)
		{
			// ft_putendl("exec_condition 2");
			if (block->type == IS_LINE)
			{
				// ft_putendl("exec_condition 3.1");
				parse(env, (char**)(&(block->content)), 1);
				// ft_putendl("exec_condition 4.1");
			}
			else
			{
				// ft_putendl("exec_condition 3.2");
				exec_condition(env, block->content);
				// ft_putendl("exec_condition 4.2");
			}
			block = block->block;
		}
		// ft_putendl("exec_condition 5");
		if (cond->type == COND_IF)
			return ;
	}
}

void	handle_condition(t_env *env, char **split)
{
	t_cond	*cond;

	cond = env->cond;
	// ft_putendl("handle_condition 1");
	if (cond->block == NULL && ft_strcmp(split[0], "do") != 0) //   NO DO BLOCK PRESENT
		cond->has_block = 0;
	else if (cond->block == NULL && ft_strcmp(split[0], "do") == 0) // DO BLOCK PRESENT
		split++; // IGNORE 'DO' OF COMMAND, IT'S DONE ITS JOB
	// ft_putendl("handle_condition 2");
	if (ft_strcmp(split[0], "done") == 0)
		cond->has_block = 0;
	else
		add_to_block(cond, env, split);
	// ft_putendl("handle_condition 3");
	while (env->cond->has_block == 0 && env->cond->parent != NULL)
		env->cond = env->cond->parent;
	// ft_putendl("handle_condition 4");
	if (env->cond->has_block == 0)
	{
		cond = env->cond;
		env->cond = env->cond->parent;
		exec_condition(env, cond);
		destroy_condition(cond);
	}
	// ft_putendl("handle_condition 5");
}
