/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 16:18:04 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/20 18:26:01 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# define PROMPT "$\e[0;31mms\e[0m>"
# include <signal.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# define INPUT_SIZE 4096
# define BUFF_SIZE 32

typedef struct	s_env
{
	char	*input;
	char	**ev;
	char	**savev;
	char	*dir;
	char	**path;
	int		i;
}				t_env;

/*
** main.c
*/

t_env			*env(void);

/*
** getnextline
*/

int				get_next_line(const int fd, char **line);

/*
** ft_cmpspec.c
*/

int				ft_cmpspec(char *s1, char *str);
char			*ft_super_strstr(const char *str1, const char *str2);

/*
**cmd.c
*/

int				ft_read(t_env *env);
int				ft_reco_cmd(t_env *env);
void			ft_suppr_quotes(char *str, int i, int j);

/*
**error.c
*/

void			error(int i, char *str);
void			*palloc(size_t	size);

/*
**env_mod.c
*/

int				find_param(char **split, char *str);
void			add_var_to_env(t_env *env, char *str);
void			suppr_var_env(t_env *env, char *str);

/*
**cmd_env.c
*/

int				save_env(t_env *env);
void			print_split(char **split);
void			reco_env(t_env *env, char **input, int i, int j);

/*
**ft_dollar.c
*/

void			ft_dollar(t_env *env, int i, char quote);

/*
**set_env.c
*/

void			set_oldpwd(t_env *env, char *str);
void			set_env(t_env *env, char **ev);

/*
**fork.c
*/

void			ft_fork(t_env *env, char **input);

/*
**setenv.c
*/

void			getpwd(char *pwd);

/*
**ft_strsplitquote.c
*/

char			**ft_strsplitquote(char const *s, char c, char tab);

/*
** free.c
*/

void			env_free(t_env *env);
int				free_double_array(char **tab);

/*
** builtin.c
*/

void			ft_cd(char **split, t_env *env, char *reg, char *oldpwd);
void			ft_echo(char **split);
void			ft_exit(void);

void			ft_aperture(void);

#endif
