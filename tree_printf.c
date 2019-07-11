/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 16:07:43 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/11 21:56:06 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

void	print_par_l(t_data *data)
{
	ft_putstr(data->rights);
	ft_putchar(' ');
	ft_putnbr((int)data->hd_link);
	ft_putchar(' ');
	ft_putstr(data->user);
	ft_putchar(' ');
	ft_putstr(data->group);
	ft_putchar(' ');
	ft_putnbr((int)data->size);
	ft_putchar('\t');
	ft_putstr(data->time);
	ft_putchar(' ');
}

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

void	print_str_l(t_tree *tree)
{
	if (tree)
	{
		print_par_l(tree->data);
		ft_putstr(tree->name);
		ft_putchar('\n');
	}
}

void	print_total(t_tree *tree)
{
	if (tree && tree->data->blocks != 0)
	{
		ft_putstr("total ");
		ft_putnbr(tree->par->data->blocks);
		ft_putchar('\n');
	}
}
