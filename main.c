/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 15:45:21 by wclayton          #+#    #+#             */
/*   Updated: 2019/11/04 02:22:16 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		*queue(int size)
{
	int *queue;

	queue = (int*)malloc(sizeof(int) * (size + 3));
	queue[0] = 2;
	queue[1] = 3;
	queue[2] = 0;
	return (queue);
}

size_t	namelen1(char *line)
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

size_t	namelen2(char *line)
{
	size_t	len;

	len = 0;
	while (*line && *line != '-')
		line++;
	if (!*line++)
		return (0);
	while (ft_isalnum(*line) || *line == '_')
	{
		line++;
		len++;
	}
	return (len);
}

void	lem(int fd)
{
	t_map	map;
	t_path	*path;

	path = NULL;
	initmap(&map);
	readinput(&map, fd, NULL);
	if (!val_part(map))
		exit_w(-1);
	search_path(&map);
	if (!map.path[map.var_num])
		exit_w(-1);
	if ((map.path[map.var_num])->dist == 0)
		exit_w(-1);
	writeinput(map.buf);
	if (map.path[map.var_num]->dist == 1)
		all_ants_one_way(&map, map.path[map.var_num]);
	else
		lets_go(&map, map.path[0], map.ant_num, map.path[0]);
	map_deletepath(&map, path);
}

int		main(int argc, char **argv)
{
	(void)argv;
	if (argc == 1)
		lem(0);
	else if (argc == 2)
		lem(open(argv[1], O_RDONLY));
	else
		exit_w(-1);
}
