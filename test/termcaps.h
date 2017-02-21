/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:15:55 by mleclair          #+#    #+#             */
/*   Updated: 2017/02/21 17:51:14 by aridolfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAP_H
# define TERMCAP_H

# include "../42sh.h"

typedef struct	s_var
{
	char	*buff;
	char	*cpy;
	char	*ret;
	int		lenligne;
	int		i;
	int		sovi;
	int		del;
	int		selmode;
	int		lenprompt;
	int		selstart;
	int		selend;
	size_t	inputlen;
	char	**ac;
}				t_var;

void			add_history(t_var *var);
<<<<<<< HEAD:test/termcaps.h
char			**autocomplete(char *input, int pos, t_env *env);
=======
>>>>>>> df690a33ba500f3efbacdc10da33e251b56f5bd7:test/termcaps.h

#endif
