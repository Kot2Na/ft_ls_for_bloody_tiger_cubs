/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_controller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:52:59 by bomanyte          #+#    #+#             */
/*   Updated: 2019/07/11 21:26:15 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

void	tree_controller(t_tree *root, t_bit *flags)
{
	flags->a ? get_totalr(root) : get_total(root);
	if (flags->l)
		tree_sort(root, ascii_sort);
	if (flags->t)
		 sort_t(root);
	 if (flags->s)
		 tree_sort(root, size_sort);
}
