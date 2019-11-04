/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 01:36:38 by tlynesse          #+#    #+#             */
/*   Updated: 2019/11/04 01:38:36 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	dijkstra_q_push(int *q, int num)
{
	q[++q[0]] = num;
	q[2]++;
}

int		dijkstra_q_pop(int *q)
{
	q[2]--;
	return (q[q[1]++]);
}

int		*dijkstra_queue(int size)
{
	int *q;

	q = (int*)malloc(sizeof(int) * (size + 3));
	q[0] = 2;
	q[1] = 3;
	q[2] = 0;
	return (q);
}

void	init_dijkstra(t_dijkstra *dijkstra, t_map *map)
{
	int	i;

	(dijkstra)->matrix = map->matrix;
	(dijkstra)->matrix_size = map->rooms_cnt;
	(dijkstra)->vert = (int*)malloc(sizeof(int) * map->rooms_cnt);
	(dijkstra)->dist = (int*)malloc(sizeof(int) * map->rooms_cnt);
	(dijkstra)->poin = (int*)malloc(sizeof(int) * map->rooms_cnt);
	i = 0;
	while (i < map->rooms_cnt)
	{
		dijkstra->vert[i] = 0;
		dijkstra->dist[i] = 0;
		dijkstra->poin[i] = -1;
		i++;
	}
}

void	reset_dijkstra(t_dijkstra *dijkstra, t_map *map)
{
	int	i;

	i = 0;
	while (i < map->rooms_cnt)
	{
		dijkstra->vert[i] = 0;
		dijkstra->dist[i] = 0;
		dijkstra->poin[i] = -1;
		i++;
	}
}
