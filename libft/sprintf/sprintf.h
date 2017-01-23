/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprintf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 13:53:34 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/19 12:14:36 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRINTF_H
# define SPRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <wchar.h>
# include "../libft.h"

typedef int	(*t_fun)(va_list a, int b, char c, char **d);

void		ft_serror(void);
t_fun		*ft_stype(void);
int			ft_sfuckit(char c);
int			ft_sisokay(char c);
int			sconv(int nb, char *net);
char		*ft_sprintf(const char *str, ...);
void		ft_sapliopt(char *res, char *str);
int			ft_sprec(int i, int k, char c, char **str);
int			ft_smoncul(char *opt, char **str, int i);
int			ft_sopts(char *opt, char **str, int i);
char		*ft_sprint(char *str, int k, int u);
void		ft_smemlcat(char *dst, const char *src, int start, int end);
char		*ft_sitoa_base(uintmax_t value, int base, char neg);
int			ft_atoi_base_printf(const char *str, int str_base, int i);
int			ft_ss(va_list ap, int k, char c, char **str);
int			ft_sp(va_list ap, int k, char c, char **str);
int			ft_sd(va_list ap, int k, char c, char **str);
int			ft_si(va_list ap, int k, char c, char **str);
int			ft_so(va_list ap, int k, char c, char **str);
int			ft_su(va_list ap, int k, char c, char **str);
int			ft_sx(va_list ap, int k, char c, char **str);
int			ft_sc(va_list ap, int k, char c, char **str);
int			ft_sisrandom(va_list ap, int i, char c, char **str);
int			ft_shastag(int k, int i, int boul, char **str);
int			ft_snumber(int k, int i, int boul, char **str);
int			ft_sminus(int k, int i, int boul, char **str);
int			ft_splus(int k, int i, int boul, char **str);

#endif
