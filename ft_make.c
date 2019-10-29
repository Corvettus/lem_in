/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 04:51:52 by tlynesse          #+#    #+#             */
/*   Updated: 2019/10/30 00:36:58 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room_list_rough	*ft_seach_ends(t_room_list_rough *r_room, int mode)
{
	if (mode == 's')
	{
		while (r_room->data->start_fl == 1)
			r_room = r_room->next;
		return (r_room);
	}
	else if (mode == 'e')
	{
		while (r_room->data->end_fl == 1)
			r_room = r_room->next;
		return (r_room);
	}
	else
		return (NULL);
}

t_room_list_rough	*ft_r_seach_name(t_room_list_rough *r_room, char *name)
{
	while (ft_strcmp((const char*)r_room->data->name, (const char*)name) != 0)
		r_room = r_room->next;
	if (ft_strcmp((const char*)r_room->data->name, (const char*)name) == 0)
		return (r_room);
	else
		return (NULL);
}

t_room_data	*ft_room_data_cpy(t_room_data *room_data)
{
	t_room_data	*room_data_fresh;

	room_data_fresh = (t_room_data*)malloc(sizeof(t_room_data));
	room_data_fresh->name = ft_strdup(room_data->name);
	room_data_fresh->x = room_data->x;
	room_data_fresh->y = room_data->y;
	room_data_fresh->height = room_data->height;
	room_data_fresh->start_fl = room_data->start_fl;
	room_data_fresh->end_fl = room_data->end_fl;
	return (room_data_fresh);
}

t_link_list	*ft_cast_link(t_room *room)
{
	t_link_list	*res;

	if ((res = (t_link_list*)malloc(sizeof(t_link_list))) == NULL)
		return (NULL);
	res->prev = NULL;
	res->link->room = room;
	res->next = NULL;
	res->link->weight = room->type;
	return (res);
}

t_link_list	*ft_add_link(t_room *room_from, t_room *room_to)
{
	t_link_list	*tmp;
	t_room		*room_in_to;

	tmp = room_from->link_list;
	if (tmp == NULL)
		room_from->link_list = ft_cast_link(room_in_to);
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = ft_cast_link(room_in_to);
	}
	return (tmp);
}

t_link_list_rough	*ft_r_link_list_del_elem(t_link_list_rough *r_link,
t_link_list_rough *to_del)
{
	if (to_del == NULL)
		return (r_link);
	if (to_del->prev != NULL)
		to_del->prev->next = to_del->next;
	if (to_del->next != NULL)
		to_del->next->prev = to_del->prev;
	if (to_del != NULL)
	{
		if (to_del->name1 != NULL)
			free(to_del->name1);
		if (to_del->name2 != NULL)
			free(to_del->name2);
		free(to_del);
	}
	return (r_link);
}

void	ft_linking_rooms(t_room *room_1, t_room *room_2)
{
	ft_add_link((room_1->link_list)->link->room, room_2);
	ft_add_link(room_2, room_1);
}

t_room	*ft_create_node(t_room_list_rough *r_room, t_room_data *room_data)
{
	t_room	*room;

	room = (t_room*)malloc(sizeof(t_room));
	room->data = room_data;
	room->link_list = NULL;
	return (room);
}

t_room	*ft_create_room(t_room_list_rough *r_room)
{
	t_room		*room_in;
	t_room		*room_out;
	t_room_data	*room_data;

	room_data = ft_room_data_cpy(r_room->data);
	room_in = (t_room*)malloc(sizeof(t_room));
	room_in->data = room_data;
	room_in->link_list = NULL;
	room_in->type = 'i';
	room_out = (t_room*)malloc(sizeof(t_room));
	room_out->data = room_data;
	room_out->link_list = NULL;
	room_out->type = 'o';
	ft_add_link(room_in, room_out);
	return (room_in);
}

int	ft_make_map(t_room_list_rough *r_room, t_link_list_rough **r_link,
t_room_list_rough *r_start, t_room **start)
{
	t_link_list_rough	*tmp;
	t_room				*room_in;
	t_link_list_rough	*r_next;
	char				*tmp_name;

	if ((tmp = r_link) == NULL)
		return (0);
	while (ft_strcmp((const char*)tmp->name1,
			(const char*)r_start->data->name) != 0 &&
			ft_strcmp((const char*)tmp->name2,
			(const char*)r_start->data->name) != 0 && tmp != NULL)
		tmp = tmp->next;
	if (tmp == NULL)
		return (0);
	if (ft_strcmp((const char*)tmp->name1,
			(const char*)r_start->data->name) == 0)
		tmp_name = tmp->name1;
	else if (ft_strcmp((const char*)tmp->name2,
			(const char*)r_start->data->name) == 0)
		tmp_name = tmp->name2;
	else
		tmp_name = NULL;
	if (*start == NULL)
		*start = ft_create_room(r_start);
	if (room_in == NULL)
		room_in = ft_create_room(ft_r_seach_name(r_room, tmp_name));
	ft_linking_rooms(start, room_in);
	*r_link = ft_r_link_list_del_elem(*r_link, tmp);
	if (ft_make_map(r_room, r_link, r_start, start) == -1)
	{
		// free all
		return (-1);
	}
	r_next = r_link;
	while (ft_strcmp((const char*)r_next->name1,
			(const char*)room_in->data->name) != 0 &&
			ft_strcmp((const char*)r_next->name2,
			(const char*)room_in->data->name) != 0 && r_next != NULL)
		r_next = r_next->next;
	if (ft_make_map(r_room, r_link, r_next, room_in))
	{
		// free all
		return (-1);
	}
	return (1);
}

t_room	*ft_build(t_room_list_rough *r_room, t_link_list_rough *r_link)
{
	t_room_list_rough	*r_start;
	t_room_list_rough	*r_end;
	t_room				*start;

	r_start = ft_seach_ends(r_room, 's');
	r_end = ft_seach_ends(r_room, 'e');
	if (ft_make_map(r_room, &r_link, r_start, &start) == -1)
	{
		//err
	}
	//ft_print_map();
	return (start);
}
