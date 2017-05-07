/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 13:58:42 by mleclair          #+#    #+#             */
/*   Updated: 2017/05/07 14:26:27 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chell.h"

int		is_file(char *path)
{
	struct stat *stats;

	stats = palloc(sizeof(struct stat));
	stat(path, stats);
	if (S_ISDIR(stats->st_mode) || S_ISCHR(stats->st_mode) ||
		S_ISBLK(stats->st_mode) || S_ISFIFO(stats->st_mode) ||
		S_ISLNK(stats->st_mode) || S_ISSOCK(stats->st_mode))
	{
		free(stats);
		return (1);
	}
	free(stats);
	return (0);
}
