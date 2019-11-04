/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_room.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 01:44:51 by tlynesse          #+#    #+#             */
/*   Updated: 2019/11/04 02:36:38 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		iscoord1(char **line)
{
	long	nbr;

	nbr = 0;
	if (**line == '-')
		return (0);
	while (ft_isdigit(**line) && nbr <= INT_MAX)
		nbr = 10 * nbr + (*(*line)++ - '0');
	if (*(*line)++ == ' ' && nbr <= INT_MAX)
		return (1);
	return (0);
}

int		iscoord2(char **line)
{
	long	nbr;

	nbr = 0;
	if (**line == '-')
		return (0);
	while (ft_isdigit(**line) && nbr <= INT_MAX)
		nbr = 10 * nbr + (*(*line)++ - '0');
	if (**line == '\0' && nbr <= INT_MAX)
		return (1);
	return (0);
}

size_t	namelen(char *line)
{
	size_t	len;

	len = 0;
	while (ft_isalnum(*line) || *line == '_')
	{
		line++;
		len++;
	}
	return (len);
}

int		isname(char **line, t_room *room)
{
	char	name[1 + namelen(*line)];
	size_t	i;

	i = 0;
	while (ft_isalnum(**line) || **line == '_')
		name[i++] = *(*line)++;
	name[i] = '\0';
	while (room && ft_strcmp(name, room->name))
		room = room->next;
	if (*(*line)++ == ' ' && !room)
		return (1);
	return (0);
}

int		isroom(char *line, t_room *room)
{
	if (*line == 'L' || *line == '#')
		return (0);
	if (!isname(&line, room))
		return (0);
	if (!iscoord1(&line))
		return (0);
	if (!iscoord2(&line))
		return (0);
	return (1);
}
