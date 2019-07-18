/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 06:09:11 by bomanyte          #+#    #+#             */
/*   Updated: 2019/07/18 03:12:05 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

static int		find_n_length(long long num)
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

unsigned short	max_link(t_tree *root, t_bit *bit)
{
	unsigned short links;
	unsigned short i;

	links = 0;
	i = 1;
	if (root->par)
		root = root->par->chi;
	if (!root->par && !root->chi)
	{
		while (root->pre)
			root = root->pre;
	}
	while (root)
	{
		if (!bit->a)
		{
			if (root->data->hd_link > links && root->name[0] != '.')
				links = root->data->hd_link;
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

int				max_size(t_tree *root, t_bit *bit)
{
	long long size;
	long long i;

	size = 0;
	i = 1;
	if (root->par)
		root = root->par->chi;
	if (!root->par && !root->chi)
	{
		while (root->pre)
			root = root->pre;
	}
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

void			print_hd_link(t_data *data, unsigned short n1)
{
	if (find_n_length(data->hd_link) != n1)
	{
		n1 -= find_n_length(data->hd_link) - 1;
		while (n1--)
			ft_putchar(' ');
	}
	else
		ft_putchar(' ');
}

void			print_size(t_data *data, long long n)
{
	if (find_n_length(data->size) != n)
	{
		n -= find_n_length(data->size) - 1;
		while (n--)
			ft_putchar(' ');
	}
	else
		ft_putchar(' ');
}
