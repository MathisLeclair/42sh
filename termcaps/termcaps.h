/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:15:55 by mleclair          #+#    #+#             */
/*   Updated: 2017/02/22 11:42:15 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAP_H
# define TERMCAP_H

# include "../42sh.h"

typedef struct	s_var
{
	char		*buff;
	char		*cpy;
	char		*ret;
	int			lenligne;
	long int	i;
	int			sovi;
	int			del;
	int			selmode;
	int			lenprompt;
	int			selstart;
	int			selend;
	size_t		inputlen;
	char		**ac;
}				t_var;

void			add_history(t_var *var);
char			**autocomplete(char *input, int pos, t_env *env);
void			reset(struct termios term, t_var *var, char *str);
void			touch(struct termios term, t_var *var, char *str);

void			add_car(t_var *var, int boule, char c);
void			rem_car(t_var *var);

void			left_arrow(t_var *var);
void			right_arrow(t_var *var);
void			shift_arrow_r(t_var *var);
void			shift_arrow_l(t_var *var);
void			up_arrow(t_var *var);
void			down_arrow(t_var *var);

void			shift_down(t_var *var);
void			shift_up(t_var *var);

void			home(t_var *var);
void			end(t_var *var);
void			deleteu(t_var *var);
void			backspace(t_var *var);

void			select_mode(t_var *var);
void			desel(t_var *var);
void			copy(t_var *var, int p);
void			cut(t_var *var);

#endif