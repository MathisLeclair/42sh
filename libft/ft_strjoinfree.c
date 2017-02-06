/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 10:45:56 by mleclair          #+#    #+#             */
/*   Updated: 2017/02/06 13:53:29 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(char *s1, char *s2, int k)
{
	int		lentotal;
	char	*str;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	lentotal = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (lentotal) + 1);
	if (str == NULL || s1 == NULL || s2 == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
		str[i++] = s2[j];
	str[i] = '\0';
	if (k == 1 || k == 3)
		free(s1);
	if (k == 2 || k == 3)
		free(s2);
	return (str);
}
