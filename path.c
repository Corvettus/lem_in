/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 02:13:01 by tlynesse          #+#    #+#             */
/*   Updated: 2019/11/04 02:27:18 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	path_push(t_path ***path, t_way *way, int num, t_map *map)
{
	t_path *ptr;

	map->var_num = num;
	map->path_var_num[num] += 1;
	if (!(*path)[num])
	{
		(*path)[num] = init_path();
		(*path)[num]->way = way;
		(*path)[num]->next = NULL;
		(*path)[num]->dist = 0;
		(*path)[num]->dist = way_len(way);
		return ;
	}
	else
	{
		ptr = (*path)[num];
		while (ptr && ptr->next)
			ptr = ptr->next;
		ptr->next = init_path();
		ptr->next->way = way;
		ptr->next->dist = way_len(way);
	}
}

void	search_path(t_map *map)
{
	t_dijkstra	dijkstrao;
	t_way		*tmp;
	int			lim;

	lim = 0;
	init_search(map);
	init_dijkstra(&dijkstrao, map);
	while (lim < map->limit
		&& (tmp = dijkstra(map, &dijkstrao)))
	{
		if (check_overlap(tmp, &map, &dijkstrao))
		{
			++lim;
			reset_dijkstra(&dijkstrao, map);
			continue;
		}
		mat_search(&map->matrix, tmp);
		path_push(&map->path, way_prettify(tmp), lim, map);
		reset_dijkstra(&dijkstrao, map);
	}
	dij_delete(&dijkstrao);
	mat_delete(map->matrix, map->rooms_cnt);
}

void	path_delete(t_path *path)
{
	t_path	*ptr;
	t_path	*next;

	ptr = path;
	while (ptr)
	{
		next = ptr->next;
		way_delete(ptr->way);
		ptr->way = NULL;
		free(ptr);
		ptr = NULL;
		ptr = next;
	}
	path = NULL;
}

int		path_up(t_path *path, t_map *map)
{
	int dist;
	int i;

	i = 0;
	while (path)
	{
		dist = path->dist;
		while (dist--)
			if (move_up(dist, path->way, map, i))
				i = 1;
		path = path->next;
	}
	return (i);
}

void	map_deletepath(t_map *map, t_path *path)
{
	map_delete(map);
	path_delete(path);
	exit(-1);
}
