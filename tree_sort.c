/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 18:23:23 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/09 20:49:38 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"
#include <stdio.h>

void	tree_swap(t_tree *tree1, t_tree *tree2)
{
	if (tree1->pre)
		tree1->pre->next = tree2;
	if (tree2->next)
		tree2->next->pre = tree1;
	tree2->pre = tree1->pre;
	tree1->next = tree2->next;
	tree2->next = tree1;
	tree1->pre = tree2;
	if (tree1->par->chi - tree1 == 0)
		tree1->par->chi = tree2;
}

void	ascii_sort(t_tree *tree)
{
	t_tree *start;
	t_tree *first;
	t_tree *second;

	if (tree)
	{
		first = tree;
		while (first)
		{
			second = first;
			start = tree;
			while (second && start)
			{
				if (start->next && (ft_strcmp(start->name, start->next->name) > 0))
					tree_swap(start, start->next);
				start = start->next;
				second = second->next;
			}
			first = first->next;
		}
		while (tree)
		{
			if(tree->chi)
				ascii_sort(tree->chi);
			tree = tree->next;
		}
	}
}
