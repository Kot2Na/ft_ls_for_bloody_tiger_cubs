/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   born_and_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:45:13 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/08 17:55:05 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"
#include <stdio.h>

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
	if (from)
	{
		result = ft_strjoin(from, "/");
		from = result;
		result = ft_strjoin(result, to);
		free(from);
	}
	else
		result = ft_strdup(to);
	return (result);
}

t_tree	*tree_open(t_bit *bit, t_tree *root, char *name)
{
	DIR		*fdir;
	t_dir	*file;
	t_tree	*leaf;
	char	*path;
	
	if ((fdir = opendir(name)))
	{
		while((file = readdir(fdir)))
		{
			path = make_path(name, file->d_name);
			leaf = tree_addend_chil(root, tree_create(file->d_name));
			printf("%p\n", leaf->data);
			fill_data(leaf, path);
/*			printf("\npath %s\n", path);
			printf("\nuid %s\n", leaf->data->user);
			printf("\ngid %s\n", leaf->data->group);
			printf("\ntime %s\n", leaf->data->time);
			printf("\nrights %s\n", leaf->data->rights);
			printf("\nsoft link %s\n", leaf->data->soft_ln);
			printf("\nhard links %d\n", leaf->data->hd_link);
			printf("\nerrors %d\n", leaf->data->error); */
			free(path);
			if (bit->R)
			{
				if (!(ft_strncmp(file->d_name, "..", PATH_MAX) == 0 || (ft_strncmp(file->d_name, ".", PATH_MAX) == 0)))
				{
					path = make_path(name, file->d_name);
					fill_data(leaf, path);
		/*	printf("\nuid %s\n", leaf->data->user);
			printf("\ngid %s\n", leaf->data->group);
			printf("\ntime %s\n", leaf->data->time);
			printf("\nrights %s\n", leaf->data->rights);
			printf("\nsoft link %s\n", leaf->data->soft_ln); */
					leaf = tree_open(bit, leaf, path);
					//fill_data(leaf, path);
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
	if (i == ac)
	{
		tree = tree_addend(tree, tree_create("."));
		tree = tree_open(bit, tree, tree->name);
	}
	while (av[i])
	{
		tree = tree_addend(tree, tree_create(av[i]));
		tree = tree_open(bit, tree, tree->name);
		i++;
	}
	return (tree);
}
