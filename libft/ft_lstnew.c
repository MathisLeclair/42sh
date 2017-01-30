/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 13:37:52 by mleclair          #+#    #+#             */
/*   Updated: 2016/11/08 09:38:40 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *penis;

	penis = (t_list *)malloc(sizeof(t_list));
	if (penis == NULL)
		return (NULL);
	if (content == NULL)
	{
		penis->content = NULL;
		penis->content_size = 0;
	}
	else
	{
		penis->content = (void *)malloc(content_size);
		if (penis->content == NULL)
			return (NULL);
		ft_memcpy(penis->content, content, content_size);
		penis->content_size = content_size;
	}
	penis->next = NULL;
	return (penis);
}
