/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mepalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:16:07 by mleclair          #+#    #+#             */
/*   Updated: 2016/11/08 09:39:59 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_mepalloc(size_t size)
{
	void *truc;

	truc = (void *)palloc(size);
	if (truc == NULL)
		return (NULL);
	ft_memset(truc, 0, size);
	return (truc);
}
