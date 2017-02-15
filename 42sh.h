/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 16:36:54 by mleclair          #+#    #+#             */
/*   Updated: 2017/02/15 18:06:16 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# define FALSE	0
# define PROMPT "$\e[0;31m42sh\e[0m>"
# define INPUT_SIZE 4096
# define BUFF_SIZE 32

# include "./libft/libft.h"
# include <signal.h>
# include <unistd.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/types.h>
# include <term.h>
# include <sys/stat.h>
# include <pwd.h>

typedef struct	s_env
{
	char			**history;
	char			*input;
	char			**ev;
	char			**savev;
	char			*dir;
	char			**path;
	int				i;
	struct s_env	*loc;
	char			*find;
}				t_env;

typedef struct dirent	t_dirent;

/*
** main.c
*/

t_env			*env(void);

/*
** redirection.c
*/

void 			rd_pipe(char *cmd1, char *cmd2, char *args1[], char *args2[]);
void			rd_output(char *cmd, char *args[], char *filename);
void			rd_output_apd(char *cmd, char *args[], char *filename);
void			rd_input(char *cmd, char *args[], char *filename);

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

void			error(int i, char *str, char *str2);
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

char			**ft_strsplitquote(char const *s, char c, char t);

/*
** free.c
*/

void			env_free(t_env *env);
int				free_double_array(char **t);

/*
** builtin.c
*/

void			ft_cd(char **split, t_env *env, char *reg, char *oldpwd);
void			ft_echo(char **split);
void			ft_exit(void);

void			ft_aperture(void);

/*
** tilde.c
*/
void			ft_tilde(t_env *e, int i, char quote);


/*
** verif_quote.c
*/

int				verif_quote(char *inp, int k);

/*
** double_array_sort.c
*/

void			double_array_sort(char **t);

void	add_str_to_dstr(char ***dstr, char *str);

void	history(t_env *env, char **split);

#endif
