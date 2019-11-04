/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms_n_links.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 01:42:15 by tlynesse          #+#    #+#             */
/*   Updated: 2019/11/04 02:27:03 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*roomnew(char *name, t_point coords, t_link *link)
{
	t_room	*room;

	if (!(room = (t_room *)malloc(sizeof(t_room))))
		exit_w(-1);
	room->name = name;
	room->coords = coords;
	room->dist = INFINITY;
	room->num = 0;
	room->in = 0;
	room->out = 0;
	room->links = 0;
	room->link = link;
	room->next = NULL;
	return (room);
}

void	roomadd(t_room **room, t_room *new)
{
	new->next = *room;
	*room = new;
}

void	rev_link(t_link **link)
{
	t_link	*prev;
	t_link	*curr;
	t_link	*next;

	prev = NULL;
	curr = *link;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*link = prev;
}

t_link	*linknew(t_room *room, float weight)
{
	t_link *link;

	if (!(link = (t_link *)malloc(sizeof(t_link))))
		exit_w(-1);
	link->room = room;
	link->weight = weight;
	link->next = NULL;
	return (link);
}

void	add_link(t_link **link, t_link *new)
{
	new->next = *link;
	*link = new;
}
