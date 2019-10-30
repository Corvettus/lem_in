/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 17:17:56 by tlynesse          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/10/30 06:03:57 by wclayton         ###   ########.fr       */
=======
/*   Updated: 2019/10/30 02:49:42 by tlynesse         ###   ########.fr       */
>>>>>>> 0752952a7deb032169c51ad59f99c8481e6a0dc8
/*                                                                            */
/* ************************************************************************** */

/* #include "lem_in.h"

int		ft_bfs_heights_count(t_room *start)
{
	start->data->height = 0;

	
}

int		q_push(t_room_q **head, t_room *room, t_room *wherefrom)
{
	t_room_q *tmp;

	if ((tmp = (t_room_q*)malloc(sizeof(t_room_q))))
	{
		tmp->next = *head;
		tmp->room = room;
		tmp->wherefrom = wherefrom;
		*head = tmp;
		return (1);
	}
	else
		return (0);
	
	
}

t_room_q	*q_pop(t_room_q **head)
{
	t_room_q	*out;
	if (*head)
	{
		out = *head;
		*head = (*head)->next;
		return (out);
	}
	else
		return (0);	
}


t_path	*dijkstra(t_room *start, t_room *end)
{
	t_path	*res;
	t_way	*way;
	t_way	*to_visit;
	t_room_q	*queue;
	t_room		*now;
	t_room_q	*temp;
	t_link_list *link_temp;

	way = (t_way*)malloc(sizeof(t_way));
	queue = (t_room_q*)malloc(sizeof(t_room_q));
	queue->next = 0;
	queue->room = 0;
	queue->next = 0;
	way->room = end;
	way->next = 0;
	way->prev = 0;
	end->data->height = 0;

	res = 0;

	q_push(&queue, end, 0);
	while(queue)
	{
		temp = q_pop(&queue);
		if (temp->room != end)
			temp->room->data->height = temp->wherefrom->data->height + 1;
		link_temp = temp->room->link_list;
		while (link_temp)
		{
			if (link_temp->link->room->data->height == -1)
				q_push(&queue, link_temp->link->room, temp->room);
			link_temp = link_temp->next;
		}
	}

	//rasstavili vesa ot konca. 
	//teper idem ot nachala i dobavlyaem v put komnaty s naimenshim vesom
	//vse napisano supershakalno i podlezhit ispravleniyu

	//sry ne mogu dopisat minus glaza


}

void	lem_in(t_room *start, t_room *end)
{
	
}
 */