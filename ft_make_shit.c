/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_shit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 04:51:52 by tlynesse          #+#    #+#             */
/*   Updated: 2019/10/27 07:45:13 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room_list_rough	*ft_seach_ends(t_room_list_rough *r_room, int mode)
{
	if (mode == 's')
	{
		while (r_room->start == 1)
			r_room = r_room->next;
		return (r_room);
	}
	else if (mode == 'e')
	{
		while (r_room->end == 1)
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

//==============================================================================

t_link_list	*ft_cast_link(t_room *room_in_to, char type)
{
	t_link_list	*res;

	if ((res = (t_link_list*)malloc(sizeof(t_link_list))) == NULL)
		return (NULL);
	res->prev = NULL;
	res->room = room_in_to;
	res->next = NULL;
	if (type == 'i')
		res = 1;
	return (res);
}

t_link_list	*ft_add_link(t_room *room, char type)
{
	t_link_list	*tmp;
	t_room		*room_in_to;

	tmp = room->link_list;
	if (tmp == NULL)
		room->link_list = ft_cast_link(room_in_to, type);
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = ft_cast_link(room_in_to, type);
	}
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

t_room	*ft_cast_map_elem(t_room_list_rough *r_room, char type)
{
	t_room	*res;

	if ((res = (t_room*)malloc(sizeof(t_room))) == NULL)
		return (NULL);
	if ((res->data->name = ft_strdup(r_room->data->name)) == 0)
	{
		free(res);
		return (NULL);
	}
	res->data->x = r_room->data->x;
	res->data->y = r_room->data->y;
	res->type = type;
	res->link_list = ft_add_link(r_room, type == 'i' ? 'o' : 'i');
	return (res);
}

//----------------------------------------------------------------------------------------------

int	ft_make_map(t_room_list_rough *r_room, t_link_list_rough **r_link,
t_room_list_rough *r_start, t_room *start)
{
	t_link_list_rough	*tmp;
	t_room				*room_in;
	t_link_list_rough	*r_next;

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
	{
		if (start == NULL)
			start = ft_cast_map_elem(r_start, 'i');
		room_in = ft_cast_map_elem(ft_seach_name(r_room, tmp->name2));
		
	}
	else if (ft_strcmp((const char*)tmp->name2,
		(const char*)r_start->data->name) == 0)
	{
		if (start == NULL)
			start = ft_cast_map_elem(r_start, 'i');
		room_in = ft_cast_map_elem(ft_seach_name(r_room, tmp->name1), 'i');
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

t_room	*ft_build(t_room_list_rough *r_room, t_link_list_rough *r_link)
{
	t_room_list_rough	*r_start;
	t_room_list_rough	*r_end;

	r_start = ft_seach_ends(r_room, 's');
	r_end = ft_seach_ends(r_room, 'e');
	if (ft_make_map(r_room, &r_link, r_start, NULL) == -1)
	{
		//err
	}

}
