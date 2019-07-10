/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 00:52:26 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/10 19:10:45 by crycherd         ###   ########.fr       */
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
# include <limits.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>

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
	unsigned short		type;
	long long			blocks;
	char				*rights;
	unsigned short		hd_link;
	char				*soft_ln;
	char				*user;
	char				*group;
	long long			size;
	char				*time;
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
t_tree					*tree_open(t_bit *bit, t_tree *root, char *name);
t_tree					*tree_born(t_bit *bit, int ac, char **av);
char					*make_path(char *from, char *to);
int						is_legal(char c);
int						one_or_not(t_tree *tree);
int						validate_flags(char **argv);
int						ascii_sort(t_tree *first, t_tree *second);
int						size_sort(t_tree *first, t_tree *second);
void					tree_print(t_tree *tree, char *name, t_bit *bit);
void					tree_destroy(t_tree *tree);
void					set_flags(char **argv, t_bit *flags);
void					print_str_l(t_tree *tree);
void					set_zero(t_bit *flags);
void					print_path(char *path);
void					print_name(char *name);
void					fill_data(t_tree *node, char *name);
void					tree_swap(t_tree *tree1, t_tree *tree2);
void					tree_sort(t_tree *tree, int (*sort)(t_tree *, t_tree *));
void					sort_my_child(t_tree *tree, int (*sort)(t_tree *, t_tree *));
long long				get_total(t_tree *root);
long long				get_totalR(t_tree *root);

#endif
