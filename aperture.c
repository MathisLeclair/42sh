/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aperture.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 16:36:54 by mleclair          #+#    #+#             */
/*   Updated: 2017/03/07 13:16:56 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	aperture2(void)
{
	char	buf[5];
	int		fd;
	int		truc;

	truc = fork();
	if (truc == 0)
	{
		env()->i = 0;
		if ((fd = open("stillalive.txt", O_RDONLY)) == -1)
		{
			ft_putstr("But why delete it ? you monster\n");
			return ;
		}
		while (read(fd, buf, 1))
		{
			write(1, &buf[0], 1);
			usleep(80000);
		}
		exit(0);
	}
	else
		wait(NULL);
}

void	ft_aperture(void)
{
	ft_printf("\033[01;33m");
	ft_printf("%s\n", "");
	ft_printf("%s\n", "              .,-:;//;:=,");
	ft_printf("%s\n", "          . :H@@@MM@M#H/.,+%;,");
	ft_printf("%s\n", "       ,/X+ +M@@M@MM%=,-%HMMM@X/,");
	ft_printf("%s\n", "     -+@MM; $M@@MH+-,;XMMMM@MMMM@+-");
	ft_printf("%s\n", "    ;@M@@M- XM@X;. -+XXXXXHHH@M@M#@/.");
	ft_printf("%s\n", "  ,%MM@@MH ,@%=             .---=-=:=,.");
	ft_printf("%s\n", "  =@#@@@MX.,                -%HX$$%%%:;");
	ft_printf("%s\n", " =-./@M@M$                   .;@MMMM@MM:");
	ft_printf("%s\n", " X@/ -$MM/                    . +MM@@@M$");
	ft_printf("%s\n", ",@M@H: :@:                    . =X#@@@@-");
	ft_printf("%s\n", ",@@@MMX, .                    /H- ;@M@M=");
	ft_printf("%s\n", ".H@@@@M@+,                    %MM+..%#$.");
	ft_printf("%s\n", " /MMMM@MMH/.                  XM@MH; =;");
	ft_printf("%s\n", "  /%+%$XHH@$=              , .H@@@@MX,");
	ft_printf("%s\n", "   .=--------.           -%H.,@@@@@MX,");
	ft_printf("%s\n", "   .%MM@@@HHHXX$$$%+- .:$MMX =M@@MM%.");
	ft_printf("%s\n", "     =XMMM@MM@MM#H;,-+HMM@M+ /MMMX=");
	ft_printf("%s\n", "       =%@M@M#@$-.=$@MM@@@M; %M%=");
	ft_printf("%s\n", "         ,:+$+-,/H#MMMMMMM@= =,");
	ft_printf("%s\n", "               =++%%%%+/:-.");
	ft_printf("\033[0m");
	aperture2();
}
