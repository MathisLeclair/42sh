/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:15:55 by mleclair          #+#    #+#             */
/*   Updated: 2017/02/17 17:38:22 by bfrochot         ###   ########.fr       */
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

#endif