/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 14:26:37 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/10 21:51:18 by crycherd         ###   ########.fr       */
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

void	for_l(t_tree *tree, char *name, t_bit *bit)
{
	char	*path;
	int		i;

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
			print_total(tree);
		bit_a_l(tree, bit);
		tree = tree->next;
		i++;
		free(path);
	}
}

void	not_for_l(t_tree *tree, char *name, t_bit *bit)
{
	char	*path;
	int		i;

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
		bit_a(tree, bit);
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
