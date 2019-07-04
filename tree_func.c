/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 01:10:41 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/05 02:20:26 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

t_tree	*tree_create(char *name)
{
	t_tree *new;

	new = NULL;
	if ((new = (t_tree*)malloc(sizeof(t_tree))))
	{
		new->name = ft_strdup(name);
		new->data = NULL;
		new->par = NULL;
		new->chi = NULL;
		new->nex = NULL;
		new->pre = NULL;
	}
	return (new);
}

t_tree *tree_addend(t_tree *start, t_tree *new)
{
	if (start)
	{
		while (start->next)
			start = start->next;
		start->next = new;
		new->pre = start;
		new->par = start->parent;
	}
	return (new);
}

t_tree *tree_addend_chil(t_tree *root, t_tree *leaf)
{
	leaf = tree_addend(root->chi, leaf);
	if (!root->chi)
	{
		root->chi = leaf;
		leaf->par = root;
	}
	return (leaf);
}

void tree_destroy(t_tree *tree)
{
	if (tree)
	{
		tree_destroy(tree->next);
		tree_destroy(tree->child);
		ft_putstr(tree->name);
		ft_putstr("was delete\n")
		if (tree->data)
			free(data);
		free(tree->name);
		free(tree);
	}
}

