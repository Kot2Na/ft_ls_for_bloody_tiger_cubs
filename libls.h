/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 00:52:26 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/06 19:45:05 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBLS_H
# define LIBLS_H

# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>

typedef struct dirent	t_dir;
typedef struct stat		t_stat;

typedef struct			s_bit
{
	unsigned int		a:1;
	unsigned int		R:1;
	unsigned int		l:1;
	unsigned int		t:1;
	unsigned int		r:1;
} 						t_bit;

typedef struct			s_data
{
	int					error;
	char				*rights;
	int					link;
	char				*group;
	long long			size;
	long long			time;
}						t_data;

typedef struct			s_tree
{
	char				*name;
	t_data				*data;
	struct s_tree		*par;
	struct s_tree		*chi;
	struct s_tree		*next;
	struct s_tree		*pre;
}						t_tree;

t_tree					*tree_create(char *name);
t_tree					*tree_addend(t_tree *start, t_tree *new);
t_tree					*tree_addend_chil(t_tree *root, t_tree *leaf);
t_tree					*tree_to_start(t_tree *tree);
t_tree					*tree_open(char *name);
t_tree					*tree_born(t_bit *bit, int ac, char **av);
void					tree_print(t_tree *tree);
void					tree_destroy(t_tree *tree);
int						is_legal(char c);
int						validate_flags(char **argv);
void					set_flags(char **argv, t_bit *flags);
void					set_zero(t_bit *flags);

#endif