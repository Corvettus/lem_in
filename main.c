/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 15:45:21 by wclayton          #+#    #+#             */
/*   Updated: 2019/11/04 00:41:12 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem_in.h"
//lemin, read, setroom, setlink, map_delete, 

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

void		link_compl(t_room **room, t_room *start, t_room *end)
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

t_way	*new_way(t_room *room)
{
	t_way	*way;

	way = NULL;
	if (!(way = (t_way *)malloc(sizeof(t_way))))
		exit_w(-1);
	way->room = room;
	way->next = NULL;
	return (way);
}

void	add_way(t_way **way, t_way *new)
{
	new->next = *way;
	*way = new;
}

t_room	*getroomout(t_room *room)
{
	t_room	*out;
	t_link	*tmp;

	out = roomnew(room->name, room->coords, NULL);
	out->out = 1;
	tmp = room->link;
	while ((tmp))
		tmp = tmp->next;
	
	rev_link(&out->link);
	return (out);
}

t_room	*getroomin(t_room *room)
{
	t_room	*in;
	t_link	*tmp;

	in = room;
	in->in = 1;
	in->links = 1;
	tmp = in->link;
	while (tmp)
	{
		tmp->weight = INFINITY;
		tmp = tmp->next;
	}
	return (in);
}

t_room	*init_roomsplit(t_room *room)
{
	t_room	*in;
	t_room	*out;

	in = getroomin(room);
	out = getroomout(room);
	add_link(&in->link, linknew(out, 0));
	add_link(&out->link, linknew(in, INFINITY));
	out->next = in->next;
	in->next = out;
	return (in);
}

void			room_split(t_room **room, t_room *start, t_room *end)
{
	t_room	*tmp;

	tmp = *room;
	while (tmp)
	{
		if (tmp != start && tmp != end)
		{
			tmp = init_roomsplit(tmp);
			tmp = tmp->next->next;
		}
		else
			tmp = tmp->next;
	}
	link_compl(room, start, end);
}


int		*queue(int size)
{
	int *queue;

	queue = (int*)malloc(sizeof(int) * (size + 3));
	queue[0] = 2;
	queue[1] = 3;
	queue[2] = 0;
	return (queue);
}

int		way_len(t_way *way)
{
	t_way	*ptr;
	int		i;

	i  = 0;
	ptr = way;
	while (ptr)
	{
		i++;
		ptr->ant = 0;
		ptr = ptr->next;
	}
	return (i);
}

void	path_push(t_path ***path, t_way *way, int num, t_map *map)
{
	t_path *ptr;
	
	map->var_num = num;
	map->path_var_num[num] += 1;
	if (!(*path)[num])
	{
		(*path)[num] = init_path();
		(*path)[num]->way = way;
		(*path)[num]->next = NULL;
		(*path)[num]->dist = 0;
		(*path)[num]->dist = way_len(way);
		return ;
	}
	else
	{
		ptr = (*path)[num];
		while (ptr && ptr->next)
			ptr = ptr->next;
		ptr->next = init_path();
		ptr->next->way = way;
		ptr->next->dist = way_len(way);
	}
}


t_way	*way_prettify(t_way *way)
{
	t_way	*ptr;
	t_way	*cur;

	ptr = way;
	cur = NULL;
	cur = ptr;
	ptr = ptr->next;
	way = way->next;
	free(cur);
	while (ptr && ptr->next)
	{
		if (ptr->room->name == ptr->next->room->name)
		{
			cur = ptr->next;
			ptr->next = ptr->next->next;
			free(cur);
			continue;
		}
		ptr = ptr->next;
	}
	return (way);
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

int		check_roomname(t_room *room, char *name)
{
	while (room && ft_strcmp(name, room->name))
		room = room->next;
	if (room)
		return (1);
	return (0);
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

int				islink(char *line, t_room *room)
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

int			get_rooms_count(t_map *map)
{
	int		i;
	t_room	*ptr;

	i = 0;
	ptr = map->room;
	while (ptr)
	{
		ptr->dist = 0;
		i++;
		ptr = ptr->next;
	}
	return (i);
}

t_room		*find_room_by_num(t_map *map, int num)
{
	t_room		*ptr;

	if (map->start->num == num)
		return (map->start);
	if (map->end->num == num)
		return (map->end);
	ptr = map->room;
	while (ptr)
	{
		if (ptr->num == num)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

int		**init_matrix(int size)
{
	int		**matrix;
	int		i;
	int		j;

	matrix = (int**)malloc(sizeof(int*) * (size + 1));
	i = -1;
	while (++i < size)
	{
		matrix[i] = (int *)malloc(sizeof(int) * (size + 1));
		j = -1;
		while (++j < size)
			matrix[i][j] = 0;
	}
	return (matrix);
}

void	mat_delete(int **matrix, int size)
{
	int		i;

	i = 0;
	while (i < size)
		free(matrix[i++]);
	free(matrix);
}

void	fill_matrix(int ***matrix, t_map *map)
{
	t_link *ptr;
	t_room *room_ptr;

	room_ptr = map->room;
	while (room_ptr)
	{
		ptr = room_ptr->link;
		while (ptr)
		{
			(*matrix)[ptr->room->num][room_ptr->num] = 1;
			ptr = ptr->next;
		}
		room_ptr = room_ptr->next;
	}
}

void	dijkstra_q_push(int *q, int num)
{
	q[++q[0]] = num;
	q[2]++;
}

int		dijkstra_q_pop(int *q)
{
	q[2]--;
	return (q[q[1]++]);
}

int		*dijkstra_queue(int size)
{
	int *q;

	q = (int*)malloc(sizeof(int) * (size + 3));
	q[0] = 2;
	q[1] = 3;
	q[2] = 0;
	return (q);
}

void	init_rooms(t_map *map)
{
	t_room	*ptr;
	int		i;

	i = 0;
	ptr = map->room;
	while (ptr)
	{
		ptr->dist = 0;
		if (ptr == map->start)
			map->start_id = i;
		if (ptr == map->end)
			map->end_id = i;
		ptr->num = i;
		i++;
		ptr = ptr->next;
	}
}

void	init_dijkstra(t_dijkstra *dijkstra, t_map *map)
{
	int	i;

	(dijkstra)->matrix = map->matrix;
	(dijkstra)->matrix_size = map->rooms_cnt;
	(dijkstra)->vert = (int*)malloc(sizeof(int) * map->rooms_cnt);
	(dijkstra)->dist = (int*)malloc(sizeof(int) * map->rooms_cnt);
	(dijkstra)->poin = (int*)malloc(sizeof(int) * map->rooms_cnt);
	i = 0;
	while (i < map->rooms_cnt)
	{
		dijkstra->vert[i] = 0;
		dijkstra->dist[i] = 0;
		dijkstra->poin[i] = -1;
		i++;
	}
}

void	reset_dijkstra(t_dijkstra *dijkstra, t_map *map)
{
	int	i;

	i = 0;
	while (i < map->rooms_cnt)
	{
		dijkstra->vert[i] = 0;
		dijkstra->dist[i] = 0;
		dijkstra->poin[i] = -1;
		i++;
	}
}

void	dij_delete(t_dijkstra *dijkstra)
{
	free(dijkstra->vert);
	free(dijkstra->dist);
	free(dijkstra->poin);
}

void	init_search(t_map *map)
{
	int		i;

	i = 0;
	room_split(&(map->room), map->start, map->end);
	init_rooms(map);
	map->rooms_cnt = get_rooms_count(map);
	map->matrix = init_matrix(map->rooms_cnt);
	map->add_matrix = init_matrix(map->rooms_cnt);
	fill_matrix(&(map->matrix), map);
	fill_matrix(&(map->add_matrix), map);
	map->limit = get_limit(map);
	map->path = (t_path**)malloc(sizeof(t_path*) * map->limit);
	map->path_var_num  = (int*)malloc(sizeof(int) * map->limit);
	while (i < map->limit)
	{
		map->path[i] = NULL;
		map->path_var_num[i] = 0;
		i++;
	}
	map->var_num = 0;
}

void	dijkstra_level_up(int **q, int **q1, int size)
{
	free(*q);
	*q = *q1;
	*q1 = queue(size);
}

int		get_linked(t_dijkstra *dijkstra, int cur, int *linked)
{
	int	i;

	i = 0;
	while (i < dijkstra->matrix_size)
	{
		if (dijkstra->matrix[cur][i] && dijkstra->vert[i] == 0)
		{
			*linked = i;
			return (1);
		}
		i++;
	}
	return (0);
}

int	dijkstra_add_dist(t_map *map, t_dijkstra *dijkstra)
{
	int		cur;
	int		linked;
	int		i;
	
	i = 1;
	dijkstra->q1 = dijkstra_queue(dijkstra->matrix_size);
	cur = map->start_id;
	dijkstra->vert[cur] = 1;
	dijkstra_q_push(dijkstra->q, cur);
	while (dijkstra->q[2] != 0)
	{
		cur = dijkstra_q_pop(dijkstra->q);
		while (get_linked(dijkstra, cur, &linked))
		{
			dijkstra->vert[linked] = 1;
			dijkstra->dist[linked] = i;
			dijkstra->poin[linked] = cur;
			dijkstra_q_push(dijkstra->q1, linked);
		}
		if (dijkstra->q[2] == 0 && ++i)
			dijkstra_level_up(&(dijkstra->q), &(dijkstra->q1), dijkstra->matrix_size);
	}
	dijkstra->poin[map->start_id] = -1;
	free(dijkstra->q);
	free(dijkstra->q1);
	return (0);
}

t_way	*dijkstra(t_map *map, t_dijkstra *dijkstra)
{
	t_way	*way;

	way = NULL;
	dijkstra->q = dijkstra_queue(dijkstra->matrix_size);
	// if (dijkstra_stend_check(dijkstra, map, &way))
	// 	return (way);
	dijkstra_add_dist(map, dijkstra);
	dijkstra->i = map->end_id;
	if (dijkstra->poin[dijkstra->i] == -1)
		return (NULL);
	dijkstra->latest_dist = 0;
	while (dijkstra->i != -1)
	{
		add_way(&way, new_way(find_room_by_num(map, dijkstra->i)));
		dijkstra->i = dijkstra->poin[dijkstra->i];
		dijkstra->latest_dist++;
	}
	return (way);
}

int		mat_search(int ***matrix, t_way *way)
{
	t_way	*ptr;
	t_way	*next;
	int		i = 0;
	
	ptr = way;
	next = ptr->next;
	while (next)
	{
		(*matrix)[ptr->room->num][next->room->num] = ((*matrix)[ptr->room->num][next->room->num]) ? 0 : 1;
		(*matrix)[next->room->num][ptr->room->num] = ((*matrix)[next->room->num][ptr->room->num]) ? 0 : 1;
		ptr = ptr->next;
		next = next->next;
		i++;
	}
	return (i);
}


void	mat_copy(int ***matrix, int **add_matrix, int size)
{
	int		i;
	int		j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while(++j < size)
			(*matrix)[i][j] = add_matrix[i][j];
	}
}

int		get_limit(t_map *map)
{
	int lim;

	if (map->rooms_cnt < 2000)
		lim = 12;
	else
	{
		lim = 6;
		if (map->ant_num > 130)
			lim = 7;
		if (map->ant_num > 175)
			lim = 8;
		if (map->ant_num > 200)
			lim = 9;
		if (map->ant_num > 220)
			lim = 10;
		if (map->ant_num > 250)
			lim = 12;
		if (map->ant_num > 325)
			lim = 13;
		if (map->ant_num > 450)
			lim = 14;
	}
	return (lim + 10);
}

int		check_overlap(t_way *way, t_map **map, t_dijkstra *dijkstra)
{
	t_way	*ptr;
	t_way	*next;

	ptr = way;
	next = ptr->next;
	while (next)
	{
		if ((ptr->room->name == next->room->name && ptr->room->out &&
			next->room->in) || (ptr->room->name != next->room->name &&
			ptr->room->in && next->room->out))
		{
			(*map)->add_matrix[ptr->room->num][next->room->num] = 0;
			(*map)->add_matrix[next->room->num][ptr->room->num] = 0;
			{
				mat_copy(&dijkstra->matrix, (*map)->add_matrix, (*map)->rooms_cnt);
				return (1);
			}
			
		}
		ptr = ptr->next;
		next = next->next;
	}
	return (0);
}

void	search_path(t_map *map)
{
	t_dijkstra	dijkstrao;
	t_way	*tmp;
	int		lim;
	// int		k;

	lim = 0;
	// k = 0;
	init_search(map);
	init_dijkstra(&dijkstrao, map);
	while (lim < map->limit //&& k < map->limit_variations + 1
		&& (tmp = dijkstra(map, &dijkstrao)))
	{
		if (check_overlap(tmp, &map, &dijkstrao))
		{
			++lim;
			//k = 0;
			reset_dijkstra(&dijkstrao, map);
			continue;
		}
		mat_search(&map->matrix, tmp);
		path_push(&map->path, way_prettify(tmp), lim, map);
		reset_dijkstra(&dijkstrao, map);
		//k++;
	}
	dij_delete(&dijkstrao);
	mat_delete(map->matrix, map->rooms_cnt);
}

void	rev_room(t_room **room)
{
	t_room	*prev;
	t_room	*curr;
	t_room	*next;

	prev = NULL;
	curr = *room;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*room = prev;
}

t_room		*roomnew(char *name, t_point coords, t_link *link)
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

int				isroom(char *line, t_room *room)
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

int	iscomment(char *line)
{
	if (line[0] == '#' && line[1] != '#')
		return (1);
	return (0);
}

int	iscommand(char *line)
{
	if (line[0] == '#' && line[1] == '#')
		return (1);
	return (0);
}

int	isantnbr(char *line)
{
	long	nbr;

	nbr = 0;
	if (!ft_isdigit(*line) && *line != '+')
		return (0);
	if (*line == '+')
		line++;
	while (ft_isdigit(*line) && nbr <= INT_MAX)
		nbr = 10 * nbr + (*line++ - '0');
	if (!*line && nbr <= INT_MAX)
		return (1);
	return (0);
}


t_way	*init_way(t_room *room)
{
	t_way	*way;

	way = (t_way*)malloc(sizeof(t_way));
	way->room = room;
	way->ant = 0;
	way->next = NULL;
	return (way);
}

void	way_delete(t_way *way)
{
	t_way	*ptr;
	t_way	*next;

	ptr = way;
	while (ptr)
	{
		next = ptr->next;
		free(ptr);
		ptr = NULL;
		ptr = next;
	}
}

t_path	*init_path(void)
{
	t_path *path;

	path = (t_path*)malloc(sizeof(t_path));
	path->way = NULL;
	path->next = NULL;
	path->dist = -1;
	return (path);
}

void	path_delete(t_path *path)
{
	t_path	*ptr;
	t_path	*next;

	ptr = path;
	while (ptr)
	{
		next = ptr->next;
		way_delete(ptr->way);
		ptr->way = NULL;
		free(ptr);
		ptr = NULL;
		ptr = next;
	}
	path = NULL;
}

void	ans_wr(int i, t_room *room, char fl)
{
	char	*ant;

	ant = ft_itoa(i);
	if (fl)
		write(1, " ", 1);
	write(1, "L", 1);
	ft_putstr(ant);
	write(1, "-", 1);
	ft_putstr(room->name);
	free(ant);
}

void	all_ants_one_way(t_map *map, t_path *path)
{
	int ant;

	ant = 1;
	ans_wr(ant, path->way->room, 0);
	while (++ant <= map->ant_num)
	{
		ans_wr(ant, path->way->room, 1);
	}
	write(1, "\n", 1);
}

int		move_up(int dist, t_way *way, t_map *map, int j)
{
	int	i;

	i = 0;
	while (dist--)
		way = way->next;
	(void)map;
	if (way->ant != 0)
	{
		i = 1;
		if (way->next != NULL)
		{
			ans_wr(way->ant, way->next->room, j);
			way->next->ant = way->ant;
		}
		else
			i = 0;
		way->ant = 0;
	}
	return (i);
}

int		path_up(t_path *path, t_map *map)
{
	int dist;
	int i;

	i = 0;
	while (path)
	{
		dist = path->dist;
		while (dist--)
			if (move_up(dist, path->way, map, i))
				i = 1;
		path = path->next;
	}
	return (i);
}

void	lets_go(t_map *map, t_path *path, int ants, t_path *begin)
{
	int		ant;
	int		sw;

	ant = 0;
	while (ant < ants)
	{
		sw = path_up(path, map);
		path = begin;
		path->way->ant = ++ant;
		ans_wr(ant, path->way->room, sw);
		while (path->next && path->next->dist - begin->dist < ants - ant)
		{
			path = path->next;
			path->way->ant = ++ant;
			ans_wr(ant, path->way->room, 1);
		}
		write(1, "\n", 1);
	}
	while (ant)
	{
		ant = path_up(begin, map);
		if (ant)
			write(1, "\n", 1);
	}
}

void	exit_w(int status)
{
	if (status == -1)
		ft_putstr_fd("ERROR\n", 2);
	if (status != -1)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}

void	del(void *elem, size_t size)
{
	size = 0;
	free(elem);
}

void	rooml_delete(t_link **link)
{
	t_link	*tmp;
	t_link	*next;

	tmp = *link;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void		map_delete(t_map *map)
{
	t_room	*tmp;
	t_room	*next;

	tmp = map->room;
	while (tmp)
	{
		next = tmp->next;
		rooml_delete(&tmp->link);
		if (!tmp->in)
			free(tmp->name);
		free(tmp);
		tmp = next;
	}
	ft_lstdel(&map->buf, del);
	ft_memset(map, 0, sizeof(t_map));
	map = NULL;
}

void		map_deletepath(t_map *map, t_path *path)
{
	map_delete(map);
	path_delete(path);
	exit(-1);
}

void		linker(t_room *room_1, t_room *room_2)
{
	add_link(&room_1->link, linknew(room_2, 1));
	add_link(&room_2->link, linknew(room_1, 1));
	room_1->links++;
	room_2->links++;
}

t_room	*getroom1(char *line, t_map map)
{
	char	*name;
	size_t	len;

	len = 0;
	while (line[len] != '-')
		len++;
	name = ft_strsub(line, 0, len);
	while (map.room && ft_strcmp(name, map.room->name))
		map.room = map.room->next;
	free(name);
	return (map.room);
}

t_room	*getroom2(char *line, t_map map)
{
	char	*name;

	while (*line != '-')
		line++;
	name = ft_strdup(++line);
	while (map.room && ft_strcmp(name, map.room->name))
		map.room = map.room->next;
	free(name);
	return (map.room);
}

void			setlink(char *line, t_map *map)
{
	t_room	*room1;
	t_room	*room2;

	room1 = getroom1(line, *map);
	room2 = getroom2(line, *map);
	linker(room1, room2);
}

t_point	getcoords(char *line)
{
	t_point	coords;

	while (*line != ' ')
		line++;
	coords.x = ft_getnbr(++line);
	while (*line != ' ')
		line++;
	coords.y = ft_getnbr(++line);
	return (coords);
}

char		*getroomname(char *line)
{
	size_t	len;

	len = 0;
	while (line[len] != ' ')
		len++;
	return (ft_strsub(line, 0, len));
}

void			setroom(char *line, t_room **room)
{
	t_room	*new;
	char	*name;
	t_point	coords;

	name = getroomname(line);
	coords = getcoords(line);
	new = roomnew(name, coords, NULL);
	roomadd(room, new);
}

void	read_err(t_map *map, int fd, char **line)
{
	close(fd);
	free(*line);
	map_delete(map);
	exit_w(-1);
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

int	readcommand(t_map *map, int fd, char **line)
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

void		readinput(t_map *map, int fd, char *line)
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

void		writeinput(t_list *buf)
{
	while (buf)
	{
		ft_putendl(buf->content);
		buf = buf->next;
	}
	ft_putchar('\n');
}

int		val_part(t_map map)
{
	if (map.ant_num <= 0)
		return (0);
	if (!map.start || !map.end || !map.start->links || !map.end->links)
		return (0);
	return (1);
}

void		initmap(t_map *map)
{
	map->ant_num = -1;
	map->buf = NULL;
	map->room = NULL;
	map->start = NULL;
	map->end = NULL;
}

void			lem(int fd)
{
	t_map	map;
	t_path	*path;

	path = NULL;
	initmap(&map);
	readinput(&map, fd, NULL);
	if(!val_part(map))
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

int				main(int argc, char **argv)
{
	(void) argv;
	if (argc == 1)
		lem(0);
	else if (argc == 2)
		lem(open(argv[1], O_RDONLY));
	else
		exit_w(-1);
}
