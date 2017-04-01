/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 14:59:40 by mleclair          #+#    #+#             */
/*   Updated: 2017/04/01 16:12:03 by aridolfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <unistd.h>
#include <term.h>
#include <curses.h>
#include <stdlib.h>

#include "../chell.h"

void	reset(t_var *var)
{
	ft_putstr(tgetstr("rs", NULL));
	if (tcgetattr(0, &var->term) == -1)
		error(-6, 0, 0);
	var->term.c_lflag = (ICANON | ECHO);
	tcsetattr(0, 0, &var->term);
	tcsetattr(0, 0, &var->termsav);
	var->term = var->termsav;
	ft_putstr(tgetstr("ei", NULL));
}

void	initterm(t_var *var)
{
	var->termsav = var->term;
	var->term.c_lflag &= ~(ICANON);
	var->term.c_lflag &= ~(ECHO);
	var->term.c_cc[VMIN] = 1;
	var->term.c_cc[VTIME] = 0;
}

char	*termcaps(t_ssprintf *prompt, int u)
{
	char			*str;
	t_var			*var;

	ft_putstr(prompt->buf);
	var = tvar();
	initvar(var, 1, u);
	if ((str = getenv("TERM")) == NULL)
		tgetent(NULL, "xterm-256color");
	else
		tgetent(NULL, str);
	if (tcgetattr(0, &var->term) == -1)
		error(-6, 0, 0);
	initterm(var);
	if (tcsetattr(0, TCSADRAIN, &var->term) == -1)
		error(-6, 0, 0);
	touch(var, prompt);
	reset(var);
	str = ft_strdup(var->ret);
	ft_bzero(prompt->buf, prompt->ret);
	free(prompt);
	initvar(var, 1, u);
	return (str);
}
