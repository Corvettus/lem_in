/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 01:33:38 by tlynesse          #+#    #+#             */
/*   Updated: 2019/10/26 19:03:10 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

typedef struct	s_room_data
{
	char	*name;
	int		x;
	int		y;
	int		height;
}				t_room_data;

typedef struct	s_room_list_rough
{
	t_room_data			*data;
	int					start;
	int					end;
	t_room_list_rough	*next;
}				t_room_list_rough;

typedef struct	s_link_list_rough
{
	t_link_list_rough	*prev;
	char				*name1;
	char				*name2;
	t_link_list_rough	*next;
}				t_link_list_rough;

typedef struct	s_room
{
	t_room_data	*data;
	char		type; // i = in, o = out
	t_link_list	*link_list;
}				t_room;

typedef struct	s_link
{
	float		weight;
	t_room_in	*room_in;
}				t_link;

typedef struct	s_room_in
{
	t_room_data	*data;
	t_room_out	*room_out;
}				t_room_in;

typedef struct	s_link_list
{
	t_link		*prev;
	t_room_in	*room;
	t_link		*next;
}				t_link_list;

typedef struct	s_room_out
{
	t_room_data	*data;
	t_link_list	*link_list;
}				t_room_out;

typedef struct	s_ends
{
	t_room_in	*start;
	t_room_in	*end;
}				t_ends;


#endif
