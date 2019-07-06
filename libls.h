/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 00:52:26 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/05 05:11:46 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBLS_H
# define LIBLS_H

# include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

typedef struct dirent	t_dir;
typedef struct stat		t_stat;

typedef struct			s_data
{
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
void					tree_print(t_tree *tree);
void					tree_destroy(t_tree *tree);

#endif
