/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 01:11:17 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/12 19:56:33 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

int main(int ac, char **av)
{
	t_bit	*flag;
	t_tree	*tree;
	t_tree	*tree_er;

	flag = create_flag(ac, av);
	tree_er = tree_invalid(ac, av, flag);
	tree = tree_born(flag, ac, av);
	if (tree)
	{
		tree = tree_to_start(tree);
		flag->a ? get_totalr(tree) : get_total(tree);
		tree_controller(tree, flag);
	}
	if (tree_er)
	{
		tree_er = tree_to_start(tree_er);
		tree_sort(tree_er, ascii_sort);
		tree_er = tree_to_start(tree_er);
	}
	tree_print(tree_er, NULL, flag);
	tree_print(tree, NULL, flag);
	tree_destroy(tree);
	tree_destroy(tree_er);
	free(flag);
	return (0);
}
