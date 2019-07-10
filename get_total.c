/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_totalR.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 19:50:19 by bomanyte          #+#    #+#             */
/*   Updated: 2019/07/10 21:25:04 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"
#include <stdio.h>

long long	get_total(t_tree *root)
{
	if (!root->par || (root->name[0] != '.' && !(ft_strncmp(root->name, "..", PATH_MAX) == 0 || (ft_strncmp(root->name, ".", PATH_MAX) == 0)))) {
		if (root->par)
			root->par->data->blocks += root->data->blocks;
		if (root->chi) {
			root->data->blocks += get_total(root->chi);
		}
		if (root->next) {
			root = root->next;
			get_total(root);
			return (root->data->blocks);
		}
		if (!root->next && !root->chi)
			return (root->data->blocks);
	}
	if (root->next)
		get_total(root->next);
	return (0);
}

long long	get_totalr(t_tree *root)
{
	if (root->par)
		root->par->data->blocks += root->data->blocks;
	if (root->chi) {
		root->data->blocks += get_totalr(root->chi);
	}
	if (root->next) {
		root = root->next;
		get_totalr(root);
		return (root->data->blocks);
	}
	if (!root->next && !root->chi)
		return (root->data->blocks);
	return (0);
}
