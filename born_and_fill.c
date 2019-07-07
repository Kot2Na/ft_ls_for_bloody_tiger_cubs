/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   born_and_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:45:13 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/06 19:29:12 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

t_tree	*tree_to_start(t_tree *tree)
{
	if (tree)
	{
		while(tree->par)
			tree = tree->par;
		while(tree->pre)
			tree = tree->pre;
	}
	return (tree);
}

t_tree	*tree_open(char *name)
{
	DIR		*fdir;
	t_dir	*file;
	t_tree	*root;

	root = NULL;
	root = tree_create(name);
	if ((fdir = opendir(name)))
	{
		while((file = readdir(fdir)))
			tree_addend_chil(root, tree_create(file->d_name));
		closedir(fdir);
	}
	return (root);
}

t_tree	*tree_born(t_bit *bit, int ac, char **av)
{
	t_tree	*tree;
	int			i;

	i = 1;
	tree = NULL;
	while (av[i] && av[i][0] == '-')
		i++;
	while (av[i])
	{
		tree = tree_addend(tree, tree_open(av[i]));
		i++;
	}
	return (tree);
}
