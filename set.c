/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 01:56:50 by tlynesse          #+#    #+#             */
/*   Updated: 2019/11/04 02:43:40 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	setroom(char *line, t_room **room)
{
	t_room	*new;
	char	*name;
	t_point	coords;

	name = getroomname(line);
	coords = getcoords(line);
	new = roomnew(name, coords, NULL);
	roomadd(room, new);
}

void	setlink(char *line, t_map *map)
{
	t_room	*room1;
	t_room	*room2;

	room1 = getroom1(line, *map);
	room2 = getroom2(line, *map);
	linker(room1, room2);
}

t_room	*init_roomsplit(t_room *room)
{
	t_room	*in;
	t_room	*out;

	in = getroomin(room);
	out = getroomout(room);
	add_link(&in->link, linknew(out, 0));
	add_link(&out->link, linknew(in, INFINITY));
	out->next = in->next;
	in->next = out;
	return (in);
}

int		**init_matrix(int size)
{
	int		**matrix;
	int		i;
	int		j;

	matrix = (int**)malloc(sizeof(int*) * (size + 1));
	i = -1;
	while (++i < size)
	{
		matrix[i] = (int *)malloc(sizeof(int) * (size + 1));
		j = -1;
		while (++j < size)
			matrix[i][j] = 0;
	}
	return (matrix);
}
