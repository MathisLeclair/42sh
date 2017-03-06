/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 14:59:40 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/06 14:10:12 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <unistd.h>
#include <term.h>
#include <curses.h>
#include <stdlib.h>

#include "../42sh.h"

t_var	*tvar(void)
{
	static t_var	*var = NULL;

	if (var == NULL)
	{
		var = malloc(sizeof(t_var));
		var->cpy = malloc(sizeof(INPUT_SIZE));
		var->ret = malloc(sizeof(INPUT_SIZE));
		var->buff = malloc(3);
		var->buff[0] = 0;
		var->buff[1] = 0;
		var->buff[2] = 0;
	}
	return (var);
}

void	initvar(t_var *var, int i)
{
	if (i == 1)
		bzero(var->buff, 3);
	var->lenprompt = 10 + ft_strlen(env()->dir);
	var->lenligne = var->lenprompt;
	var->i = 0;
	var->sovi = 0;
	var->del = 0;
	var->selmode = 0;
	var->selstart = -1;
	var->selend = -1;
	var->inputlen = 0;
	var->ac = NULL;
	var->arr = 0;
	var->ret[0] = 0;
}

void	add_car(t_var *var, int boule, char c)
{
	char *tmp;

	++var->inputlen;
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
	ft_strcpy(tmp, var->ret + var->i + 1);
	var->ret[var->i] = 0;
	ft_strcat(var->ret, tmp);
	free(tmp);
}

void	left_arrow(t_var *var)
{
	int i;

	--var->i;
	--var->lenligne;
	if (var->lenligne % tgetnum("co") == 0)
	{
		ft_putstr(tgetstr("up", NULL));
		i = -1;
		while (++i < tgetnum("co"))
			ft_putstr(tgetstr("nd", NULL));
	}
	else
		ft_putstr(tgetstr("le", NULL));
}

void	right_arrow(t_var *var)
{
	if (var->i < (int)ft_strlen(var->ret))
	{
		if (var->lenligne % tgetnum("co") == 0)
			ft_putstr(tgetstr("sf", NULL));
		else
			ft_putstr(tgetstr("nd", NULL));
		++var->i;
		++var->lenligne;
	}
}

void	shift_arrow_l(t_var *var)
{
	if (!var->ret[var->i])
		left_arrow(var);
	while ((var->ret[var->i] == ' ' || var->ret[var->i] == '\t') && var->i > 0)
		left_arrow(var);
	while (var->i > 0 && var->ret[var->i] && var->ret[var->i] != ' '
		&& var->ret[var->i] != '\t')
		left_arrow(var);
}

void	shift_arrow_r(t_var *var)
{
	if (!var->ret[var->i] && var->i != 0)
		return ;
	while (var->ret[var->i] == ' ' || var->ret[var->i] == '\t')
		right_arrow(var);
	while (var->i >= 0 && var->ret[var->i] && var->ret[var->i] != ' '
		&& var->ret[var->i] != '\t')
		right_arrow(var);
}

void	shift_up(t_var *var)
{
	int i;

	i = -1;
	while (++i < tgetnum("co") && var->i > 0)
		left_arrow(var);
}

void	shift_down(t_var *var)
{
	int i;

	i = -1;
	while (++i < tgetnum("co"))
		right_arrow(var);
}

void	paste(t_var *var)
{
	int i;

	ft_putstr(var->cpy);
	i = ft_strlen(var->cpy);
	while (--i >= 0)
		add_car(var, 1, var->cpy[i]);
	var->i += ft_strlen(var->cpy);
	i = var->i;
	ft_putstr(tgetstr("cd", NULL));
	write(1, var->ret + var->i, ft_strlen(var->ret) - var->i);
	var->i = ft_strlen(var->ret);
	var->lenligne = ft_strlen(var->ret) + var->lenprompt;
	while (var->i > i)
		left_arrow(var);
	var->selend = -1;
	var->selstart = -1;
}

void	ft_asdf(t_var *var, int i, int *bg)
{
	int		j;
	char	*tmp;
	char	*tmp2;

	var->ac = malloc(sizeof(char *));
	var->ac[0]= 0;
	while (env()->history[++i])
		if (strstr(env()->history[i], var->ret))
			add_str_to_dstr(&var->ac, env()->history[i] + 7);
	i = 0;
	while (var->ac[i])
	{
		tmp = ft_strdup(var->ac[i]);
		tmp2 = ft_strdup(var->ret);
		if (!ft_strcmp_beg(tmp, tmp2))
		{
			free(var->ac[i]);
			j = i;
			while (var->ac[j++])
				var->ac[j - 1] = var->ac[j];
		}
		else
			++i;
		free(tmp);
		free(tmp2);
	}
	*bg = i;
}

void	up_arrow(t_var *var, int *bg)
{
	char *tmp;

	if (env()->history[*bg] == 0)
		ft_asdf(var, -1, bg);
	if (var->arr == NULL)
		var->arr = ft_strdup(var->ret);
	if (var->ac[0])
	{
		while (var->i != 0)
			backspace(var);
		while (var->ret[0])
			deleteu(var);
		if (*bg > 0)
			(*bg)--;
		tmp = var->cpy;
		var->cpy = var->ac[*bg];
		paste(var);
		var->cpy = tmp;
	}
}

void	down_arrow(t_var *var, int *bg)
{
	char *tmp;

	if (var->ac[0])
	{
		while (var->i != 0)
			backspace(var);
		while (var->ret[0])
			deleteu(var);
		if (var->ac[*bg])
			(*bg)++;
		if (var->ac[*bg] == 0)
		{
			tmp = var->cpy;
			var->cpy = var->arr;
			paste(var);
			var->cpy = tmp;
		}
		else
		{
			tmp = var->cpy;
			var->cpy = var->ac[*bg];
			paste(var);
			var->cpy = tmp;
		}
	}
}

void	control_r(t_var *var, char *tmp, char *tmp2, int j)
{
	char		*str;
	t_ssprintf	*loul;
	int			i;

	if (var->cpy)
		tmp2 = ft_strdup(var->cpy);
	loul = malloc(sizeof(t_ssprintf));
	loul->buf = ft_strdup("\nhist-i-search : ");
	loul->ret = ft_strlen("\nhist-i-search : ");
	str = termcaps(loul);
	free(loul->buf);
	free(loul);
	i = ft_strlen(str) / tgetnum("co") + 2;
	while (i--)
		ft_putstr(tgetstr("up", NULL));
	while (--j)
		ft_putstr(tgetstr("nd", NULL));
	initvar(var, 1);
	ft_putstr(tgetstr("cd", NULL));
	i = 0;
	while (env()->history[i])
		++i;
	while (i > 0 && str[0] && --i && !ft_strcmp_beg(env()->history[i] + 7, str))
		;
	if (str[0] && ((i == 0 && env()->history[i] && ft_strcmp_beg(env()->history[i] + 7, str)) || i != 0))
		var->cpy = env()->history[i] + 7;
	else
		var->cpy = tmp;
	paste(var);
	free(tmp);
	var->cpy = tmp2;
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

void	deleteu(t_var *var)
{
	int i;

	if (var->del == 1)
		read(0, NULL, 3);
	if (var->del == 1)
		var->del = 0;
	rem_car(var);
	ft_putstr(tgetstr("cd", NULL));
	write(1, var->ret + var->i, ft_strlen(var->ret + var->i));
	i = ft_strlen(var->ret + var->i);
	while (i-- > 0)
		ft_putstr(tgetstr("le", NULL));
	--var->inputlen;
}

void	backspace(t_var *var)
{
	if (var->i > 0)
	{
		left_arrow(var);
		deleteu(var);
	}
}

void	replace_w(char *word, t_var *var)
{
	char	*tmp;

	while (var->i && var->ret[var->i - 1] != ' ')
		backspace(var);
	while (var->ret[var->i] != ' ' && var->ret[var->i])
		deleteu(var);
	tmp = var->cpy;
	var->cpy = ft_strdup(word);
	paste(var);
	free(var->cpy);
	var->cpy = tmp;
}

void	put_ac(t_var * var)
{
	int i;

	i = var->i;
	while (var->i != var->inputlen)
		right_arrow(var);
	while ((var->i + var->lenprompt - 1) % tgetnum("co") != 0)
	{
		write(1, " ", 1);
		var->i += 1;
	}
	auto_prop(var);
	while (var->i != i)
	{
		ft_putstr(tgetstr("le", NULL));
		var->i -= 1;
	}
	var->lenligne = var->i + var->lenprompt;
}

void	tabu(t_var *var, int *j)
{
	static int	i;

	if (*j == 0)
	{
		*j = 1;
		var->ac = autocomplete(var->ret, var->i, env());
		if (var->ac == NULL || var->ac[0] == 0)
			return ;
		if (var->ac[1] == 0)
			replace_w(var->ac[0], var);
		if (var->ac[1] == 0)
			*j = 0;
		else
			put_ac(var);
		i = 0;
	}
	else
	{
		if (var->ac == NULL || var->ac[0] == 0)
			return ;
		if (var->ac[i] == 0)
			i = 0;
		replace_w(var->ac[i], var);
		put_ac(var);
		++i;
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
	var->selstart = -1;
	var->selend = -1;
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
	if (var->buff[0] == 68 && var->i == (int)ft_strlen(var->ret))
		left_arrow(var);
	else if (var->buff[0] == 68 && var->i > 0 && var->i < (int)ft_strlen(var->ret)) //SHIFT + LEFT ARROW
	{
		ft_putstr(tgetstr("mr", NULL)); // MODE REVERSE VIDEO
		write(1, &var->ret[var->i], 1);
		ft_putstr(tgetstr("me", NULL)); // STOP VIDEO MODE
		left_arrow(var);
		ft_putstr(tgetstr("le", NULL));
		var->selstart = var->i < var->selstart ? var->i : var->selstart;
	}
	else if (var->buff[0] == 67 && var->i < (int)ft_strlen(var->ret)) // SHIFT + RIGHT ARROW
	{
		ft_putstr(tgetstr("mr", NULL)); // MODE REVERSE VIDEO
		write(1, &var->ret[var->i], 1);
		ft_putstr(tgetstr("me", NULL)); // STOP VIDEO MODE
		right_arrow(var);
		ft_putstr(tgetstr("le", NULL));
		var->selend = var->i > var->selend ? var->i : var->selend;
	}
	ft_putstr(tgetstr("im", NULL)); // START OF INSERTE MODE
}

void	copy(t_var *var, int p)
{
	int i;
	int j;

	i = 0;
	j = 0;
	var->cpy[0] = 0;
	while (i < var->selstart)
		++i;
	while (i <= var->selend)
		var->cpy[j++] = var->ret[i++];
	var->cpy[i + 1] = 0;
	if (p != 1 && var->cpy[0])
		desel(var);
}

void	cut(t_var *var)
{
	int i;

	copy(var, 1);
	if (var->selstart == -1 || var->selend == -1)
		return ;
	i = var->i;
	while (var->i != var->selstart)
	{
		var->selend--;
		backspace(var);
	}
	while (var->i != var->selend)
	{
		var->selend--;
		deleteu(var);
	}
	deleteu(var);
	var->selstart = -1;
	var->selend = -1;
	var->selmode = 0;
}

void	reset(t_var *var)
{
	ft_putstr(tgetstr("rs", NULL));
	if (tcgetattr(0, &var->term) == -1)
		error(-6, 0, 0);
	var->term.c_lflag = (ICANON | ECHO);
	tcsetattr(0, 0, &var->term);
	tcsetattr(0, 0, &var->termsav);
	var->term = var->termsav;
	ft_putstr(tgetstr("ei", NULL)); // END OF INSERT MODE
}

void	exclam(t_var *var)
{
	int i;
	int u;
	int k;
	int j;
	char *tmp;

	u = -1;
	i = ft_strfind(var->ret, '!');
	while (env()->history[u])
			++u;
	j = i;
	while (var->ret[j] && var->ret[j] != ' ')
		++j;
	tmp = ft_strcdup(var->ret + i, j- i);
	if (!ft_isdigit(var->ret[i + 1]))
	{
		k = u;
		while (k > 0 && env()->history[--k])
			if(ft_strcmp_beg(env()->history[k] + 7, tmp + 1))
				break ;
		if (k == 0 && !ft_strcmp_beg(env()->history[k] + 7, tmp + 1))
			error(-13, NULL, NULL);
		if (k == 0 && !ft_strcmp_beg(env()->history[k] + 7, tmp + 1))
			return ;
	}
	else
	{
		u = i;
		while (ft_isdigit(var->ret[++u]))
			;
		if (u > 100000)
		{
			error(-13, NULL, NULL);
			return ;
		}
		k = ft_atoi(var->ret + i + 1);
		if (k > u)
		{
			error(-13, NULL, NULL);
			return ;
		}
	}
	free(tmp);
	ft_remstr(var->ret, i, j);
	var->i = i;
	i = ft_strlen(env()->history[k]);
	while (i-- > 7)
		add_car(var, 1, (env()->history[k])[i]);
}

void	touch(t_var *var)
{
	// char		*test;
	int	i;
	int j;
	int bg;

	// test = ft_sprintf("\e[1;32m%C\e[0;m \e[1;36m%s \e[0m%s", L'✈', "test", "$\e[0;31m42sh\e[0m>");
	// ft_putstr(test);
	bg = 0;
	while (env()->history[bg])
		++bg;
	i = 0;
	var->i = 0;
	var->ret[0] = 0; 
	ft_putstr(tgetstr("im", NULL)); // START OF INSERTE MODE
	ft_putstr(tgetstr("bw", NULL));
	while (var->buff[0] != 10)
	{
		read(0, var->buff, 3);
		if (var->buff[0] == 27 && var->buff[2] == 91)
			select_mode(var);
		else if (var->buff[1] == -119) //ALT + X
			cut(var);
		else if (var->buff[1] == -89) //ALT + C
			copy(var, 0);
		else if (var->selmode == 1 && var->buff[0] > 0)
			desel(var);
		if (var->buff[0] == 3 && var->buff[1] == 0) //CTRL + C
			continue ;
		if (var->buff[0] == -30 && var->buff[1] == -120) //ALT + V
			paste(var);
		if (var->buff[0] == 27 && var->buff[2] == 68 && var->i > 0) //LEFT ARROW
			left_arrow(var);
		if (var->buff[0] == 27 && var->buff[2] == 67)  //RIGHT ARROW 
			right_arrow(var);
		if (var->buff[0] == 59 && var->buff[2] == 68) //SHIFT + LEFT ARROW
			shift_arrow_l(var);
		if (var->buff[0] == 59 && var->buff[2] == 67) //SHIFT + RIGHT ARROW
			shift_arrow_r(var);
		if (var->buff[0] == 59 && var->buff[2] == 65) //SHIFT + UP ARROW
			shift_up(var);
		if (var->buff[0] == 59 && var->buff[2] == 66) //SHIFT + DOWN ARROW
			shift_down(var);
		if (var->buff[0] == 27 && var->buff[2] == 72) //HOME
			home(var);
		if (var->buff[0] == 9 && var->buff[2] == 0) // AUTOCOMPLETE
			tabu(var, &i);
		else if (var->buff[0] == 27 && var->buff[2] == 65 && env()->history[0]) // UP ARROW
			up_arrow(var, &bg);
		else if (var->buff[0] == 27 && var->buff[2] == 66 && var->ac) // DOWN ARROW
			down_arrow(var, &bg);

		else
		{
			free(var->arr);
			var->arr = NULL;
			while (env()->history[bg])
				++bg;
			if (var->ac)
				free_double_array(var->ac);
			if (var->ac)
				var->ac = NULL;
			i = 0;
		}
		if (var->buff[0] == 18 && var->buff[1] == 0 && var->buff[2] == 0)
			control_r(var, ft_strdup(var->ret), NULL, var->lenprompt);
		if (var->buff[0] == 27 && var->buff[2] == 70) //END
			end(var);
		if (var->del == 1)
			var->del = 0;
		if (var->buff[0] == 127 && var->buff[1] == 0) //backspace
			backspace(var);
		if (var->buff[0] == 27 && var->buff[2] == 51) //DELETE
		{
			var->del = 1;
			deleteu(var);
		}
		if (var->buff[0] == 4 && ft_strlen(var->ret) == 0)
		{
			reset(var);
			error(-6, NULL, NULL);
		}
		else if (var->buff[1] == 0 && ft_isprint(var->buff[0])) // STANDARD CHAR
		{
			write(1, &var->buff[0], 1);
			add_car(var, 0, 0);
			++var->i;
			++var->lenligne;
			// printf("%d\n", var->lenligne);
			if (var->lenligne % tgetnum("co") == 1)
				ft_putstr(tgetstr("sf", NULL));
			ft_putstr(tgetstr("cd", NULL));
			write(1, var->ret + var->i, ft_strlen(var->ret + var->i));
			j = ft_strlen(var->ret + var->i);
			while (j-- > 0)
				ft_putstr(tgetstr("le", NULL));
		}
		// printf("\nid1 touche = %d\n", var->buff[0]); //  DEBUG INPUT
		// printf("id2 touche = %d\n", var->buff[1]);
		// printf("id3 touche = %d\n", var->buff[2]);
		var->buff[1] = 0;
		var->buff[2] = 0;
	}
	while (var->i != var->inputlen)
		right_arrow(var);
	ft_putstr(tgetstr("cd", NULL));
	if (ft_strchr(var->ret, '!'))
		exclam(var);
	write(1, "\n", 1);
	ft_putstr(tgetstr("ei", NULL)); // END OF INSERT MODE
}

char	*termcaps(t_ssprintf *prompt)
{
	char			*str;
	t_var			*var;

	ft_putstr(prompt->buf);
	var = tvar();
	initvar(var, 1);
	if ((str = getenv("TERM")) == NULL)
		str = ft_strdup("xterm-256color");
	tgetent(NULL, str);
	if (tcgetattr(0, &var->term) == -1)
		error(-6, 0, 0);
	var->termsav = var->term;
	var->term.c_lflag &= ~(ICANON);
	var->term.c_lflag &= ~(ECHO);
	var->term.c_cc[VMIN] = 1;
	var->term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &var->term) == -1)
		error(-6, 0, 0);
	touch(var);
	reset(var);
	str = ft_strdup(var->ret);
	if (var->ret[0] && ft_strcmp("\nhist-i-search : ", prompt->buf))
		add_history(var);
	ft_bzero(prompt->buf, prompt->ret);
	initvar(var, 1);
	return (str);
}
