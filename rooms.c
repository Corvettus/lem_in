/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 02:17:42 by tlynesse          #+#    #+#             */
/*   Updated: 2019/11/04 02:22:33 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_roomname(t_room *room, char *name)
{
	while (room && ft_strcmp(name, room->name))
		room = room->next;
	if (room)
		return (1);
	return (0);
}

t_room	*find_room_by_num(t_map *map, int num)
{
	t_room		*ptr;

	if (map->start->num == num)
		return (map->start);
	if (map->end->num == num)
		return (map->end);
	ptr = map->room;
	while (ptr)
	{
		if (ptr->num == num)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

void	rev_room(t_room **room)
{
	t_room	*prev;
	t_room	*curr;
	t_room	*next;

	prev = NULL;
	curr = *room;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*room = prev;
}
