/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 01:38:39 by tlynesse          #+#    #+#             */
/*   Updated: 2019/11/04 02:34:44 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	dij_delete(t_dijkstra *dijkstra)
{
	free(dijkstra->vert);
	free(dijkstra->dist);
	free(dijkstra->poin);
}

void	init_search(t_map *map)
{
	int		i;

	i = 0;
	room_split(&(map->room), map->start, map->end);
	init_rooms(map);
	map->rooms_cnt = get_rooms_count(map);
	map->matrix = init_matrix(map->rooms_cnt);
	map->add_matrix = init_matrix(map->rooms_cnt);
	fill_matrix(&(map->matrix), map);
	fill_matrix(&(map->add_matrix), map);
	map->limit = get_limit(map);
	map->path = (t_path**)malloc(sizeof(t_path*) * map->limit);
	map->path_var_num = (int*)malloc(sizeof(int) * map->limit);
	while (i < map->limit)
	{
		map->path[i] = NULL;
		map->path_var_num[i] = 0;
		i++;
	}
	map->var_num = 0;
}

void	dijkstra_level_up(int **q, int **q1, int size)
{
	free(*q);
	*q = *q1;
	*q1 = queue(size);
}

int		dijkstra_add_dist(t_map *map, t_dijkstra *dijkstra)
{
	int		cur;
	int		linked;
	int		i;

	i = 1;
	dijkstra->q1 = dijkstra_queue(dijkstra->matrix_size);
	cur = map->start_id;
	dijkstra->vert[cur] = 1;
	dijkstra_q_push(dijkstra->q, cur);
	while (dijkstra->q[2] != 0)
	{
		cur = dijkstra_q_pop(dijkstra->q);
		while (get_linked(dijkstra, cur, &linked))
			dijkstra_util(linked, cur, i, &dijkstra);
		if (dijkstra->q[2] == 0 && ++i)
			dijkstra_level_up(&(dijkstra->q), &(dijkstra->q1),
			dijkstra->matrix_size);
	}
	dijkstra->poin[map->start_id] = -1;
	free(dijkstra->q);
	free(dijkstra->q1);
	return (0);
}

t_way	*dijkstra(t_map *map, t_dijkstra *dijkstra)
{
	t_way	*way;

	way = NULL;
	dijkstra->q = dijkstra_queue(dijkstra->matrix_size);
	dijkstra_add_dist(map, dijkstra);
	dijkstra->i = map->end_id;
	if (dijkstra->poin[dijkstra->i] == -1)
		return (NULL);
	dijkstra->latest_dist = 0;
	while (dijkstra->i != -1)
	{
		add_way(&way, new_way(find_room_by_num(map, dijkstra->i)));
		dijkstra->i = dijkstra->poin[dijkstra->i];
		dijkstra->latest_dist++;
	}
	return (way);
}
