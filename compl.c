/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 01:54:13 by tlynesse          #+#    #+#             */
/*   Updated: 2019/11/04 02:28:24 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	rooml_comp(t_link **link, t_room *end)
{
	t_link	*tmp;
	t_link	*new;
	t_link	*del;

	new = NULL;
	tmp = *link;
	if (tmp->room->in)
		add_link(&new, linknew(tmp->room->link->room, INFINITY));
	while (tmp->next)
	{
		if (tmp->next->room->in || tmp->next->room == end)
		{
			del = tmp->next;
			if (tmp->next->room->in)
				add_link(&new, linknew(tmp->next->room->link->room, INFINITY));
			tmp->next = tmp->next->next;
			free(del);
		}
		else
			tmp = tmp->next;
	}
	(void)end;
	(void)del;
	rev_link(&new);
	tmp->next = new;
}

void	endl_compl(t_link **link, t_room *start)
{
	t_link	*tmp;
	t_link	*new;

	new = NULL;
	tmp = *link;
	if (tmp->room->in)
		add_link(&new, linknew(tmp->room->link->room, INFINITY));
	else if (tmp->room == start)
		add_link(&new, linknew(tmp->room, INFINITY));
	while (tmp->next)
	{
		if (tmp->next->room->in)
			add_link(&new, linknew(tmp->next->room->link->room, INFINITY));
		else if (tmp->next->room == start)
			add_link(&new, linknew(tmp->next->room, INFINITY));
		tmp = tmp->next;
	}
	(void)start;
	rev_link(&new);
	del_link(link);
	*link = new;
}

void	link_compl(t_room **room, t_room *start, t_room *end)
{
	t_room	*tmp;

	tmp = *room;
	while (tmp)
	{
		if (tmp->link && tmp == end)
			endl_compl(&tmp->link, start);
		else if (tmp->in && tmp->link)
			rooml_comp(&tmp->link, end);
		tmp = tmp->next;
	}
}
