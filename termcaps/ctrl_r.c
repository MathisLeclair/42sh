/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_r.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 13:46:09 by mleclair          #+#    #+#             */
/*   Updated: 2017/05/15 17:18:36 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../chell.h"

void	control_r3(char *str, int j)
{
	int i;

	i = ft_strlen(str) / tgetnum("co") + 2;
	while (i--)
		ft_putstr(tgetstr("up", NULL));
	while (--j)
		ft_putstr(tgetstr("nd", NULL));
}

void	control_r2(char *str, char *tmp, char *tmp2, int i)
{
	free(tvar()->cpy);
	if (str[0] && ((i == 0 && env()->history[i] &&
		ft_strcmp_beg(env()->history[i] + 7, str)) || i != 0))
		tvar()->cpy = env()->history[i] + 7;
	else
		tvar()->cpy = tmp;
	paste(tvar());
	free(tmp);
	tvar()->cpy = tmp2;
}

void	control_r(t_var *var, char *tmp, char *tmp2, int j)
{
	char		*str;
	t_ssprintf	*truc;
	int			i;
	char		*tmp3;

	if (var->termlvl > 0)
		return (free2(tmp, tmp2));
	if (var->cpy)
		tmp2 = ft_strdup(var->cpy);
	truc = palloc(sizeof(t_ssprintf));
	tmp3 = ft_strdup("\nhist-i-search : ");
	truc->buf = tmp3;
	truc->ret = ft_strlen("\nhist-i-search : ");
	str = termcaps(truc, 16, 1);
	free(tmp3);
	control_r3(str, j);
	initvar(var, 1, 10, 0);
	ft_putstr(tgetstr("cd", NULL));
	i = 0;
	while (env()->history[i])
		++i;
	while (i > 0 && str[0] && --i && !ft_strcmp_beg(env()->history[i] + 7, str))
		;
	control_r2(str, tmp, tmp2, i);
	free(str);
}
