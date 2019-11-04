/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 02:11:53 by tlynesse          #+#    #+#             */
/*   Updated: 2019/11/04 02:25:21 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	mat_delete(int **matrix, int size)
{
	int		i;

	i = 0;
	while (i < size)
		free(matrix[i++]);
	free(matrix);
}

void	fill_matrix(int ***matrix, t_map *map)
{
	t_link *ptr;
	t_room *room_ptr;

	room_ptr = map->room;
	while (room_ptr)
	{
		ptr = room_ptr->link;
		while (ptr)
		{
			(*matrix)[ptr->room->num][room_ptr->num] = 1;
			ptr = ptr->next;
		}
		room_ptr = room_ptr->next;
	}
}

int		mat_search(int ***matrix, t_way *way)
{
	t_way	*ptr;
	t_way	*next;
	int		i;

	i = 0;
	ptr = way;
	next = ptr->next;
	while (next)
	{
		(*matrix)[ptr->room->num][next->room->num] =
		((*matrix)[ptr->room->num][next->room->num]) ? 0 : 1;
		(*matrix)[next->room->num][ptr->room->num] =
		((*matrix)[next->room->num][ptr->room->num]) ? 0 : 1;
		ptr = ptr->next;
		next = next->next;
		i++;
	}
	return (i);
}

void	mat_copy(int ***matrix, int **add_matrix, int size)
{
	int		i;
	int		j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			(*matrix)[i][j] = add_matrix[i][j];
	}
}

int		check_overlap(t_way *way, t_map **map, t_dijkstra *dijkstra)
{
	t_way	*ptr;
	t_way	*next;

	ptr = way;
	next = ptr->next;
	while (next)
	{
		if ((ptr->room->name == next->room->name && ptr->room->out &&
			next->room->in) || (ptr->room->name != next->room->name &&
			ptr->room->in && next->room->out))
		{
			(*map)->add_matrix[ptr->room->num][next->room->num] = 0;
			(*map)->add_matrix[next->room->num][ptr->room->num] = 0;
			{
				mat_copy(&dijkstra->matrix, (*map)->add_matrix,
				(*map)->rooms_cnt);
				return (1);
			}
		}
		ptr = ptr->next;
		next = next->next;
	}
	return (0);
}
