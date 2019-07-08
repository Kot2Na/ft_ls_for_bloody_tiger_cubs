/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 16:07:43 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/08 17:30:53 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

void	print_path(char *path)
{
	if (path)
	{
		ft_putstr(path);
		ft_putstr(":\n");
	}
}

void	print_name(char *name)
{
	if (name)
	{
		ft_putstr(name);
		ft_putchar('\t');
	}
}
