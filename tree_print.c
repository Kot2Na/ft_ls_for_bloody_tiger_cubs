/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 14:26:37 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/09 16:51:39 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

int		tree_error(t_tree *tree)
{
	int error;

	error = 0;
	if (tree->data)
	{
		if (tree->data->error != 13 && tree->data->error != 0)
		{
			ft_putstr("\nft_ls: ");
			ft_putstr(tree->name);
			ft_putstr(": ");
			ft_putstr(strerror(tree->data->error));
			ft_putchar('\n');
			error = 1;
		}
	}
	return (error);
}


void	tree_error_13(t_tree *tree, char *name)
{
	char *path;

	if (tree)
	{
		path = make_path(name, tree->name);
		print_path(path);
		ft_putstr("ft_ls: ");
		ft_putstr(tree->name);
		ft_putstr(": ");
		ft_putstr(strerror(tree->data->error));
		ft_putchar('\n');
		free(path);
	}
}

void	print_par_l(t_data *data)
{
	ft_putstr(data->rights);
	ft_putchar(' ');
	ft_putnbr((int) data->hd_link);
	ft_putchar(' ');
	ft_putstr(data->user);
	ft_putchar(' ');
	ft_putstr(data->group);
	ft_putchar(' ');
	ft_putnbr((int) data->size);
	ft_putchar(' ');
	ft_putstr(data->time);
	ft_putchar(' ');
}

void	for_l(t_tree *tree, char *name, t_bit *bit)
{
	char *path;
	int i;

	i = 1;
	while (tree)
	{
		if (tree_error(tree))
		{
			tree = tree->next;
			continue ;
		}
		path = make_path(name, tree->name);
		if (one_or_not(tree) && i == 1)
			print_path(name);
		if (tree->par && i == 1)
		{
			ft_putstr("total ");
			ft_putnbr(tree->par->data->blocks);
			ft_putchar('\n');
		}
		if (tree->par)
		{
			if (bit->a)
			{
				print_par_l(tree->data);
				ft_putstr(tree->name);
				ft_putchar('\n');
			}
			else if (tree->name[0] != '.')
			{
				print_par_l(tree->data);
				ft_putstr(tree->name);
				ft_putchar('\n');
			}
		}
		tree = tree->next;
		i++;
		free(path);
	}
}

void	not_for_l(t_tree *tree, char *name, t_bit *bit)
{
	char *path;
	int i;

	i = 1;
	while (tree)
	{
		if (tree_error(tree))
		{
			tree = tree->next;
			continue ;
		}
		path = make_path(name, tree->name);
		if (one_or_not(tree) && i == 1)
			print_path(name);
		if (tree->par)
		{
			if (bit->a)
				print_name(tree->name);
			else if (tree->name[0] != '.')
				print_name(tree->name);
		}
		if (i % 6 == 0)
			ft_putchar('\n');
		tree = tree->next;
		free(path);
		i++;
	}
	ft_putchar('\n');
}

void	tree_print(t_tree *tree, char *name, t_bit *bit)
{
	char	*path;

	if (tree)
	{
		if (bit->l)
			for_l(tree, name, bit);
		else
			not_for_l(tree, name, bit);
		while (tree)
		{
			if (tree->data && tree->data->error == 13)
				tree_error_13(tree, name);
			if (tree->chi)
			{
				path = make_path(name, tree->name);
				ft_putchar('\n');
				if (bit->a)
					tree_print(tree->chi, path, bit);
				else if (tree->name[0] != '.' || !tree->par)
					tree_print(tree->chi, path, bit);
				free(path);
			}
			tree = tree->next;
		}
	}
}
