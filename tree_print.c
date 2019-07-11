/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 14:26:37 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/11 16:44:25 by crycherd         ###   ########.fr       */
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
			ft_putstr("ft_ls: ");
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

int		for_l(t_tree *tree, char *name, t_bit *bit)
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
		if (one_or_not(tree) && !tree->pre)
			print_path(name);
		if (tree->par && !tree->pre)
			print_total(tree);
		if (bit_a_l(tree, bit))
			i++;
		tree = tree->next;
		free(path);
	}
	return (i);
}

int		not_for_l(t_tree *tree, char *name, t_bit *bit)
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
		if (bit_a(tree, bit))
			i++;
		if (i % 6 == 0)
			ft_putchar('\n');
		tree = tree->next;
		free(path);
	}
	return (i);
}

void	tree_print(t_tree *tree, char *name, t_bit *bit)
{
	int		i;

	if (tree)
	{
		i = bit->l ? for_l(tree, name, bit) : not_for_l(tree, name, bit);
		while (tree)
		{
			if (tree->data && tree->data->error == 13)
				tree_error_13(tree, name);
			if (i > 1)
			{
				ft_putchar('\n');
				i = 0;
			}
			if (tree->chi)
				print_chi(tree, name, bit);
			tree = tree->next;
		}
	}
}
