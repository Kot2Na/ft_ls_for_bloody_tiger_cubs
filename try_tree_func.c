/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 01:10:41 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/08 20:31:46 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"
#include <stdio.h>

t_tree	*tree_create(char *name)
{
	t_tree *new;

	new = NULL;
	if ((new = (t_tree*)malloc(sizeof(t_tree))))
	{
		new->data = malloc(sizeof(t_data));
		new->data->error = 0;
		new->data->type = 0;
		new->data->blocks = 0;
		new->data->rights = NULL;
		new->data->hd_link = 0;
		new->data->soft_ln = NULL;
		new->data->user = NULL;
		new->data->group = NULL;
		new->data->size = 0;
		new->data->time = NULL;
		new->name = ft_strdup(name);
		new->par = NULL;
		new->chi = NULL;
		new->next = NULL;
		new->pre = NULL;
	}
	return (new);
}

t_tree	*tree_addend(t_tree *start, t_tree *new)
{
	if (start)
	{
		while (start->next)
			start = start->next;
		start->next = new;
		new->pre = start;
		new->par = start->par;
	}
	return (new);
}

t_tree	*tree_addend_chil(t_tree *root, t_tree *leaf)
{
	leaf = tree_addend(root->chi, leaf);
	if (!root->chi)
	{
		root->chi = leaf;
		leaf->par = root;
	}
	return (leaf);
}

void	tree_destroy(t_tree *tree)
{
	if (tree)
	{
		tree_destroy(tree->next);
		tree_destroy(tree->chi);
		if (tree->data)
			free(tree->data);
		free(tree->name);
		free(tree);
	}
}

void	tree_print(t_tree *tree, char *name, t_bit *bit)
{
	char	*path;
	int		i;
	t_tree	*start;

	start = tree;
	i = 1;
	if (tree)
	{
		if (bit->R && name)
		{
			ft_putstr(name);
			/*printf("\nuid %s\n", tree->data->user);
			printf("\ngid %s\n", tree->data->group);
			printf("\ntime %s\n", tree->data->time); */
			printf("\nrights %s\n", tree->data->rights);
			printf("\nsoft link %s\n", tree->data->soft_ln);
			/*printf("\nhard links %d\n", tree->data->hd_link);
			printf("\nerrors %d\n", tree->data->error); */
			ft_putchar('\n');
		}
		while (tree)
		{
			ft_putstr(tree->name);
			//printf("\nuid %s\n", tree->data->user);
			 //printf("\ngid %s\n", tree->data->group);
			//printf("\ntime %s\n", tree->data->time);
			printf("\nrights %s\n", tree->data->rights);
			printf("\nsoft link %s\n", tree->data->soft_ln);
			printf("\nblocks %lld\n", tree->data->blocks);
			//printf("\nhard links %d\n", tree->data->hd_link);
			//printf("\nerrors %d\n", tree->data->error);
			ft_putchar(' ');
			tree = tree->next;
			if (i % 5 == 0)
				ft_putchar('\n');
			i++;
		}
		ft_putchar('\n');
		tree = start;
		while (tree)
		{
			if (tree->chi)
			{
				path = make_path(name, tree->name);
				ft_putchar('\n');
			printf("\nrights %s\n", tree->data->rights);
			printf("\nsoft link %s\n", tree->data->soft_ln);
			printf("\nblocks %lld\n", tree->data->blocks);
				tree_print(tree->chi, path, bit);
				free(path);
			}
			tree = tree->next;
		}
	}
}
