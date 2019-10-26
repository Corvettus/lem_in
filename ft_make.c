/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 04:51:52 by tlynesse          #+#    #+#             */
/*   Updated: 2019/10/26 17:43:50 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room_list_rough	*ft_seach_ends(t_room_list_rough *r_room, int mode)
{
	if (mode == 's')
	{
		while (r_room->start == 0)
			r_room = r_room->next;
		return (r_room);
	}
	else if (mode == 'e')
	{
		while (r_room->end == 0)
			r_room = r_room->next;
		return (r_room);
	}
	else
		return (NULL);
}

t_room_list_rough	*ft_seach_name(t_room_list_rough *r_room, char *name)
{
	while (ft_strcmp((const char*)r_room->data->name, (const char*)name) != 0)
		r_room = r_room->next;
	if (ft_strcmp((const char*)r_room->data->name, (const char*)name) == 0)
		return (r_room);
	else
		return (NULL);
}

t_room_out	*ft_cast_map_elem_out(t_room_list_rough *r_room)
{
	t_room_out	*res;

	if ((res = (t_room_out*)malloc(sizeof(t_room_out))) == NULL)
		return (NULL);
	res->link_list = NULL;
	return (res);
}

t_link	*ft_cast_link(t_room_in *room_in_to)
{
	t_link	*res;

	if ((res = (t_link*)malloc(sizeof(t_link))) == NULL)
		return (NULL);
	res->room_in = room_in_to;
	res->weight = 1;
	return (res);
}

void	ft_add_link_elem_out(t_room_out **room_out, t_room_in *room_in_to)
{
	t_link	*tmp;

	tmp = (*room_out)->link_list;
	if (tmp == NULL)
		(*room_out)->link_list = ft_cast_link(room_in_to);
	else
	{
		while (tmp->room_in != NULL)
			tmp = tmp->room_in;
		tmp->room_in = ft_cast_link(room_in_to);
	}
}

t_link_list_rough	*ft_r_link_free_elem(t_link_list_rough *to_del)
{
	if (to_del != NULL && to_del != NULL)
	{
		if(to_del->name1 != NULL)
			free(to_del->name1);
		if(to_del->name2)
			free(to_del->name2);
		free(to_del);
	}
	return (NULL);
}

t_link_list_rough	*ft_r_link_list_del_elem(t_link_list_rough **r_link,
t_link_list_rough *to_del)
{
	if (to_del->prev == NULL)
	{
		*r_link = (*r_link)->next;
		ft_r_link_free_elem(to_del);
		return (*r_link);
	}
	to_del->prev->next = to_del->next;
	to_del->next->prev = to_del->prev;
	ft_r_link_free_elem(to_del);
	return (*r_link);
}

t_room_in	*ft_cast_map_elem_in(t_room_list_rough *r_room)
{
	t_room_in	*res;

	if ((res = (t_room_out*)malloc(sizeof(t_room_out))) == NULL)
		return (NULL);
	if ((res->data->name = ft_strdup(r_room->data->name)) == NULL)
	{
		free(res);
		return (NULL);
	}
	res->data->x = r_room->data->x;
	res->data->y = r_room->data->y;
	res->room_out = ft_cast_map_elem_out(r_room);
	res->room_out->data = res->data;
	return (res);
}

int	ft_make_map(t_room_list_rough *r_room, t_link_list_rough **r_link,
t_room_list_rough *r_start, t_room_in *start)
{
	t_link_list_rough	*tmp;
	t_room_in			*room_in;
	t_link_list_rough	*r_next;

	tmp = r_link;
	while (ft_strcmp((const char*)tmp->name1,
			(const char*)r_start->data->name) != 0 &&
			ft_strcmp((const char*)tmp->name2,
			(const char*)r_start->data->name) != 0 && tmp != NULL)
		tmp = tmp->next;
	if (tmp == NULL)
		return (0);
	if (ft_strcmp((const char*)tmp->name1,
		(const char*)r_start->data->name) == 0)
	{
		if (start == NULL)
			start = ft_cast_map_elem_in(r_start);
		room_in = ft_cast_map_elem_in(ft_seach_name(r_room, tmp->name2));
		
	}
	else if (ft_strcmp((const char*)tmp->name2,
		(const char*)r_start->data->name) == 0)
	{
		if (start == NULL)
			start = ft_cast_map_elem_in(r_start);
		room_in = ft_cast_map_elem_in(ft_seach_name(r_room, tmp->name1));
	}
	if (start != NULL && room_in != NULL)
	{
		ft_add_link_elem_out(&start->room_out, room_in);
		ft_add_link_elem_out(&room_in->room_out, start);
	}
	else
	{
		// free rooms 1 & 2
		return (-1);
	}
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

t_room_in	*ft_build(t_room_list_rough *r_room, t_link_list_rough *r_link)
{
	t_room_list_rough	*r_start;
	t_room_list_rough	*r_end;
	t_room_in			*start;

	r_start = ft_seach_ends(r_room, 's');
	r_end = ft_seach_ends(r_room, 'e');
	start = NULL;
	if (ft_make_map(r_room, &r_link, r_start, start) == -1)
	{
		//err
	}

}