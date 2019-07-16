/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 00:52:26 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/16 04:26:03 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBLS_H
# define LIBLS_H

# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>

# define LINK /bit.ly/2Y7fGri

typedef struct dirent	t_dir;
typedef struct stat		t_stat;
typedef	struct winsize	t_win;

typedef struct			s_bit
{
	unsigned int		a:1;
	unsigned int		re:1;
	unsigned int		l:1;
	unsigned int		t:1;
	unsigned int		r:1;
	unsigned int		s:1;
	unsigned int		er:1;
	unsigned int		lgbt:1;
}						t_bit;

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
	long int			time_hash;
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

void					sort_not_next(t_tree *root, t_tree *p);
void					sort_next(t_tree *root, t_tree *p);
void					sort_t_ascii(t_tree *tr, int (*s)(t_tree *, t_tree *));
t_tree					*tree_create(char *name);
t_tree					*tree_addend(t_tree *start, t_tree *new);
t_tree					*tree_addend_chil(t_tree *root, t_tree *leaf);
t_tree					*tree_to_start(t_tree *tree);
t_tree					*tree_open(t_bit *bit, t_tree *root, char *name);
t_tree					*tree_born(t_bit *bit, int ac, char **av);
t_tree					*to_start(t_tree *tree);
t_tree					*tree_invalid(int ac, char **av, t_bit *bit);
t_bit					*create_flag(int ac, char **av);
char					*make_path(char *from, char *to);
char					*time_to_str(char *buf);
int						tree_print(t_tree *tree, char *name, t_bit *bit);
void					tree_controller(t_tree *root, t_bit *flag);
void					sort_t(t_tree *root);
void					tree_destroy(t_tree *tree);
void					play_song(void);
void					set_flags(char **argv, t_bit *flags);
void					print_total(t_tree *tree);
int						print_chi(t_tree *tree, char *name, t_bit *bit);
void					print_str_l(t_tree *tree, t_bit *bit);
void					set_zero(t_bit *flags);
void					print_path(char *path);
void					print_name(char *name);
void					fill_data(t_tree *node, char *name);
void					tree_swap(t_tree *tree1, t_tree *tree2);
void					tree_sort(t_tree *tr, int (*s)(t_tree *, t_tree *));
void					sort_my_child(t_tree *tr, int (*s)(t_tree *, t_tree *));
void					file_set_zero(t_tree *node, int err);
void					print_lgbt(int f);
void					kill_song(void);
int						path_and_total(t_tree *tree, t_bit *bit, char *name);
void					calc_row_col(int nbr, int max, int *col, int *row);
int						print_new_line(int i);
int						count_tree(t_tree *tree, t_bit *bit);
int						count_name_tree(t_tree *tree, t_bit *bit);
t_tree					*find_tree(t_tree *tree, int n, t_bit *bit);
void					fill_space(char *name, int max);
int						print_me_please(t_tree *tr, t_bit *bt, int nb, int mx);
int						prepar_for_print(t_tree *tree, t_bit *bit);
int						tree_error_13(t_tree *tree, char *name);
int						bit_a_l(t_tree *tree, t_bit *bit);
int						tree_error(t_tree *tree);
int						bit_a(t_tree *tree, t_bit *bit);
int						is_legal(char *c);
int						one_or_not(t_tree *tree, t_bit *bit);
int						validate_flags(char **argv);
int						ascii_sort(t_tree *first, t_tree *second);
int						dir_valid(char *name);
int						size_sort(t_tree *first, t_tree *second);
long long				get_total(t_tree *root);
long long				get_totalr(t_tree *root);

#endif
