/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 00:52:26 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/05 01:09:35 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBLS_H
# define LIBLS_H

#include "libft.h"

typedef struct		s_data
{
	char			*rights;
	int				link;
	char			*group;
	long long		size;
	long long		time;
}					t_data;

typedef struct		s_tree
{
	char			*name;
	t_data			*data;
	struct s_tree	*par;
	struct s_tree	*chi;
	struct s_tree	*nex;
	struct s_tree	*pre;
}					t_tree;

#endif
