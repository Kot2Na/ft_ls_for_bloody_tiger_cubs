/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 06:41:46 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/16 07:06:42 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

t_tree	*tree_file(t_bit *bit, int ac, char **av)
{
	t_tree *file;
	int i;

	i = 0;
	file = NULL;
	while (av[i] && av[i][0] == '-' && av[i][1] != '\0')
		i++;
	while (av[i])
	{
		if (!dir_valid(av[i]) && errno == ENOTDIR)
		{
			errno = 0;
			file = tree_addend(file, tree_create(av[i]));
			fill_data(file, av[i]);
			file = tree_open(bit, file, file->name);
		}
		i++;
	}
	return (file);
}

void	file_l(t_tree *tree, t_bit *bit)
{
	while (tree)
	{
		if (bit->lgbt)
			print_lgbt(0);
		if (tree_error(tree))
		{
			tree = tree->next;
			continue ;
		}
		bit_a_l(tree, bit);
		tree = tree->next;
	}
	print_lgbt(-666);
}

int		file_not_l(t_tree *tree, t_bit *bit)
{
	int		max;
	int		nbr;

	if (tree && bit)
	{
		nbr = count_tree(tree, bit);
		max = count_name_tree(tree, bit);
		return (print_me_please(tree, bit, nbr, max));
	}
	return (0);
}

void print_file(t_tree *tree, t_bit *bit)
{
	if (tree && bit)
	{
		if (bit->l)
			file_l(tree, bit);
		else
			file_not_l(tree, bit);
	}
}
