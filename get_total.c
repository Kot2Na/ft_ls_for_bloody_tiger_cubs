/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_total.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 19:50:19 by bomanyte          #+#    #+#             */
/*   Updated: 2019/07/08 20:23:17 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

long long	get_total(t_tree *root, int size)
{
	long long blocks;
	if (root->type != 2 && root->next)
	{
		size = root->blocks;
		size += get_total(root->next);
	}
	else if (root->type != 2 && !root->next)
		return (size);
	if (root && root->child)
		root->blocks = get_total(root->chi);
	return (root->blocks);
}
