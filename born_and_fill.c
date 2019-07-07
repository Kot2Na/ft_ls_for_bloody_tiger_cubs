/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   born_and_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:45:13 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/07 15:10:01 by crycherd         ###   ########.fr       */
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

char	*make_path(char *from, char *to)
{
	char *result;

	result = NULL;
	result = ft_strjoin(from, "/");
	from = result;
	result = ft_strjoin(result, to);
	free(from);
	return (result);
}

t_tree	*tree_open(t_bit *bit, t_tree *root, char *name)
{
	DIR		*fdir;
	t_dir	*file;
	t_tree	*leaf;
	char	*path;
	
	path = name;
	if ((fdir = opendir(name)))
	{
		while((file = readdir(fdir)))
		{
			leaf = tree_addend_chil(root, tree_create(file->d_name));
			if (bit->R)
			{
				if (!(ft_strncmp(file->d_name, "..", PATH_MAX) == 0 || (ft_strncmp(file->d_name, ".", PATH_MAX) == 0)))
				{
					path = make_path(name, file->d_name);
					leaf = tree_open(bit, leaf, path);
					free(path);
				}
			}
		}
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
		tree = tree_addend(tree, tree_create(av[i]));
		tree = tree_open(bit, tree, av[i]);
		i++;
	}
	return (tree);
}
