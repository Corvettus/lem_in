/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 02:14:36 by tlynesse          #+#    #+#             */
/*   Updated: 2019/11/04 02:44:28 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	way_delete(t_way *way)
{
	t_way	*ptr;
	t_way	*next;

	ptr = way;
	while (ptr)
	{
		next = ptr->next;
		free(ptr);
		ptr = NULL;
		ptr = next;
	}
}

void	del(void *elem, size_t size)
{
	size = 0;
	free(elem);
}

void	rooml_delete(t_link **link)
{
	t_link	*tmp;
	t_link	*next;

	tmp = *link;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void	map_delete(t_map *map)
{
	t_room	*tmp;
	t_room	*next;

	tmp = map->room;
	while (tmp)
	{
		next = tmp->next;
		rooml_delete(&tmp->link);
		if (!tmp->in)
			free(tmp->name);
		free(tmp);
		tmp = next;
	}
	ft_lstdel(&map->buf, del);
	ft_memset(map, 0, sizeof(t_map));
	map = NULL;
}
