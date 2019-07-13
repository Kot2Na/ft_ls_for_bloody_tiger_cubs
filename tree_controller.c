/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_controller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:52:59 by bomanyte          #+#    #+#             */
/*   Updated: 2019/07/13 17:19:27 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

void	tree_controller(t_tree *root, t_bit *flags)
{
	flags->a ? get_totalr(root) : get_total(root);
	tree_sort(root, ascii_sort);
	if (flags->t)
	{
        sort_t(root);
        sort_t_ascii(root, ascii_sort);
    }
	 if (flags->s)
		 tree_sort(root, size_sort);
}
