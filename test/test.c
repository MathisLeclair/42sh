/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 14:59:40 by mleclair          #+#    #+#             */
/*   Updated: 2017/02/10 15:09:06 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <unistd.h>
#include <term.h>
#include <errno.h>
#include <stdio.h>
#include <curses.h>
#include <stdlib.h>

#include "test.h"

t_var	*tvar(void)
{
	static t_var	*var = NULL;

	if (var == NULL)
		var = malloc(sizeof(t_var));
	return (var);
}

void	initvar(t_var *var)
{
	var->buff = malloc(3);
	var->ret = malloc(INPUT_SIZE);
	var->cpy = malloc(INPUT_SIZE);
	var->cpy[0] = 0;
	var->lenligne = 14; // A CHANGER POUR LA TAILLE DU PROMPT EN TPS REEL
	var->i = 0;
	var->sovi = 0;
	var->del = 0;
	var->selmode = 0;
	var->selstart = -1;
	var->selend = -1;
}

void	add_car(t_var *var, int boule, char c)
{
	char *tmp;

	tmp = malloc(4096);
	tmp[0] = 0;
	ft_strcpy(tmp, var->ret + var->i);
	var->ret[var->i] = boule == 1 ? c : var->buff[0];
	var->ret[var->i + 1] = 0;
	ft_strcat(var->ret, tmp);
	free(tmp);
}

void	rem_car(t_var *var)
{
	char *tmp;

	tmp = malloc(4096);
	ft_strcpy(tmp, var->ret + var->i + 2);
	var->ret[var->i] = 0;
	ft_strcat(var->ret, tmp);
	free(tmp);
}

void	left_arrow(t_var *var)
{
	--var->i;
	--var->lenligne;
	ft_putstr(tgetstr("le", NULL));
}

void	right_arrow(t_var *var)
{
	if (var->lenligne == tgetnum("co"))
	{
		ft_putstr(tgetstr("do", NULL));
		ft_putstr(tgetstr("cr", NULL));
		var->lenligne = 15;
	}
	++var->i;
	++var->lenligne;
	ft_putstr(tgetstr("nd", NULL));
}

void	shift_arrow_l(t_var *var)
{
	if (!var->ret[var->i])
		left_arrow(var);
	while ((var->ret[var->i] == ' ' || var->ret[var->i] == '\t') && var->i > 0)
		left_arrow(var);
	while (var->i > 0 && ft_isalpha(var->ret[var->i]))
		left_arrow(var);
}

void	shift_arrow_r(t_var *var)
{
	if (!var->ret[var->i] && var->i != 0)
		return ;
	while (var->ret[var->i] == ' ' || var->ret[var->i] == '\t')
		right_arrow(var);
	while (var->i >= 0 && ft_isalpha(var->ret[var->i]))
		right_arrow(var);
}

void	home(t_var *var)
{
	while(var->i > 0)
		left_arrow(var);
}

void	end(t_var *var)
{
	int lenret;

	lenret = ft_strlen(var->ret);
	while(var->i < lenret)
		right_arrow(var);
}

void	delete(t_var *var)
{
	ft_putstr(tgetstr("dc", NULL));
	rem_car(var);
}

void	backspace(t_var *var)
{
	if (var->i > 0)
	{
		left_arrow(var);
		ft_putstr(tgetstr("dc", NULL));
		rem_car(var);
	}
}

void	desel(t_var *var)
{
	int j;

	ft_putstr(tgetstr("ei", NULL)); // END OF INSERTE MODE
	j = var->i;
	while (j > 0)
	{
		ft_putstr(tgetstr("le", NULL)); // MOVE CUROR TO LEFT
		--j;
	}
	write(1, var->ret, ft_strlen(var->ret));
	var->selmode = 0;
	var->i = var->sovi;
	var->sovi = 0;
	var->selstart = 0;
	var->selend = 0;
	ft_putstr(tgetstr("rc", NULL)); // RESTORE POS
	ft_putstr(tgetstr("im", NULL)); // START OF INSERTE MODE
}

void	select_mode(t_var *var)
{
	var->selmode = 1;
	if (var->sovi == 0)
	{
		var->sovi = var->i;
		ft_putstr(tgetstr("sc", NULL)); //SAV CURSOR POS
	}
	ft_putstr(tgetstr("ei", NULL)); // END OF INSERTE MODE
	ft_putstr(tgetstr("ms", NULL));
	read(0, var->buff, 3);
	var->selstart = var->selstart == -1 ? var->i : var->selstart;
	var->selend = var->selend == -1 ? var->i : var->selend;
	if (var->buff[0] == 68 && var->i == ft_strlen(var->ret))
		left_arrow(var);
	else if (var->buff[0] == 68 && var->i > 0 && var->i < ft_strlen(var->ret)) //SHIFT + LEFT ARROW
	{
		ft_putstr(tgetstr("mr", NULL)); // MODE REVERSE VIDEO
		write(1, &var->ret[var->i], 1);
		ft_putstr(tgetstr("me", NULL)); // STOP VIDEO MODE
		left_arrow(var);
		ft_putstr(tgetstr("le", NULL));
		var->selstart = var->i < var->selstart ? var->i : var->selstart;
	}
	else if (var->buff[0] == 67 && var->i < ft_strlen(var->ret)) // SHIFT + RIGHT ARROW
	{
		ft_putstr(tgetstr("mr", NULL)); // MODE REVERSE VIDEO
		write(1, &var->ret[var->i], 1);
		ft_putstr(tgetstr("me", NULL)); // STOP VIDEO MODE
		right_arrow(var);
		ft_putstr(tgetstr("le", NULL));
		var->selend = var->selend < var->i ? var->i : var->selend;
	}
	ft_putstr(tgetstr("im", NULL)); // START OF INSERTE MODE
}

void	copy(t_var *var)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < var->selstart)
		;
	while (i++ < var->selend)
		var->cpy[++j] = var->ret[i];
	var->cpy[i] = 0;
	desel(var);
}

void	cut(t_var *var)
{
	int i;

	i = var->i;
	copy(var);
	while (i-- < var->selstart)
		ft_putstr(tgetstr("nd", NULL));
	while (i++ > var->selstart)
		ft_putstr(tgetstr("le", NULL));
	while (var->selend - var->selstart > 0)
	{
		delete(var);
		var->selstart++;
	}
	var->selstart = 0;
	var->selend = 0;
	var->selmode = 0;
}

void	paste(t_var *var)
{
	int i;

	i = -1;
	if (ft_strlen(var->cpy) == 0)
		return ;
	ft_putstr(var->cpy);
	while (var->cpy[++i])
		;
	while (i--)
		add_car(var, 1 , var->cpy[i]);
	var->i = ft_strlen(var->ret);
}

void	touch(t_var *var)
{
	char *test;

	test = ft_sprintf("\e[1;32m%C\e[0;m \e[1;36m%s \e[0m%s", L'✈', "test", "$\e[0;31m42sh\e[0m>");
	ft_putstr(test);
	var->i = 0;
	var->ret = malloc(4096);
	var->ret[0] = 0; 
	ft_putstr(tgetstr("im", NULL)); // START OF INSERTE MODE
	while (var->buff[0] != 10)
	{
		read(0, var->buff, 3);

		if (var->buff[0] == 27 && var->buff[2] == 91)
			select_mode(var);
		else if (var->buff[1] == -119) //CTRL + X
			cut(var);
		else if (var->buff[1] == -89) //CTRL + C
			copy(var);
		else if (var->selmode == 1 && var->buff[0] > 0)
			desel(var);
		if (var->buff[0] == -30 && var->buff[1] == -120) //CTRL + V
			paste(var);
		if (var->buff[0] == 27 && var->buff[2] == 68 && var->i > 0) //LEFT ARROW
			left_arrow(var);
		if (var->buff[0] == 27 && var->buff[2] == 67 && var->i < ft_strlen(var->ret))  //RIGHT ARROW 
			right_arrow(var);
		if (var->buff[0] == 59 && var->buff[2] == 68) //SHIFT + LEFT ARROW
			shift_arrow_l(var);
		if (var->buff[0] == 59 && var->buff[2] == 67) //SHIFT + RIGHT ARROW
			shift_arrow_r(var);
		if (var->buff[0] == 27 && var->buff[2] == 72) //HOME
			home(var);
		if (var->buff[0] == 27 && var->buff[2] == 70) //END
			end(var);
		if (var->buff[0] == 127 && var->buff[1] == 0) //backspace
			backspace(var);
		if (var->del == 1)
			var->del = 0;
		if (var->buff[0] == 27 && var->buff[2] == 51) //DELETE
		{
			var->del = 1;
			delete(var);
		}
		if (var->buff[0] == 4)
			break ;
		else if(var->buff[1] == 0 && var->buff[0] != 10 && var->buff[0] != 127 && var->del != 1) // STANDARD CHAR
		{
			write(1, &var->buff[0], 1);
			add_car(var, 0, 0);
			++var->i;
			++var->lenligne;
		}
		// printf("\nid1 touche = %d\n", var->buff[0]); //  DEBUG INPUT
		// printf("id2 touche = %d\n", var->buff[1]);
		// printf("id3 touche = %d\n", var->buff[2]);
		var->buff[1] = 0;
		var->buff[2] = 0;
	}
	ft_putchar('\n');
	printf("finit = %s\n", var->ret);
	ft_putstr(tgetstr("ei", NULL)); // END OF INSERT MODE
}

int main(void)
{
	char *str;
	struct termios term;
	t_var	*var;

	var = tvar();
	initvar(var);
	if ((str = getenv("TERM")) == NULL)
		return (-1);
	tgetent(NULL, str);
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	touch(var);
// reset
	if (tcgetattr(0, &term) == -1)
		return (-1);
term.c_lflag = (ICANON | ECHO);
	if (tcsetattr(0, 0, &term) == -1)
		return (-1);
	free(var->buff);
}