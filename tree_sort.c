/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 18:23:23 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/09 18:30:40 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

void	tree_swap(t_tree *tree1, t_tree *tree2)
{
	t_tree botle;

	botle = *tree1;
	*tree1 = *tree2;
	*tree2 = botle;
}

void	ascii_sort(t_tree *tree)
{
	t_tree *start;
	int i;

	start = tree;

}
