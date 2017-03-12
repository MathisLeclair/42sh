/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 16:03:36 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/12 15:15:33 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	add_local(t_env *env, char **split)
{
	int i;
	int j;

	(void)env;
	i = -1;
	while (split[++i])
	{
		if ((j = ft_strfind(split[i], '=')) != -1)
			if (ft_isalpha(split[i][0]))
				add_var_to_env(env->loc, split[i]);
	}
}

void	builtin_export(t_env *env, char **split)
{
	int i;
	int j;

	i = 0;
	if (!split[1] || (split[1][0] == '-' && split[1][1] == 'p'))
		while (env->ev[++i])
			ft_printf("%s %s\n", "export", env->ev[i]);
	else if (split[1][1] && split[1][0] == '-' && split[1][1] != 'p')
		ft_printf("%s %c\n", "export : bad option:", split[1][1]);
	else
		while (split[++i])
			if (ft_strfind(split[i], '=') != -1)
			{
				add_local(env, split);
				add_var_to_env(env, split[i]);
			}
			else
			{
				j = find_param(env->loc->ev, split[i]);
				if (j == -1)
					continue ;
				add_var_to_env(env, env->loc->ev[j]);
			}
}

void	builtin_read2(char *str)
{
	int i;
	char *tmp;

	i = -1;
	while(str[++i])
	{
		if (str[i] == '\\')
		{
			tmp = palloc(ft_strlen(str) + 2);
			*tmp = 0;
			ft_strncat(tmp, str, i);
			tmp[i] = '\\';
			tmp[i + 1] = 0;
			ft_strcat(tmp, str + i);
			free(str);
			str = tmp;
		}
	} 
}

void	builtin_read(t_env *ev, char **split)
{
	char	*bufe;
	char	truc[INPUT_SIZE];
	int		r;
	int		i;

	r = 0;
	i = 1;
	truc[0] = 0;
	bufe = malloc(INPUT_SIZE);
	read(0, bufe, INPUT_SIZE);
	if (split[1] && split[1][0] == '-' && split[1][1] == 'r')
	{
		r = 1;
		builtin_read2(bufe);
	}
	i = r == 1 ? 2 : 1;
	while (split[++r])
	{
		ft_strcat(truc, split[i]);
		ft_strcat(truc, "=");
		ft_strcat(truc, bufe);
		add_var_to_env(ev->loc, split[i]);
		truc[0] = 0;
	}
}

void	history(t_env *env, char **split)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = malloc(INPUT_SIZE);
	*tmp = 0;
	if (split[0] && split[1] && split[2])
		error(-7, NULL, NULL);
	else if (!(env->history))
		error(-11, 0, 0);
	else if (split[1])
	{
		if (split[1][0] == '-')
		{
			if (split[1][1] == 'c')
			{
				free_double_array(env->history);
				ft_strcat(ft_strcat(tmp, env->ev[find_param(env->ev,"HOME")] + 5), "/.42shistory");
				unlink(tmp);
				set_history();
				retvalue_into_loc(env, 0);
			}
			else
			{
				ft_putstr("Wrong argument, only -c accepted.\n");
				retvalue_into_loc(env, 1);
			}
		}
		else if (split[1] && isnumber(split[1][0]))
		{
			i = ft_atoi(split[1]);
			j = 0;
			while (env->history[j])
				++j;
			while (i-- > 0)
				ft_printf("%s\n", env->history[j - i - 1]);
			retvalue_into_loc(env, 0);
		}
		else
		{
			ft_putstr("Is not a number.\n");
			retvalue_into_loc(env, 1);
		}
	}
	else
	{
		print_split(env->history);
		retvalue_into_loc(env, 0);
	}
}
