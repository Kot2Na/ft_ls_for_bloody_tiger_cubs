/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   born_and_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:45:13 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/10 20:48:52 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

void fill_error(t_tree *tree)
{
	t_data *data;

	data = (t_data*)malloc(sizeof(t_data));
	data->error = errno;
	errno = 0;
	tree->data = data;
}

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
			fill_data(leaf, path);
			if (bit->R)
				if (!(ft_strncmp(file->d_name, "..", PATH_MAX) == 0 || (ft_strncmp(file->d_name, ".", PATH_MAX) == 0)))
					leaf = tree_open(bit, leaf, path);
			free(path);
		}
		closedir(fdir);
	}
	else if (errno != 20)
		fill_error(root);
	errno = 0;
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
		fill_data(tree, ".");
		tree = tree_open(bit, tree, tree->name);
	}
	while (av[i])
	{
		tree = tree_addend(tree, tree_create(av[i]));
		fill_data(tree, av[i]);
		tree = tree_open(bit, tree, tree->name);
		i++;
	}
	return (tree);
}
