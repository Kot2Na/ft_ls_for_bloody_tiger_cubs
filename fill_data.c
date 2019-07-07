/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:04:29 by bomanyte          #+#    #+#             */
/*   Updated: 2019/07/07 17:20:02 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"
#include <stdio.h>

static void		file_set_zero(t_tree *node, int errno)
{
	node->user = NULL;
	node->group = NULL;
	node->hd_link = NULL;
	node->time = NULL;
	node->size = NULL;
	node->rights = NULL;
	node->error = errno;
} 

//static void	get_id(t_tree *node, struct stat *buff)
static void		get_id(struct stat *buff)
{
	char *uid;
	char *gid;
	struct passwd *user_id;
	struct group *group_id;
	user_id = getpwuid(buff->st_uid);
	group_id = getgrgid(buff->st_gid);
	uid = ft_strdup(user_id->pw_name);
	gid = ft_strdup(group_id->gr_name);
	//node->user = uid;
	//node->group = gid;
}

//static void	get_link(t_tree *node, struct stat *buff)
void		get_link(struct stat *buff)
{
	unsigned short hd_link;
	if (!(hd_link = (unsigned short)malloc(sizeof(buff->st_nlink))))
		perror("malloc");
	hd_link = buff->st_nlink;
	//node->hd_link = hd_link;
}

//static void	get_time(t_tree *node, static stat buff)
static void		get_time(struct  stat *buff)
{
	char *buf;
	char *time;
	char copy[13];
	int i;
	int j;

	i = 0;
	j = 4;
	buf = ctime(&buff->st_mtime);
	while (i != 12)
	{
		copy[i] = buf[j];
		i++;
		j++;
	}
	time = ft_strdup(copy);
	printf("%s\n", time);
	//node->time = time;
}

static void		get_size(t_tree *node, struct stat *buff)
{
	long long size;
	size = (long long)malloc(sizeof(buff->st_size));
	size = buff->st_size;
	//node->size = size;
}

static int		get_soft_ln(t_tree *node, struct stat *buff, char *path)
{
	char *buf;
	ssize_t len;

	if (S_ISLNK(buff->st_mode))
	{
		len = buff->st_size + 1;
		if (!(buf = (char *)malloc(len)))
		{
			perror("malloc");
			exit(-1);
		}
		if (readlink(path, buf, len) == -1)
		{
			perror("readlink");
			exit(-1);
		}
		buf[len] = '\0';
		//node->soft_ln = buf;
		return (1);
	}
/*	node->soft_ln = NULL; */
	return (0);
}

static void	get_rwx(char *buf, struct stat *buff)
{
	buf[1] = (buff->st_mode & S_IRUSR) ? 'r' : '-';
	buf[4] = (buff->st_mode & S_IRGRP) ? 'r' : '-';
	buf[7] = (buff->st_mode & S_IROTH) ? 'r' : '-';
	buf[2] = (buff->st_mode & S_IWUSR) ? 'w' : '-';
	buf[5] = (buff->st_mode & S_IWGRP) ? 'w' : '-';
	buf[8] = (buff->st_mode & S_IWOTH) ? 'w' : '-';
	buf[3] = (buff->st_mode & S_IXUSR) ? 'x' : '-';
	buf[6] = (buff->st_mode & S_IXGRP) ? 'x' : '-';
	buf[9] = (buff->st_mode & S_IXOTH) ? 'x' : '-';
}

static void    get_mode(t_tree *node, struct stat *buff, char *path)
{
	int is_l;
	char *buf;
	
	is_l = 0;
	buf = (char *)ft_memalloc(10);
	while (is_l != 10)
	{
		buf[is_l] = '-';
		is_l++;
	}
	is_l = 0;
	if ((is_l = get_soft_ln(node, buff, path)) == -1)
		perror("get_soft_ln");
	get_rwx(buf, buff);
	buf[0] = (buff->st_mode & S_IFDIR) ? 'd' : '-';
	buf[0] = is_l ? 'l' : buf[0];
	buf[9] = (buff->st_mode & S_ISVTX) ? 't' : buf[9];
	buf[3] = (buff->st_mode & S_ISUID) ? 's' : buf[3];
	buf[6] = (buff->st_mode & S_ISGID) ? 's' : buf[6];
	//node->rights = buf;
}

//void	fill_data(t_tree *node, char *name)
void	fill_data(char *name)
{
	//char *path = "/Users/bomanyte/ft_ls/test.c";
	struct stat buff;
	
	if (errno || lstat(name, &buff) == -1)
	{
		//file_set_zero(node, errno);
		errno = 0;
		return ;
	}
	else
	{
		get_id(node, &buff);
		get_link(node, &buff);
		get_size(node, &buff);
		get_mode(node, &buff, name);
		get_time(node, &buff);
		//node->error = 0;
	}
//total
}

int main(int argc, char **argv)
{
	if (argc < 2)
		return (0);
	fill_data(argv[1]);
	return (0);
}
