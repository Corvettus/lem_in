/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 20:25:26 by aromny-w          #+#    #+#             */
/*   Updated: 2019/11/04 00:08:56 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

typedef struct s_room	t_room;

typedef struct	s_way
{
	t_room			*room;
	int				ant;
	int				suurbale;
	struct s_way	*next;
}				t_way;

typedef struct	s_path
{
	int				dist;
	t_way			*way;
	struct s_path	*next;
}				t_path;

typedef struct	s_link
{
	t_room			*room;
	float			weight;
	int				visited;
	int				excluded;
	struct s_link	*next;
}				t_link;

typedef struct	s_point
{
	int	x;
	int	y;
}				t_point;

struct			s_room
{
	char			*name;
	t_point			coords;
	float			dist;
	int				num;
	int				in;
	int				out;
	int				links;
	t_link			*link;
	struct s_room	*next;
};

typedef struct	s_map
{
	int				ant_num;
	t_list			*buf;
	t_room			*room;
	t_room			*start;
	t_room			*end;
	int				**matrix;
	int				**add_matrix;
	int				limit;
	t_path			**path;
	int				*path_var_num;
	int				var_num;
	int				rooms_cnt;
	int				start_id;
	int				end_id;
	
}				t_map;

typedef struct	s_dijkstra
{
	int			*q;
	int			*q1;
	int			**matrix;
	int			matrix_size;
	int			*vert;
	int			*dist;
	int			*poin;
	int			min;
	int			i;
	int			latest_dist;
}				t_dijkstra;

#endif
