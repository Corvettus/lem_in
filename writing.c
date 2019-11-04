/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 02:06:28 by tlynesse          #+#    #+#             */
/*   Updated: 2019/11/04 02:35:14 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ans_wr(int i, t_room *room, char fl)
{
	char	*ant;

	ant = ft_itoa(i);
	if (fl)
		write(1, " ", 1);
	write(1, "L", 1);
	ft_putstr(ant);
	write(1, "-", 1);
	ft_putstr(room->name);
	free(ant);
}

void	all_ants_one_way(t_map *map, t_path *path)
{
	int ant;

	ant = 1;
	ans_wr(ant, path->way->room, 0);
	while (++ant <= map->ant_num)
	{
		ans_wr(ant, path->way->room, 1);
	}
	write(1, "\n", 1);
}

void	lets_go(t_map *map, t_path *path, int ants, t_path *begin)
{
	int		ant;
	int		sw;

	ant = 0;
	while (ant < ants)
	{
		sw = path_up(path, map);
		path = begin;
		path->way->ant = ++ant;
		ans_wr(ant, path->way->room, sw);
		while (path->next && path->next->dist - begin->dist < ants - ant)
		{
			path = path->next;
			path->way->ant = ++ant;
			ans_wr(ant, path->way->room, 1);
		}
		write(1, "\n", 1);
	}
	while (ant)
	{
		ant = path_up(begin, map);
		if (ant)
			write(1, "\n", 1);
	}
}

void	writeinput(t_list *buf)
{
	while (buf)
	{
		ft_putendl(buf->content);
		buf = buf->next;
	}
	ft_putchar('\n');
}

void	dijkstra_util(int linked, int cur, int i, t_dijkstra **dijkstra)
{
	(*dijkstra)->vert[linked] = 1;
	(*dijkstra)->dist[linked] = i;
	(*dijkstra)->poin[linked] = cur;
	dijkstra_q_push((*dijkstra)->q1, linked);
}
