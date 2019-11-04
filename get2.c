/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 01:58:16 by tlynesse          #+#    #+#             */
/*   Updated: 2019/11/04 02:36:25 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*getroomout(t_room *room)
{
	t_room	*out;
	t_link	*tmp;

	out = roomnew(room->name, room->coords, NULL);
	out->out = 1;
	tmp = room->link;
	while ((tmp))
		tmp = tmp->next;
	rev_link(&out->link);
	return (out);
}

t_room	*getroomin(t_room *room)
{
	t_room	*in;
	t_link	*tmp;

	in = room;
	in->in = 1;
	in->links = 1;
	tmp = in->link;
	while (tmp)
	{
		tmp->weight = INFINITY;
		tmp = tmp->next;
	}
	return (in);
}

int		get_linked(t_dijkstra *dijkstra, int cur, int *linked)
{
	int	i;

	i = 0;
	while (i < dijkstra->matrix_size)
	{
		if (dijkstra->matrix[cur][i] && dijkstra->vert[i] == 0)
		{
			*linked = i;
			return (1);
		}
		i++;
	}
	return (0);
}

int		get_limit(t_map *map)
{
	int lim;

	if (map->rooms_cnt < 2000)
		lim = 12;
	else
	{
		lim = 6;
		if (map->ant_num > 130)
			lim = 7;
		if (map->ant_num > 175)
			lim = 8;
		if (map->ant_num > 200)
			lim = 9;
		if (map->ant_num > 220)
			lim = 10;
		if (map->ant_num > 250)
			lim = 12;
		if (map->ant_num > 325)
			lim = 13;
		if (map->ant_num > 450)
			lim = 14;
	}
	return (lim + 10);
}
