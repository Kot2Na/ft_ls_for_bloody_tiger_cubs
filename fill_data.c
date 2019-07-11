/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:04:29 by bomanyte          #+#    #+#             */
/*   Updated: 2019/07/11 16:55:35 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"
#include <stdio.h>

char	*time_to_str(char *buf)
{
    char copy[13];
    int i;
    int j;

    copy[12] = '\0';
    i = 0;
    j = 4;
    while (i != 12)
    {
        copy[i] = buf[j];
        i++;
        j++;
    }
    return(ft_strdup(copy));
}

static int is_sorted(t_tree *root)
{
    t_tree *p;

    if (!root || !root->pre)
        return (1);
    while (root->pre != NULL)
        root = root->pre;
    while (ft_strncmp(root->name, "..", PATH_MAX) == 0 || (ft_strncmp(root->name, ".", PATH_MAX) == 0))
        root = root->next;
    p = root->next;
    while (root)
    {
        while (p)
        {
            if (root->data->time_hash < p->data->time_hash)
                return (0);
            p = p->next;
        }
        root = root->next;
        if (root)
            p = root->next;
    }
    return (1);
}

static void sort_next(t_tree *root, t_tree *p)
{
	root->pre->next = p;
	if (p->next)
		p->next->pre = root;
	root->next = p->next;
	p->next = root;
	p->pre = root->pre;
	root->pre = p;
}

static void	sort_not_next(t_tree *root, t_tree *p)
{
	t_tree *tmp;

	tmp = root->pre;
	root->pre = p->pre;
	p->pre = tmp;
	tmp = root->next;
	root->next = p->next;
	p->next = tmp;
	p->next->pre = p;
	p->pre->next = p;
	if (root->next)
		root->next->pre = root;
	root->pre->next = root;
}

static void sort_tree(t_tree *root)
{
        t_tree *p;

		p = root->next;
		while (p)
		{
			if (root->data->time_hash < p->data->time_hash)
			{
				if (root->next == p)
					sort_next(root, p);
				else
					sort_not_next(root, p);
				root = p;
			}
			p = p->next;
		}
		if (is_sorted(root))
			return ;
        if (!root->next)
            return ;
		return(sort_tree(root->next));
}

void    sort_t(t_tree *root)
{
    t_tree *p;


    if (root && !root->par)
        return(sort_t(root->chi));
    while (root && (ft_strncmp(root->name, "..", PATH_MAX) == 0 || (ft_strncmp(root->name, ".", PATH_MAX) == 0)))
        root = root->next;
    p = root;
    if (!p)
        return ;
    sort_tree(p);
}

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
    node->data->time_hash = 0;
} 

static void	get_id(t_tree *node, t_stat *buff)
{
	struct passwd *user_id;
	struct group *group_id;

	user_id = getpwuid(buff->st_uid);
	group_id = getgrgid(buff->st_gid);
	node->data->user = ft_strdup(user_id->pw_name);
	node->data->group = ft_strdup(group_id->gr_name);
}

static int get_month(const char *buf)
{
    char month[4];
    int res;

    month[0] = buf[4];
    month[1] = buf[5];
    month[2] = buf[6];
    res = ft_strcmp(month, "Jan") ? 0 : 1;
    res = ft_strcmp(month, "Feb") ? res : 2;
    res = ft_strcmp(month, "Mar") ? res : 3;
    res = ft_strcmp(month, "Apr") ? res : 4;
    res = ft_strcmp(month, "May") ? res : 5;
    res = ft_strcmp(month, "Jun") ? res : 6;
    res = ft_strcmp(month, "Jul") ? res : 7;
    res = ft_strcmp(month, "Avg") ? res : 8;
    res = ft_strcmp(month, "Sep") ? res : 9;
    res = ft_strcmp(month, "Oct") ? res : 10;
    res = ft_strcmp(month, "Nov") ? res : 11;
    res = ft_strcmp(month, "Dec") ? res : 12;
    return (res);
}


static int get_year(const char *buf)
{
    int res;

    buf = buf + 19;
    printf("year buf is %s\n", buf);
    if (*buf == ' ')
        buf++;
    res = *buf++ - '0';
    while (*buf != '\n')
    {
        res = res * 10 + (*buf - '0');
        buf++;
    }
    return (res);
}

static void		get_size_nd_time(t_tree *node, t_stat *buff)
{
    char *buf;
    long int copy;
    int j;

    buf = ctime(&buff->st_mtime);
    copy = get_year(buf);
    copy =  (j = get_month(buf)) <= 9 ? copy * 100 + j : copy * 10 + j;
    j = 7;
    while (j != 19)
    {
        if (j == 8 && buf[j] == ' ')
            copy = copy * 10;
        else if (buf[j] >= 46 && buf[j] <= 57)
            copy = copy * 10 + (buf[j] - '0');
        j++;
    }
    node->data->time_hash = copy;
    node->data->time = time_to_str(buf);
    node->data->blocks = buff->st_blocks;
	node->data->type = (buff->st_mode & S_IFDIR) ? 2 : 1;
	node->data->size = buff->st_size;
	node->data->hd_link = buff->st_nlink;
}

static int		get_soft_ln(t_tree *node, t_stat *buff, char *path)
{
	char *buf;
	ssize_t len;

	if (S_ISLNK(buff->st_mode))
	{
		len = buff->st_size;
		if (!(buf = (char *)malloc(len)))
		{
			//perror("malloc");
			exit(-1);
		}
		if (readlink(path, buf, len) == -1)
		{
			//perror("readlink");
			exit(-1);
		}
		buf[len] = '\0';
		node->data->soft_ln = buf;
		return (1);
	}
	node->data->soft_ln = NULL; 
	return (0);
}

static void	get_rwx(char *buf, t_stat *buff)
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

static void    get_mode(t_tree *node, t_stat *buff, char *path)
{
	int is_l;
	char *buf;
	
	is_l = 0;
	buf = (char *)ft_memalloc(11);
	if ((is_l = get_soft_ln(node, buff, path)) == -1)
	{
		//perror("get_soft_ln");
	}
	get_rwx(buf, buff);
	buf[0] = (buff->st_mode & S_IFDIR) ? 'd' : '-';
	buf[0] = is_l ? 'l' : buf[0];
	buf[3] = ((buf[3] == 'x') && (buff->st_mode & S_ISUID)) ? 's' : buf[3];
	buf[3] = ((buf[3] != 's') && (buf[3] != 'x') && (buff->st_mode & S_ISUID)) ? 'S' : buf[3];
	buf[6] = ((buf[6] == 'x') && (buff->st_mode & S_ISUID)) ? 's' : buf[6];
	buf[6] = ((buf[6] != 's') && (buf[6] != 'x') && (buff->st_mode & S_ISUID)) ? 'S' : buf[6];
	buf[9] = ((buf[9] == 'x') && (buff->st_mode & S_ISVTX)) ? 't' : buf[9];
	buf[9] = ((buf[9] != 'x') && (buf[9] != 't') && (buff->st_mode & S_ISVTX)) ? 'T' : buf[9];
	node->data->rights = buf;
}

void	fill_data(t_tree *node, char *name)
{
	t_stat buff;

	if (errno || lstat(name, &buff) == -1)
	{
		file_set_zero(node, (int) errno);
		errno = 0;
		return ;
	}
	file_set_zero(node, (int) 0);
	get_id(node, &buff);
	get_size_nd_time(node, &buff);
	get_mode(node, &buff, name);
}
