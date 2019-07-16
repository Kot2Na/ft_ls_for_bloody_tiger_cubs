/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 05:48:01 by bomanyte          #+#    #+#             */
/*   Updated: 2019/07/16 05:49:39 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

static int		is_sorted(t_tree *root)
{
	t_tree *p;

	if (!root)
		return (1);
	while (root->pre != NULL)
		root = root->pre;
	p = root->next;
	while (root)
	{
		while (p)
		{
			if (root->data->time_hash < p->data->time_hash)
				return (0);
			p = p->next;
		}
		root = root->next;
		if (root)
			p = root->next;
	}
	return (1);
}

void			sort_next(t_tree *root, t_tree *p)
{
	if (root->pre)
		root->pre->next = p;
	else
		root->par->chi = p;
	if (p->next)
		p->next->pre = root;
	root->next = p->next;
	p->next = root;
	p->pre = root->pre;
	root->pre = p;
}

void			sort_not_next(t_tree *root, t_tree *p)
{
	t_tree *tmp;

	tmp = root->pre;
	root->pre = p->pre;
	p->pre = tmp;
	tmp = root->next;
	root->next = p->next;
	p->next = tmp;
	p->next->pre = p;
	if (p->pre)
		p->pre->next = p;
	else
		p->par->chi = p;
	if (root->next)
		root->next->pre = root;
	root->pre->next = root;
}

static void		sort_tree(t_tree *root)
{
	t_tree *p;

	p = root->next;
	while (p)
	{
		if (root->data->time_hash < p->data->time_hash)
		{
			if (root->next == p)
				sort_next(root, p);
			else
				sort_not_next(root, p);
			root = p;
		}
		p = p->next;
	}
	if (!root->next)
		return ;
	return (sort_tree(root->next));
}

void			sort_t(t_tree *root)
{
	t_tree *p;

	if (!root)
		return ;
	if (!root->par)
		return (sort_t(root->chi));
	p = root;
	if (!p)
		return ;
	sort_tree(p);
	p = p->par->chi;
	while (p)
	{
		if (p->chi)
			sort_t(p->chi);
		p = p->next;
	}
}
