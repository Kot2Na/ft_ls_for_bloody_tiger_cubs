/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 20:47:14 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/10 21:09:59 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

int		size_sort(t_tree *first, t_tree *second)
{
	if (first && second)
	{
		if (first->data->size > second->data->size)
			return (1);
		if (first->data->size < second->data->size)
			return (0);
		if (ascii_sort(first, second))
			return (1);
	}
	return (0);
}

int		ascii_sort(t_tree *first, t_tree *second)
{
	if (first && second)
	{
		if (ft_strcmp(first->name, second->name) > 0)
			return (1);
	}
	return (0);
}
