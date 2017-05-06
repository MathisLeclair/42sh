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

// char	**dup_split(char **split)
// {
// 	size_t	i;
// 	char	**new;

// 	i = 0;
// 	while (split[i] != NULL)
// 		i++;
// 	new = palloc(sizeof(char*) * (i + 1));
// 	new[i] = NULL;
// 	while (i-- != 0)
// 		new[i] = ft_strdup(split[i]);
// 	return (new);
// }

// char	*join_split(char **split, char *glue)
// {
// 	size_t	size;
// 	char	*str;
// 	char	**tmp;

	// ft_putendl_fd("join_split 1", env()->fdout);
// 	size = 0;
// 	tmp = split - 1;
// 	while (*(++tmp) != NULL)
// 		size += ft_strlen(*tmp) + ft_strlen(glue);
	// ft_putendl_fd("join_split 2", env()->fdout);
// 	str = palloc(sizeof(char) * (size + 1));
// 	str[0] = '\0';
// 	tmp = split - 1;
	// ft_putendl_fd("join_split 3", env()->fdout);
// 	while (*(++tmp) != NULL)
// 	{
// 		ft_strcat(str, *tmp);
// 		ft_strcat(str, glue);
// 	}
// 	str[size - 1] = '\0';
	// ft_putendl_fd("join_split 4", env()->fdout);
// 	return (str);
// }

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

	// ft_putendl_fd("destroy_condition 1", env()->fdout);
	block = cond->block;
	while (block != NULL)
	{
		// ft_putendl_fd("destroy_condition 2", env()->fdout);
		if (block->type == IS_LINE)
		{
			// ft_putendl_fd("destroy_condition 3.1", env()->fdout);
			free(block->content);
			// ft_putendl_fd("destroy_condition 4.1", env()->fdout);
		}
		else
		{
			// ft_putendl_fd("destroy_condition 3.2", env()->fdout);
			destroy_condition(block->content);
			// ft_putendl_fd("destroy_condition 4.2", env()->fdout);
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
	// ft_putendl_fd("do_if_condition 1", env->fdout);
	if (!ft_strncmp(input, "if ", 3))
		new_condition(COND_IF, env, input);
	else if (!ft_strncmp(input, "while ", 6))
		new_condition(COND_WHILE, env, input);
	else if (!ft_strncmp(input, "for ", 4))
		new_condition(COND_FOR, env, input);
	else
	{
		// ft_putendl_fd("do_if_condition 2.1", env->fdout);
		return (0);
	}
	// ft_putendl_fd("do_if_condition 2.2", env->fdout);
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

	// ft_putendl_fd("add_to_block 1", env->fdout);
	block = cond;
	// ft_putendl_fd("add_to_block 2", env->fdout);
	while (block->block != NULL)
		block = block->block;
	// ft_putendl_fd("add_to_block 3", env->fdout);
	if (do_if_condition(env, input))
	{
		// ft_putendl_fd("add_to_block 4.1", env->fdout);
		block->block = new_block_part(IS_COND, env->cond);
		// ft_putendl_fd("add_to_block 5.1", env->fdout);
	}
	else
	{
		// ft_putendl_fd("add_to_block 4.2", env->fdout);
		block->block = new_block_part(IS_LINE, ft_strdup(input));
		// ft_putendl_fd("add_to_block 5.2", env->fdout);
	}
	// ft_putendl_fd("add_to_block 6", env->fdout);
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
		// ft_putendl_fd("exec_condition 1", env->fdout);
		block = cond->block;
		while (block != NULL)
		{
			// ft_putendl_fd("exec_condition 2", env->fdout);
			if (block->type == IS_LINE)
			{
				// ft_putendl_fd("exec_condition 3.1", env->fdout);
				parse(env, (char**)(&(block->content)), 1);
				// ft_putendl_fd("exec_condition 4.1", env->fdout);
			}
			else
			{
				// ft_putendl_fd("exec_condition 3.2", env->fdout);
				exec_condition(env, block->content);
				// ft_putendl_fd("exec_condition 4.2", env->fdout);
			}
			block = block->block;
		}
		// ft_putendl_fd("exec_condition 5", env->fdout);
		if (cond->type == COND_IF)
			return ;
	}
}

void	handle_condition(t_env *env, char *input)
{
	t_cond	*cond;

	cond = env->cond;
	// ft_putendl_fd("handle_condition 1", env->fdout);
	if (cond->block == NULL && ft_strncmp(input, "do ", 3) != 0) //   NO DO BLOCK PRESENT
		cond->has_block = 0;
	else if (cond->block == NULL && ft_strncmp(input, "do ", 3) == 0) // DO BLOCK PRESENT
		input = input + 3; // IGNORE 'DO' OF COMMAND, IT'S DONE ITS JOB
	// ft_putendl_fd("handle_condition 2", env->fdout);
	if (ft_strcmp(input, "done") == 0)
		cond->has_block = 0;
	else
		add_to_block(cond, env, input);
	// ft_putendl_fd("handle_condition 3", env->fdout);
	while (env->cond->has_block == 0 && env->cond->parent != NULL)
		env->cond = env->cond->parent;
	// ft_putendl_fd("handle_condition 4", env->fdout);
	if (env->cond->has_block == 0)
	{
		cond = env->cond;
		env->cond = env->cond->parent;
		exec_condition(env, cond);
		destroy_condition(cond);
	}
	// ft_putendl_fd("handle_condition 5", env->fdout);
}
