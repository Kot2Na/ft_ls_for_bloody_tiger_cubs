/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:04:29 by bomanyte          #+#    #+#             */
/*   Updated: 2019/07/07 16:33:26 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

/*there are many error, does not compile*/

void	get_time(t_stat buff, t_tree *node)
{
	char *buff;
	char *time;
	char copy[13];
	int i;
	int j;

	i = 0;
	j = 0;
	buf = ctime(&buff.st_mtime);
	while (copy[i] != '\0')
	{
		copy[i] = buf[j];
		i++;
		j++;
	}
	time = ft_strdup(copy);
	node->time = time;
}

void	fill_data(t_tree *node, char *name)
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
		/*get_id(buff.st_uid, buff.st_gid, node);
		get_mode(buff.st_mode, node);
		get_link(buff.st_nlink, node);
		get_size(buff.st_size, node); */
		get_time(buff, node);
	}
//total
//st_uid
//st_gid
//st_mode (file or directory, permissions, sticky, suid, links)
//st_size
//st_mtime (modification)
//st_nlink
free(buff);
}
