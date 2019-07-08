/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 14:26:37 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/08 17:35:28 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

int		tree_error(t_tree *tree)
{
	int error;

	error = 0;
	if (tree->data)
		if (tree->data->error != 13)
		{
			ft_putstr("\nft_ls: ");
			ft_putstr(tree->name);
			ft_putstr(": ");
			ft_putstr(strerror(tree->data->error));
			ft_putchar('\n');
			error = 1;
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
			print_name(tree->name);
		if (i % 6 == 0)
			ft_putchar('\n');
		tree = tree->next;
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
		{
			//some function for -l
		}
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
				tree_print(tree->chi, path, bit);
				free(path);
			}
			tree = tree->next;
		}
	}
}
