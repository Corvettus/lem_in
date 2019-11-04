/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 01:48:34 by tlynesse          #+#    #+#             */
/*   Updated: 2019/11/04 02:20:19 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		readcommand(t_map *map, int fd, char **line)
{
	char	cmd[ft_strlen(*line) + 1];

	ft_strcpy(cmd, *line);
	if (ft_strcmp("##start", cmd) && ft_strcmp("##end", cmd))
		return (0);
	ft_lstadd(&map->buf, ft_lstnew(*line, ft_strlen(*line) + 1));
	free(*line);
	if (get_next_line(fd, line) != 1)
		*line = ft_strdup("");
	if (!isroom(*line, map->room))
		read_err(map, fd, line);
	else if (!ft_strcmp("##start", cmd))
	{
		setroom(*line, &map->start);
		roomadd(&map->room, map->start);
	}
	else if (!ft_strcmp("##end", cmd))
	{
		setroom(*line, &map->end);
		roomadd(&map->room, map->end);
	}
	return (1);
}

void	readinput(t_map *map, int fd, char *line)
{
	int		s[3];

	ft_memset(s, 0, sizeof(s));
	while (get_next_line(fd, &line) == 1)
	{
		if (isantnbr(line) && map->ant_num < 0 && !s[1] && !s[2] && (s[0] = 1))
			map->ant_num = ft_getnbr(line);
		else if (isroom(line, map->room) && s[0] && !s[2] && (s[1] = 1))
			setroom(line, &map->room);
		else if (islink(line, map->room) && s[0] && s[1] && (s[2] = 1))
			setlink(line, map);
		else if (iscomment(line))
			(void)line;
		else if (iscommand(line))
			readcommand(map, fd, &line) ? s[1] = 1 : 0;
		else
			read_err(map, fd, &line);
		ft_lstadd(&map->buf, ft_lstnew(line, ft_strlen(line) + 1));
		free(line);
	}
	datarev(map);
	close(fd);
}

int		val_part(t_map map)
{
	if (map.ant_num <= 0)
		return (0);
	if (!map.start || !map.end || !map.start->links || !map.end->links)
		return (0);
	return (1);
}

void	read_err(t_map *map, int fd, char **line)
{
	close(fd);
	free(*line);
	map_delete(map);
	exit_w(-1);
}
