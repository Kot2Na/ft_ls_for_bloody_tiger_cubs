/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_controller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:52:59 by bomanyte          #+#    #+#             */
/*   Updated: 2019/07/06 19:47:50 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

check_errno

get_data

sort_ascii

t_tree *tree_traverse(char **argv, t_bit *flags)
{

}

void	tree_controller(char **argv, t_bit *flags)
{
	t_tree *root;

	root = tree_traverse(argv, flags);
	if (flags->l)
		format_l(root, flags);
	else
		format(root, flags);
	if (flags->t)
		sort_t(root);
	if (flags->r)
		sort_r(root);
	print_tree(root);
}
