/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 14:26:37 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/16 03:37:36 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

int		path_and_total(t_tree *tree, t_bit *bit, char *name)
{
	int i;

	i = 0;
	if (one_or_not(tree, bit) && !tree->pre)
	{
		print_path(name);
		i = 1;
	}
	if (tree->par && !tree->pre)
	{
		print_total(tree);
		i = 1;
	}
	return (i);
}

int		for_l(t_tree *tree, char *name, t_bit *bit)
{
	int	i;

	i = 0;
	while (tree)
	{
		if (bit->lgbt)
			print_lgbt(0);
		if (tree_error(tree))
		{
			tree = tree->next;
			i = 1;
			continue ;
		}
		i = path_and_total(tree, bit, name);
		if (bit_a_l(tree, bit))
			i = 1;
		tree = tree->next;
	}
	print_lgbt(-666);
	return (i);
}

int		count_tree(t_tree *tree, t_bit *bit)
{
	int res;

	res = 0;
	if (tree)
	{
		while (tree)
		{
			if (bit->a)
				res++;
			else if (tree->name[0] != '.')
				res++;
			tree = tree->next;
		}
	}
	return (res);
}

int		count_name_tree(t_tree *tree, t_bit *bit)
{
	int	res;
	int nbr;

	res = 0;
	if (tree)
	{
		while (tree)
		{
			nbr = 0; 
			if (bit->a)
				nbr = ft_strlen(tree->name);
			else if (tree->name[0] != '.')
				nbr = ft_strlen(tree->name);
			if (nbr > res)
				res = nbr;
			tree = tree->next;
		}
	}
	return (res);
}

t_tree	*find_tree(t_tree *tree, int n, t_bit *bit)
{
	int i;

	if (tree)
	{
		i = 0;
		while (tree->next && i <= n)
		{
			if (bit->a)
				i++;
			else if (tree->name[0] != '.')
				i++;
			if (i > n)
				break ;
			tree = tree->next;
		}
	}
	return (tree);
}

void	fill_space(char *name, int max)
{
	int i;

	if (name)
	{
		i = ft_strlen(name);
		while (i <= max)
		{
			ft_putchar(' ');
			i++;
		}
	}
}

void	calc_row_col(int nbr, int max, int *col, int *row)
{
	t_win	win;	
	ioctl(0, TIOCGWINSZ, &win);
	*col = win.ws_col / (max + 1);
	if (*col == 0)
		(*col)++;
	*row = nbr / *col;
	if (nbr % *col != 0)
		(*row)++;
	*col = nbr / *row;
	if (nbr % *row != 0)
		(*col)++;
}

int		print_me_please(t_tree *tree, t_bit *bit, int nbr, int max)
{
	t_tree	*print;
	int		col;
	int		row;
	int		i;

	i = 0;
	if (tree && bit && nbr)
	{
		calc_row_col(nbr, max, &col, &row);
		while (i < nbr)
		{
			if (bit->lgbt)
				print_lgbt(0);
			print = find_tree(tree, (i / col + (i % col) * row), bit);
			(print && (i / col + (i % col) * row) < nbr) ? ft_putstr(print->name) : nbr++;
			((i + 1) % col == 0 || i + 1 == nbr) ? ft_putchar('\n') : fill_space(print->name, max);
			i++;
		}
		print_lgbt(-666);
	}
	return (i);
}

int 	prepar_for_print(t_tree *tree, t_bit *bit)
{
	int		max;
	int		nbr;

	if (tree && bit && tree->par)
	{
		nbr = count_tree(tree, bit);
		max = count_name_tree(tree, bit);
		return (print_me_please(tree, bit, nbr, max));
	}
	return (0);
}

int		not_for_l(t_tree *tree, char *name, t_bit *bit)
{
	char	*path;
	t_win	win;
	int		i;

	i = 0;
	path = make_path(name, tree->name);
	if (bit->lgbt)
	{
		print_lgbt(0);
	}
	if (one_or_not(tree, bit) && !tree->pre)
	{
		i = 1;
		print_path(name);
	}
	free(path);
	i += prepar_for_print(tree, bit);
	return (i);
}

int print_new_line(int i)
{
	if (i)
	{
		ft_putchar('\n');
		i = 0;
	}
	return (i);
}

int		tree_print(t_tree *tree, char *name, t_bit *bit)
{
	int		i;

	if (tree)
	{
		i = bit->l ? for_l(tree, name, bit) : not_for_l(tree, name, bit);
		while (tree)
		{
			if (tree->data && tree->data->error == 13)
			{
				i = print_new_line(i);
				if (bit->lgbt)
					print_lgbt(0);
				i = tree_error_13(tree, name);
			}
			if (tree->chi)
			{
				i = print_new_line(i);
				i = print_chi(tree, name, bit);
			}
			tree = tree->next;
		}
	}
	return (i);
}
