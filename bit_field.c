/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_field.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 02:02:31 by bomanyte          #+#    #+#             */
/*   Updated: 2019/07/05 03:10:00 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef struct s_bit
{
	unsigned int a:1;
	unsigned int R:1;
	unsigned int l:1;
	unsigned int t:1;
	unsigned int r:1;
} t_bit;

void	ft_putchar(char c);
void	ft_putstr(char *str);

int	is_legal(char c)
{
	if (c != 'a' && c != 'R' && c != 'l' && c != 'r' && c != 't')
		return (0);
	return (1);
}

int	validate_flags(char **argv)
{
	int i;
	int j;
	int flag;

	i = 1;
	j = 0;
	while (argv[i])
	{
		flag = 0;
		while (argv[i][j])
		{
			if (!flag && argv[i][j] && argv[i][j] != '-')
			{
                ft_putstr("ls: ");
                ft_putstr(argv[i]);
                ft_putstr(": No such file or directory\n");
                return (0);
			}
			else if (flag && !is_legal(argv[i][j]))
			{
                ft_putstr("ls: illegal option -- ");
                ft_putchar(argv[i][j]);
                ft_putchar('\n');
                return (0);
			}
			flag = 1;
			j++;
		}
		i++;
		j = 0;
	}
	return (1);
}

void    set_flags(char **argv, t_bit *flags)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (argv[i])
    {
        while (argv[i][j])
        {
            if (argv[i][j] == 'a')
                flags->a = 1;
            else if (argv[i][j] == 'R')
                flags->R = 1;
            else if (argv[i][j] == 'l')
                flags->l = 1;
            else if (argv[i][j] == 'r')
                flags->r = 1;
            else if (argv[i][j] == 't')
                flags->t = 1;
            j++;
        }
        i++;
        j = 0;
    }
}

void    set_zero(t_bit *flags)
{
    flags->a = 0;
    flags->R = 0;
    flags->l = 0;
    flags->r = 0;
    flags->t = 0;
}

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
	return (0);
}
