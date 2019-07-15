/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_field.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 02:02:31 by bomanyte          #+#    #+#             */
/*   Updated: 2019/07/15 04:10:59 by crycherd         ###   ########.fr       */
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

int		is_legal(char *c)
{
	if (*c != 'a' && *c != 'R' && *c != 'l' && *c != 'r' && *c != 't' && *c != 'S')
		return (0);
	return (1);
}

int		validate_flags(char **argv)
{
	int i;
	int j;

	i = 1;
	j = 1;
	while (argv[i])
	{
		if (argv[i][0] == '-' && argv[i][1] == '\0')
			return (1);
		if (!ft_strcmp(argv[i] + j, "LGBT"))
				j += 4;
		while (argv[i][0] == '-' && argv[i][j])
		{
			if (!is_legal(argv[i] + j))
			{
                ft_putstr("ls: illegal option -- ");
                ft_putchar(argv[i][j]);
                ft_putchar('\n');
                return (0);
			}
			j++;
		}
		i++;
		j = 1;
	}
	return (1);
}

void	set_flags(char **argv, t_bit *flags)
{
    int i;
    int j;

    i = 1;
    while (argv[i])
    {
        j = 0;
        while (argv[i][0] == '-' && argv[i][j])
        {
            if (argv[i][j] == 'a')
                flags->a = 1;
			else if (argv[i][j] == 'R')
                flags->re = 1;
			else if (argv[i][j] == 'l')
                flags->l = 1;
			else if (argv[i][j] == 'r')
                flags->r = 1;
			else if (argv[i][j] == 't')
                flags->t = 1;
			else if (argv[i][j] == 'S')
                flags->s = 1;
			else if (!ft_strcmp(argv[i] + 1, "LGBT"))
				flags->lgbt = 1;
            j++;
        }
        i++;
    }
}

void	set_zero(t_bit *flags)
{
    flags->a = 0;
    flags->re = 0;
    flags->l = 0;
    flags->r = 0;
    flags->t = 0;
	flags->s = 0;
	flags->er = 0;
	flags->lgbt = 0;
}
