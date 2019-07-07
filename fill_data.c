/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:04:29 by bomanyte          #+#    #+#             */
/*   Updated: 2019/07/06 22:00:44 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

void	get_time(static stat buff, t_tree *node)
{
	char *buff;
	char *time;

	buf = ctime(&buff.st_mtime);
	//find length of time
	//we need 2nd, 3d fields in string. size is always fixed: 3 chars for month, 5 for time.
	time = ft_strdup(ctime(&buff.st_mtime));
}

void	fill_data(char *name, t_tree *node)
{
	struct stat buff;
	
	if (errno)
	{
		node->error = errno;
		errno = 0;
		return ;
	}
	else
	{
		lstat(name, &buff);
		get_id(buff.st_uid, buff.st_gid, node);
		get_mode(buff.st_mode, node);
		get_link(buff.st_nlink, node);
		get_size(buff.st_size, node);
		get_time(buff, node);
	}
//total
//st_uid
//st_gid
//st_mode (file or directory, permissions, sticky, suid, links)
//st_size
//st_mtime (modification)
//st_nlink
}
