/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 02:10:13 by tlynesse          #+#    #+#             */
/*   Updated: 2019/11/04 02:20:48 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	del_link(t_link **alst)
{
	t_link	*tmp;
	t_link	*next;

	tmp = *alst;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	*alst = NULL;
}

int		doublelink(t_room *room, char *name1, char *name2)
{
	t_link	*tmp;

	if (room)
	{
		while (ft_strcmp(name1, room->name))
			room = room->next;
		tmp = room->link;
		while (tmp)
		{
			if (!ft_strcmp(name2, tmp->room->name))
				return (1);
			tmp = tmp->next;
		}
	}
	return (0);
}

int		islink(char *line, t_room *room)
{
	char	name1[1 + namelen1(line)];
	char	name2[1 + namelen2(line)];
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (ft_isalnum(*line) || *line == '_')
		name1[i++] = *line++;
	name1[i] = '\0';
	if (*line++ != '-')
		return (0);
	if (*line == 'L' || *line == '#')
		return (0);
	while (ft_isalnum(*line) || *line == '_')
		name2[j++] = *line++;
	name2[j] = '\0';
	if (!check_roomname((room), name1) || !check_roomname(room, name2))
		return (0);
	if (doublelink(room, name1, name2))
		return (0);
	(void)room;
	if (!*line)
		return (1);
	return (0);
}

void	linker(t_room *room_1, t_room *room_2)
{
	add_link(&room_1->link, linknew(room_2, 1));
	add_link(&room_2->link, linknew(room_1, 1));
	room_1->links++;
	room_2->links++;
}

void	datarev(t_map *map)
{
	t_room	*tmp;

	rev_room(&map->room);
	tmp = map->room;
	while (tmp)
	{
		rev_link(&tmp->link);
		tmp = tmp->next;
	}
	ft_lstrev(&map->buf);
}
