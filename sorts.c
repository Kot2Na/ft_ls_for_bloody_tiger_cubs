/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 20:47:14 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/11 18:08:48 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

//static int is_sorted_ascii(t_tree *root)
//{
//    t_tree *p;
//
//    if (!root || !root->pre)
//        return (1);
//    while (root->pre != NULL)
//        root = root->pre;
//    while (ft_strncmp(root->name, "..", PATH_MAX) == 0 || (ft_strncmp(root->name, ".", PATH_MAX) == 0))
//        root = root->next;
//    p = root->next;
//    while (root)
//    {
//        while (p)
//        {
//            if (root->data->time_hash == p->data->time_hash && ft_strcmp(root->name, p->name) < 0)
//                return (0);
//            p = p->next;
//        }
//        root = root->next;
//        if (root)
//            p = root->next;
//    }
//    return (1);
//}

static void time_ascii(t_tree *root, int (*s)(t_tree *, t_tree *))
{
    t_tree *p;

    p = root->next;
    while (p)
    {
        if (root->data->time_hash == p->data->time_hash && ft_strcmp(root->name, p->name) > 0)
        {
            if (root->next == p)
                sort_next(root, p);
            else
                sort_not_next(root, p);
            root = p;
        }
        p = p->next;
    }
//    if (is_sorted_ascii(root))
//        return ;
    if (!root->next)
        return ;
    return(time_ascii(root->next, s));
}

void    sort_t_ascii(t_tree *root, int (*s)(t_tree *, t_tree *))
{
    t_tree *p;

    if (!root)
        return ;
    if (!root->par)
        return(sort_t_ascii(root->chi, s));
    while (root && (ft_strncmp(root->name, "..", PATH_MAX) == 0 || (ft_strncmp(root->name, ".", PATH_MAX) == 0)))
        root = root->next;
    p = root;
    if (!p)
        return ;
    time_ascii(p, s);
    p = p->par->chi->next->next;
    while (p) {
        if (p->chi)
            time_ascii(p->chi, s);
        p = p->next;
    }
}

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
