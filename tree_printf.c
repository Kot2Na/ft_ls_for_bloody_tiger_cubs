/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 16:07:43 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/15 07:53:32 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

static int find_n_length(long long num)
{
    long long i;

    i = 1;
    while (num / 10 != 0)
    {
        num = num / 10;
        i++;
    }
    return (i);
}

static unsigned short max_link(t_tree *root, t_bit *bit)
{
    unsigned short links;
    unsigned short i;

    links = 0;
    i = 1;
//    while (root->pre)
//        root = root->pre;
    //if (bit->a)
        root = root->par->chi;
        //root = root->par->chi->next->next;
    while (root)
    {
    	if (!bit->a)
		{
        	if (root->data->hd_link > links && root->name[0] != '.')
            	links = root->data->hd_link;
			//while (root && root->name[0] == '.')
			//	root = root->next;
			//if (!root)
			//	return (0);
		}
		else if (root->data->hd_link > links)
            links = root->data->hd_link;
        root = root->next;
    }
    while (links / 10 != 0)
    {
        links = links / 10;
        i++;
    }
    return (i);
}

static int max_size(t_tree *root, t_bit *bit)
{
    long long size;
    long long i;

    size = 0;
    i = 1;
//    while (root->pre)
//        root = root->pre;
//	if (bit->a)
   		root = root->par->chi;
//	else    
//		root = root->par->chi->next->next;
    while (root)
    {
		if (!bit->a)
		{	
			if (root->data->size > size && root->name[0] != '.')
            	size = root->data->size;
		}
		else if (root->data->size > size)
            size = root->data->size;
        root = root->next;
    }
    while (size / 10 != 0)
    {
        size = size / 10;
        i++;
    }
    return (i);
}

static void	print_par_l(t_data *data, long long n, unsigned short n1)
{
	ft_putstr(data->rights);
	ft_putchar(' ');
    if (find_n_length(data->hd_link) != n1)
    {
        n1 -= find_n_length(data->hd_link) - 1;
        while (n1--)
            ft_putchar(' ');
    }
    else
        ft_putchar(' ');
    ft_putlongnbr(data->hd_link);
    ft_putchar(' ');
	ft_putstr(data->user);
	ft_putchar(' ');
	ft_putstr(data->group);
	ft_putchar(' ');
	if (find_n_length(data->size) != n)
	{
	    n -= find_n_length(data->size) - 1;
        while (n--)
            ft_putchar(' ');
    }
	else
        ft_putchar(' ');
    ft_putlongnbr(data->size);
    ft_putchar(' ');
	ft_putstr(data->time);
	ft_putchar(' ');
}

void	print_path(char *path)
{
	if (path)
	{
		ft_putstr(path);
		ft_putstr(":\n");
	}
}

void	print_name(char *name)
{
	if (name)
	{
		ft_putstr(name);
		ft_putchar('\t');
	}
}

void	print_str_l(t_tree *tree, t_bit *bit)
{
    long long n;
    unsigned short n1;

    n = max_size(tree, bit);
    n1 = max_link(tree, bit);
	if (tree)
	{
		print_par_l(tree->data, n, n1);
		ft_putstr(tree->name);
		ft_putchar('\n');
	}
}

void	print_total(t_tree *tree)
{
	if (tree && tree->par->data->blocks != 0)
	{
		ft_putstr("total ");
		ft_putnbr(tree->par->data->blocks);
		ft_putchar('\n');
	}
}
