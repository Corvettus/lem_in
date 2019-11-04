/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ways.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 02:15:58 by tlynesse          #+#    #+#             */
/*   Updated: 2019/11/04 02:45:59 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_way	*new_way(t_room *room)
{
	t_way	*way;

	way = NULL;
	if (!(way = (t_way *)malloc(sizeof(t_way))))
		exit_w(-1);
	way->room = room;
	way->next = NULL;
	return (way);
}

void	add_way(t_way **way, t_way *new)
{
	new->next = *way;
	*way = new;
}

int		way_len(t_way *way)
{
	t_way	*ptr;
	int		i;

	i = 0;
	ptr = way;
	while (ptr)
	{
		i++;
		ptr->ant = 0;
		ptr = ptr->next;
	}
	return (i);
}

t_way	*way_prettify(t_way *way)
{
	t_way	*ptr;
	t_way	*cur;

	ptr = way;
	cur = NULL;
	cur = ptr;
	ptr = ptr->next;
	way = way->next;
	free(cur);
	while (ptr && ptr->next)
	{
		if (ptr->room->name == ptr->next->room->name)
		{
			cur = ptr->next;
			ptr->next = ptr->next->next;
			free(cur);
			continue;
		}
		ptr = ptr->next;
	}
	return (way);
}

int		move_up(int dist, t_way *way, t_map *map, int j)
{
	int	i;

	i = 0;
	while (dist--)
		way = way->next;
	(void)map;
	if (way->ant != 0)
	{
		i = 1;
		if (way->next != NULL)
		{
			ans_wr(way->ant, way->next->room, j);
			way->next->ant = way->ant;
		}
		else
			i = 0;
		way->ant = 0;
	}
	return (i);
}
