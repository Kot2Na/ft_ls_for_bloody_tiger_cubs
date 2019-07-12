/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 01:11:17 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/12 19:46:47 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

/*t_bit *create_flag(int ac, char **av)
{
	t_bit	*bit;

	bit = NULL;
	if ((bit = (t_bit *)malloc(sizeof(t_bit))))
	{
		if (ac > 1 && !(validate_flags(av)))
		{
			free(bit);
			ft_putstr("usage: ls [-Ralrt] [file ...]\n");
			exit(0);
		}
		set_zero(bit);
		set_flags(av, bit);
	}
 	return (bit);
}
*/
/*t_tree	*tree_invalid(int ac, char **av)
{
	t_tree* tree;
	int i;

	i = 1;
	tree = NULL;
	while (av[i] && av[i][0] == '-')
		i++;
	while (av[i])
	{
		if (!dir_valid(av[i]))
		{
			tree = tree_addend(tree, tree_create(av[i]));
			file_set_zero(tree, errno); 
			errno = 0;
		}
		i++;
	}
	return (tree);
} */

int main(int ac, char **av)
{
	t_bit	*flag;
	t_tree	*tree;
	t_tree	*tree_er;

	flag = create_flag(ac, av);
	tree_er = tree_invalid(ac, av, flag);
	tree = tree_born(flag, ac, av);
	if (tree)
    {
        tree = tree_to_start(tree);
        tree_controller(tree, flag);
    }
	if (tree_er)
	{
		tree_er = tree_to_start(tree_er);
		tree_sort(tree_er, ascii_sort);
		tree_er = tree_to_start(tree_er);
	}
	//tree_controller(tree, flag);
	tree_print(tree_er, NULL, flag);
	tree_print(tree, NULL, flag);
	tree_destroy(tree);
	tree_destroy(tree_er);
	free(flag);
	return (0);
}
