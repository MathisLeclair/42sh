/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base_pr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/16 18:52:27 by exam              #+#    #+#             */
/*   Updated: 2016/12/12 16:37:26 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi_base_printf(const char *str, int str_base, int i)
{
	int		j;
	int		nb;
	char	*str1;
	char	*str2;

	nb = 0;
	str1 = "0123456789abcdef";
	str2 = "0123456789ABCDEF";
	while (str[i] == '+' || str[i] == '-' || str[i] == '#' ||
		str[i] == ' ' || str[i] == '0')
		++i;
	while ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'f')
	|| (str[i] >= 'A' && str[i] <= 'F'))
	{
		if (str[i] == '#')
			++i;
		j = 0;
		while (str[i] != str1[j] && str[i] != str2[j])
			++j;
		if (j >= str_base)
			return (nb * (str[0] == '-' ? -1 : 1));
		nb = nb * str_base + j;
		++i;
	}
	return (nb * (str[0] == '-' ? -1 : 1));
}
