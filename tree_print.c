/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 14:26:37 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/15 05:41:27 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

int		for_l(t_tree *tree, char *name, t_bit *bit)
{
	char	*path;
	int		i;

	i = 0;
	while (tree)
	{
		if (bit->lgbt)
			print_lgbt(0);
		if (tree_error(tree))
		{
			tree = tree->next;
			continue ;
		}
		path = make_path(name, tree->name);
		if (one_or_not(tree, bit) && !tree->pre)
		{
			print_path(name);
			i++;
		}
		if (tree->par && !tree->pre)
			print_total(tree);
		if (bit_a_l(tree, bit))
			i++;
		tree = tree->next;
		free(path);
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

int		print_me_please(t_tree *tree, t_bit *bit, int nbr, int max)
{
	t_tree	*print;
	t_win	win;
	int		col;
	int		row;
	int		i;

	if (tree && bit && nbr)
	{
		i = 0;
		ioctl(0, TIOCGWINSZ, &win);
		col = win.ws_col / (max + 1);
		if (col == 0)
			col++;
		row = nbr / col;
		if (nbr % col != 0)
			row++;
		col = nbr / row;
		if (nbr % row != 0)
			col++;
		while (i < nbr)
		{
			if (bit->lgbt)
				print_lgbt(0);
			print = find_tree(tree, (i / col + (i % col) * row), bit);
			if (print && (i / col + (i % col) * row) < nbr)
				ft_putstr(print->name);
			else
				nbr++;
			if ((i + 1) % col == 0 || i + 1 == nbr)
				ft_putchar('\n');
			else
				fill_space(print->name, max);
			i++;
		}
		print_lgbt(-666);
		return (1);
	}
	return (0);
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
//eto vrode tozhe
t_tree	*tree_to_last(t_tree *tree)
{
	if (tree)
	{
		while (tree->next)
			tree = tree->next;
		while (tree->pre && !tree->chi)
			tree = tree->pre;
		if (tree->chi)
			tree = tree_to_last(tree->chi);
	}
	return (tree);
}
//sosna ne prigodilas'
int		sosna_or_ne(t_tree *tree)
{
	t_tree *sosna;

	if (tree)
	{
		sosna = tree;
		tree = tree_to_start(tree);
		tree = tree_to_last(tree);
		if ((sosna - tree) == 0)
			return (1);
	}
	return (0);
}

void	print_lgbt(int f)
{
	static int i;

	if (f == -666)
	{
		ft_putstr("\033[0m");
		return ;
	}
	i = f ? 0 : ++i;
	if (i % 6 == 0)
		ft_putstr("\x1B[31m");
	if (i % 6 == 1)
		ft_putstr("\x1B[91m");
	if (i % 6 == 2)
		ft_putstr("\x1B[93m");
	if (i % 6 == 3)
		ft_putstr("\x1B[92m");
	if (i % 6 == 4)
		ft_putstr("\x1B[34m");
	if (i % 6 == 5)
		ft_putstr("\x1B[35m");
}

int		not_for_l(t_tree *tree, char *name, t_bit *bit)
{
	char	*path;
	t_win	win;

	path = make_path(name, tree->name);
	if (bit->lgbt)
		print_lgbt(0);
	if (one_or_not(tree, bit) && !tree->pre)
		print_path(name);
	free(path);
	return (prepar_for_print(tree, bit));
}

int		tree_print(t_tree *tree, char *name, t_bit *bit)
{
	int		i;
	t_tree *sosna;

	if (tree)
	{
		i = bit->l ? for_l(tree, name, bit) : not_for_l(tree, name, bit);
		while (tree)
		{
			if (tree->data && tree->data->error == 13)
			{
				if (i > 0)
				{
					ft_putchar('\n');
					i = 0;
				}
				if (bit->lgbt)
					print_lgbt(0);
				i = tree_error_13(tree, name);
			}
			if (tree->chi)
			{
				if (i > 0)
				{
					ft_putchar('\n');
					i = 0;
				}
				i = print_chi(tree, name, bit);
			}
			tree = tree->next;
		}
	}
	return (i);
}
