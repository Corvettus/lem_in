/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 01:33:38 by tlynesse          #+#    #+#             */
/*   Updated: 2019/10/30 04:43:48 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

typedef struct	s_room_in			t_room_in;
typedef struct s_link_list			t_link_list;
typedef struct s_room_list_rough	t_room_list_rough;
typedef struct	s_inp_val_data		t_inp_val_data;
typedef struct	s_ends				t_ends;

typedef struct	s_room_data
{
	char	*name;
	int		x;
	int		y;
	int		height;
	int		start_fl;
	int		end_fl;
}				t_room_data;

typedef struct					s_room_list_rough
{
	t_room_data					*data;
	struct s_room_list_rough	*next;
}								t_room_list_rough;

typedef struct	s_link_list_rough
{
	struct s_link_list_rough	*prev;
	char						*name1;
	char						*name2;
	struct s_link_list_rough	*next;
}				t_link_list_rough;

typedef struct	s_link
{
	float	weight;
	t_room	*room;
}				t_link;

typedef struct	s_link_list
{
	t_link_list	*prev;
	t_link		*link;
	t_link_list	*next;
}				t_link_list;

typedef struct	s_room
{
	t_room_data	*data;
	int			type;
	t_link_list	*link_list;
}				t_room;

typedef struct	s_ends
{
	t_room	*start;
	t_room	*end;
}				t_ends;

typedef struct	s_inp_val_data
{
	int					end_pres;
	int					start_pres;
	int					block_switch;
	int					err_pres;
	int					wait_start;
	int					wait_end;
	int					r_count;
	t_list				*input_seq;
	t_room_list_rough	*r_lr;
	t_link_list_rough	*l_lr;
}				t_inp_val_data;


typedef struct	s_way
{
	t_room			*room;
	struct s_way	*next;
}				t_way;

typedef struct	s_path
{
	t_way			*way;
	int				limit;
	int				len;
	struct s_path	*next;
}				t_path;

int main_input(int FD);

#endif
