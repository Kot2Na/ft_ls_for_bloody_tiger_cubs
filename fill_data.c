/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:04:29 by bomanyte          #+#    #+#             */
/*   Updated: 2019/07/08 18:06:09 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

static void		file_set_zero(t_tree *node, int err)
{
	node->data->user = NULL;
	node->data->group = NULL;
	node->data->hd_link = 0;
	node->data->time = NULL;
	node->data->size = 0;
	node->data->rights = NULL;
	node->data->error = err;
	node->data->type = 0;
	node->data->soft_ln = NULL;
} 

//static void		get_id(struct stat *buff)
static void	get_id(t_tree *node, struct stat *buff)
{
	char *uid;
	char *gid;
	struct passwd *user_id;
	struct group *group_id;

	user_id = getpwuid(buff->st_uid);
	group_id = getgrgid(buff->st_gid);
	node->data->user = ft_strdup(user_id->pw_name);
	node->data->group = ft_strdup(group_id->gr_name);
}

static void	get_time(t_tree *node, struct stat *buff)
//static void		get_time(struct  stat *buff)
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
	node->data->time = ft_strdup(copy);
}

static void		get_size(t_tree *node, struct stat *buff)
//static void		get_size(struct stat *buff)
{
	node->data->blocks = buff->st_blocks;
	node->data->type = (buff->st_mode & S_IFDIR) ? 2 : 1;
	node->data->size = buff->st_size;
	node->data->hd_link = buff->st_nlink; 
	return ;
}

static int		get_soft_ln(t_tree *node, struct stat *buff, char *path)
//static int		get_soft_ln(struct stat *buff, char *path)
{
	char *buf;
	ssize_t len;

	//printf("\n\npath for soft link is %s\n\n", path);
	if (S_ISLNK(buff->st_mode))
	{
		len = buff->st_size;
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
		node->data->soft_ln = buf;
		return (1);
	}
	node->data->soft_ln = NULL; 
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
//static void    get_mode(struct stat *buff, char *path)
{
	int is_l;
	char *buf;
	
	is_l = 0;
	buf = (char *)ft_memalloc(10);
	is_l = 0;
	if ((is_l = get_soft_ln(node, buff, path)) == -1)
		perror("get_soft_ln");
	get_rwx(buf, buff);
	buf[0] = (buff->st_mode & S_IFDIR) ? 'd' : '-';
	buf[0] = is_l ? 'l' : buf[0];
	buf[3] = ((buf[3] == 'x') && (buff->st_mode & S_ISUID)) ? 's' : buf[3];
	buf[3] = ((buf[3] != 's') && (buf[3] != 'x') && (buff->st_mode & S_ISUID)) ? 'S' : buf[3];
	buf[6] = ((buf[3] == 'x') && (buff->st_mode & S_ISUID)) ? 's' : buf[6];
	buf[6] = ((buf[6] != 's') && (buf[6] != 'x') && (buff->st_mode & S_ISUID)) ? 'S' : buf[6];
	buf[9] = ((buf[9] == 'x') && (buff->st_mode & S_ISVTX)) ? 't' : buf[9];
	buf[9] = ((buf[9] != 'x') && (buf[9] != 't') && (buff->st_mode & S_ISVTX)) ? 'T' : buf[9];
	node->data->rights = buf;
	//printf("rights %s\n", node->data->rights);
}

void	fill_data(t_tree *node, char *name)
//void	fill_data(char *name)
{
	struct stat buff;

//	node->data = malloc(sizeof(t_data));
	if (errno || lstat(name, &buff) == -1)
	{
		file_set_zero(node, (int) errno);
		errno = 0;
		return ;
	}
	get_id(node, &buff);
	get_size(node, &buff);
	get_mode(node, &buff, name);
	get_time(node, &buff);
}


/*int main(int argc, char **argv)
{
	if (argc < 2)
		return (0);
	fill_data(argv[1]);
	return (0);
}  */
