/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 01:11:17 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/09 16:24:44 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

t_bit *create_flag(int ac, char **av)
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

int main(int ac, char **av)
{
	t_bit	*flag;
	t_tree	*tree;
	int test;

	//flag = create_flag(ac, av);
	flag = (t_bit*)malloc(sizeof(t_bit));
	set_zero(flag);
	flag->R = 1;
	flag->l = 1;
<<<<<<< HEAD
=======
	flag->a = 0;
>>>>>>> 70468e5bcad3122949e4d1b13fba90c702da6495
	tree = tree_born(flag, ac, av);

	tree = tree_to_start(tree);
	tree_print(tree, NULL, flag);
	tree_destroy(tree);
	free(flag);
	return (0);
}
