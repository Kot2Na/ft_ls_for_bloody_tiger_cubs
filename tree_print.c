/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 14:26:37 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/12 22:52:18 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

int		for_l(t_tree *tree, char *name, t_bit *bit)
{
	char	*path;
	int		i;

	i = 0;
	while (tree)
	{
		if (tree_error(tree))
		{
			tree = tree->next;
			continue ;
		}
		path = make_path(name, tree->name);
		if (one_or_not(tree, bit) && !tree->pre)
		{
			print_path(name);
			i++;
		}
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

	i = 0;
	while (tree)
	{
		if (tree_error(tree))
		{
			tree = tree->next;
			continue ;
		}
		path = make_path(name, tree->name);
		if (one_or_not(tree, bit) && !tree->pre)
			print_path(name);
		if (bit_a(tree, bit))
			i++;
		if (!tree->next && tree->par)
			ft_putchar('\n');
		tree = tree->next;
		free(path);
	}
	return (i);
}

t_tree	*tree_to_last(t_tree *tree)
{
	if (tree)
	{
		while (tree->next)
			tree = tree->next;
		while (tree->pre && !tree->chi)
			tree = tree->pre;
		if (tree->chi)
			tree = tree_to_last(tree->chi);
	}
	return (tree);
}

int		sosna_or_ne(t_tree *tree)
{
	t_tree *sosna;

	if (tree)
	{
		sosna = tree;
		tree = tree_to_start(tree);
		tree = tree_to_last(tree);
		if ((sosna - tree) == 0)
			return (1);
	}
	return (0);
}

void	tree_print(t_tree *tree, char *name, t_bit *bit)
{
	int		i;
	t_tree *sosna;

	if (tree)
	{
		i = bit->l ? for_l(tree, name, bit) : not_for_l(tree, name, bit);
		while (tree)
		{
			if (tree->data && tree->data->error == 13)
			{
				if (i > 0)
					ft_putchar('\n');
				i += tree_error_13(tree, name);
			}
			if (tree->chi)
			{
				if (i > 0)
				{
					ft_putchar('\n');
					i = 0;
				}
				print_chi(tree, name, bit);
			}
			if (sosna_or_ne(tree))
				i = 0;
			else if (i && tree->next && !sosna_or_ne(tree))
			{
				ft_putchar('\n');
				i = 0;
			}
			tree = tree->next;
		}
	}
}
