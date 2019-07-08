/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_totalR.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 19:50:19 by bomanyte          #+#    #+#             *//*   Updated: 2019/07/08 20:13:16 by bomanyte         ###   ########.fr       */

/*                                                                            */
/* ************************************************************************** */

#include "libls.h"
#include <stdio.h>

long long	get_total(t_tree *root)
{
	if (root->name[0] != '.' && !(ft_strncmp(root->name, "..", PATH_MAX) == 0 || (ft_strncmp(root->name, ".", PATH_MAX) == 0))) {
		printf("\nnow blocks we have %lld\n", root->data->blocks);
		printf("now name is %s\n", root->name);
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
		return(get_total(root->next));
	//return get_total(root);
}

long long	get_totalR(t_tree *root)
{
	printf("\nnow blocks we have %lld\n", root->data->blocks);
	printf("now name is %s\n", root->name);
	if (root->par)
		root->par->data->blocks += root->data->blocks;
	if (root->chi) {
		root->data->blocks += get_totalR(root->chi);
	}
	if (root->next) {
		root = root->next;
		get_totalR(root);
		return (root->data->blocks);
	}
	if (!root->next && !root->chi)
		return (root->data->blocks);
	//return get_total(root);
}
