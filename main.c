/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 01:11:17 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/06 18:54:05 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

int main(int argc, char **argv)
{
	t_bit *flags;
	flags = (t_bit *)malloc(sizeof(t_bit));
	if (argc > 1 && !(validate_flags(argv)))
	{
		free(flags);
		ft_putstr("usage: ls [-Ralrt] [file ...]\n");
		exit(0);
	}
	set_zero(flags);
	set_flags(argv, flags);
	tree_controller(argv, flags);
	return (0);
}
