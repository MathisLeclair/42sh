/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 16:36:54 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/20 17:35:57 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHELL_H
# define CHELL_H

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
# include <sys/ioctl.h>
# include <pwd.h>

typedef struct	s_job
{
	char			*name;
	char			stat;
	char			*status;
	int				pid;
	int				num;
	int				killable;
	struct s_job	*prev;
	struct s_job	*next;
}				t_job;

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
	char			*redir;
	char			*inp1;
	char			*inp2;
	char			*name;
	int				lastret;
	int				isoperand;
	int				shell_terminal;
	t_job			*job;
	int				booljob;
	int				boolthing;
	char			**hash;
}				t_env;

typedef struct	s_var
{
	char			*buff;
	char			*cpy;
	char			*ret;
	char			*arr;
	int				lenligne;
	long int		i;
	int				sovi;
	int				del;
	int				selmode;
	int				lenprompt;
	int				selstart;
	int				selend;
	long int		inputlen;
	char			**ac;
	struct termios	term;
	struct termios	termsav;
}				t_var;

typedef struct dirent	t_dirent;

/*
** main.c
*/

t_env			*env(void);
void			ft_sig(int i);

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
** reco_cmd.c
*/

int				ft_reco_cmd(t_env *env, int i);

/*
**cmd.c
*/

int				ft_read(t_env *env, char *input);
char			**ft_split_input(char *input);

/*
**cmd2.c
*/

void			ft_suppr_quotes(char **str, int i, int j);
void			ft_suppr_bs(char **str);
char			**ft_split_input(char *input);
void			extracredir(t_env *e, int i, int j);
int				isinquote(char *input, int i);

/*
**cmd3.c
*/

int				cmprevtruc(t_env *env, char **input);
int				cmprev(char *str, char *tofind);
void			extract_rd_output(t_env *env, char *input);
void			extract_heredoc(t_env *env, char *input);
int				parserror(t_env *env);

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
void			add_pair_to_env(t_env *env, char *key, char *val);
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
**getpwd.c
*/

void			remove_nl(char **str);
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
** tilde.c
*/
void			ft_tilde(char **s, int i, char quote);

/*
** verif_quote.c
*/

int				verif_quote(char **inp, int k, int quote);

/*
** double_array_sort.c
*/

void			double_array_sort(char **t);

/*
** builtin.c
*/

void			ft_cd(char **split, t_env *env, char *reg, char *oldpwd);
void			ft_echo(char **split);
void			ft_exit(char **split);
void			ft_aperture(void);

/*
** builtin2.c
*/

void			history(t_env *env, char **split);
void			builtin_read(t_env *ev, char **split);
void			builtin_export(t_env *env, char **split);
void			add_local(t_env *env, char **split);

/*
** buitin3.c
*/

void			builtin_hash(t_env *env, char **split);
void			gthash(char *str);
char			*isbin(char *str);

/*
** builtin_history.c
*/

void			builtin_history(t_env *env, char **split);

/*
** operator.c
*/

void			oprt_and(t_env *env);
void			oprt_or(t_env *env);

/*
** redirection_adv.c
*/

void			rd_here_doc(t_env *env, int a, int b);
void			rd_here_string(t_env *env, int a, int b, pid_t x);

/*
** redirection_fd.c
*/

void			rd_dupinput(t_env *env, char n);
void			rd_dupoutput(t_env *env, char n);

/*
** redirection.c
*/

void			rd_output(t_env *env, int a, int b, pid_t z);
void			rd_output_apd(t_env *env, int a, pid_t b);
void			rd_input(t_env *env);

/*
** pipe.c
*/

void			rd_pipe(t_env *env);

/*
** handle_argv.c
*/

void			handle_argv(int ac, char **av, t_env *loc, int i);

/*
** handle_file.c
*/

void			handle_file(int ac, char **av, t_env *env);

/*
** bquote.c
*/

void			bquote(t_env *env);

/*
** subshell.c
*/

int				subshell(t_env *env, char *input);
void			retvalue_into_loc(t_env *env, int i);

/*
**							TERMCAPS
** arrow.c
*/

void			left_arrow(t_var *var);
void			right_arrow(t_var *var);
void			up_arrow(t_var *var, int *bg);
void			down_arrow(t_var *var, int *bg);

/*
** shift_arrow.c
*/

void			shift_arrow_r(t_var *var);
void			shift_arrow_l(t_var *var);
void			shift_down(t_var *var);
void			shift_up(t_var *var);

/*
** copy_paste.c
*/

void			paste(t_var *var);
void			copy(t_var *var, int p);
void			cut(t_var *var);

/*
** sel_desel.c
*/

void			select_mode(t_var *var);
void			desel(t_var *var);

/*
** del_backspace.c
*/

void			deleteu(t_var *var);
void			backspace(t_var *var);

/*
** home_end.c
*/

void			home(t_var *var);
void			end(t_var *var);

/*
** utils.c
*/

t_var			*tvar(void);
void			add_car(t_var *var, int boule, char c);
void			rem_car(t_var *var);
void			initvar(t_var *var, int i);
void			replace_w(char *word, t_var *var);

/*
** ctrl_r.c
*/

void			control_r(t_var *var, char *tmp, char *tmp2, int j);

/*
** tab.c
*/

void			tabu(t_var *var, int *j);

/*
** exlam.c
*/

void			exclam(t_var *var);

/*
** touch.c
*/

void			touch(t_var *var);
void			touch5(t_var *var);

/*
** exlam.c
*/

void			exclam(t_var *var);

char			*termcaps(t_ssprintf *prompt);
void			add_history(char *str);
void			reset(t_var *var);

/*
**					 END OF TERMCAPS
*/

/*
** autocomplete.c
*/

void			startfind(char **ac, t_env *env, int boolean, int i);
char			**forest(char *s, int ps, t_env *env, char first);
char			**autocomplete(char *input, int pos, t_env *env);

/*
** autocomplete2.c
*/
char			*add_bs(char *str);
int				strstr_bool(char *find, char *search_in_lc, int i);
char			*to_lwcase(char *str);
void			add_str_to_dstr(char ***dstr, char *str);
void			ft_ac_cmd_build(char ***ac, char *find);

/*
** autocomplete3.c
*/
void			ft_ac_cmd_path(char **split_path, char *find, char ***ac);
char			**ac_cmd(char *find, t_env *env);
void			ac_target2(char *a, t_dirent *td, char *f, char ***ac);
char			**ac_pwd(char *find, char *str);
void			ac_target(char *find, char ***ac);

/*
** autocomplete4.c
*/
char			**auto_possibilities(char pwd, t_env *ev);
char			*finder(char *input, int pos);
char			ft_strcmp_beg(char *str1, char *str2);

void			parse(t_env *env, char *input);
void			signblock();
void			set_history(void);
void			file_history(int i, int j, int k, int fd);
void			auto_prop(t_var *var, int p);
void			ft_join_spaces(char **tmp, int i);
int				strstr_bool(char *find, char *search_in_lc, int i);

#endif
