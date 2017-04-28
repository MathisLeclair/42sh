/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:05:01 by mleclair          #+#    #+#             */
/*   Updated: 2017/04/28 17:27:36 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

char	*sig_tab(int i)
{
	if (i == 3)
		return ("Quit");
	else if (i == 6)
		return ("Abort");
	else if (i == 7)
		return ("Bus error");
	else if (i == 8)
		return ("Floating-point exception");
	else if (i == 11)
		return ("Segmentation fault");
	else if (i == 13)
		return ("Broken PIPE");
	else if (i == 18)
		return ("Sig cont");
	else if (i == 19)
		return ("Stop");
	else if (i == 20)
		return ("Stop");
	return ("dunno");
}

void	sig_handler(int i)
{
	if (env()->i != 1)
	{
		ft_putstr(sig_tab(i));
		ft_putstr("\n");
	}
}

void	sig_init(void)
{
	signal(SIGQUIT, sig_handler);
	signal(SIGTSTP, sig_handler);
	signal(SIGSTOP, sig_handler);
	signal(SIGABRT, sig_handler);
	signal(SIGTERM, sig_handler);
	signal(SIGCONT, sig_handler);
	signal(SIGSTOP, sig_handler);
	signal(SIGSEGV, sig_handler);
	signal(SIGBUS, sig_handler);
	signal(SIGABRT, sig_handler);
	signal(SIGFPE, sig_handler);
	signal(SIGPIPE, sig_handler);
}
