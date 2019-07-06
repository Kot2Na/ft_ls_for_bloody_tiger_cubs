/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 01:11:17 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/05 03:23:14 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

int	main(int ac, char **av)
{
	DIR *fdir;
	t_dir *dir;
	t_tree *tree;

	fdir = opendir(av[1]);
	while ((dir = readdir(fdir)))
		tree = tree_addend(tree, tree_create(dir->d_name));
	closedir(fdir);
	while (tree->pre)
		tree = tree->pre;
	tree_print(tree);
	ft_putchar('\n');
	tree_destroy(tree);
	return (0);
}
