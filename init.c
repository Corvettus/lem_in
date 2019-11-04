/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 02:04:19 by tlynesse          #+#    #+#             */
/*   Updated: 2019/11/04 02:36:10 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	initmap(t_map *map)
{
	map->ant_num = -1;
	map->buf = NULL;
	map->room = NULL;
	map->start = NULL;
	map->end = NULL;
}

t_path	*init_path(void)
{
	t_path *path;

	path = (t_path*)malloc(sizeof(t_path));
	path->way = NULL;
	path->next = NULL;
	path->dist = -1;
	return (path);
}

t_way	*init_way(t_room *room)
{
	t_way	*way;

	way = (t_way*)malloc(sizeof(t_way));
	way->room = room;
	way->ant = 0;
	way->next = NULL;
	return (way);
}

void	init_rooms(t_map *map)
{
	t_room	*ptr;
	int		i;

	i = 0;
	ptr = map->room;
	while (ptr)
	{
		ptr->dist = 0;
		if (ptr == map->start)
			map->start_id = i;
		if (ptr == map->end)
			map->end_id = i;
		ptr->num = i;
		i++;
		ptr = ptr->next;
	}
}

void	room_split(t_room **room, t_room *start, t_room *end)
{
	t_room	*tmp;

	tmp = *room;
	while (tmp)
	{
		if (tmp != start && tmp != end)
		{
			tmp = init_roomsplit(tmp);
			tmp = tmp->next->next;
		}
		else
			tmp = tmp->next;
	}
	link_compl(room, start, end);
}
