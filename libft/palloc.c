/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 15:57:53 by mleclair          #+#    #+#             */
/*   Updated: 2017/04/06 16:01:02 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*palloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		ft_putstr_fd("MALLOC ERROR GET A LIFE & RAM FUCKTARD\n", 2);
	return (ptr);
}
