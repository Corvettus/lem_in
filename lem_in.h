/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 20:25:26 by aromny-w          #+#    #+#             */
/*   Updated: 2019/11/04 00:44:44 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

typedef struct s_room	t_room;

typedef struct	s_way
{
	t_room			*room;
	int				ant;
	int				suurbale;
	struct s_way	*next;
}				t_way;

typedef struct	s_path
{
	int				dist;
	t_way			*way;
	struct s_path	*next;
}				t_path;

typedef struct	s_link
{
	t_room			*room;
	float			weight;
	int				visited;
	int				excluded;
	struct s_link	*next;
}				t_link;

typedef struct	s_point
{
	int	x;
	int	y;
}				t_point;

struct			s_room
{
	char			*name;
	t_point			coords;
	float			dist;
	int				num;
	int				in;
	int				out;
	int				links;
	t_link			*link;
	struct s_room	*next;
};

typedef struct	s_map
{
	int				ant_num;
	t_list			*buf;
	t_room			*room;
	t_room			*start;
	t_room			*end;
	int				**matrix;
	int				**add_matrix;
	int				limit;
	t_path			**path;
	int				*path_var_num;
	int				var_num;
	int				rooms_cnt;
	int				start_id;
	int				end_id;
	
}				t_map;

typedef struct	s_dijkstra
{
	int			*q;
	int			*q1;
	int			**matrix;
	int			matrix_size;
	int			*vert;
	int			*dist;
	int			*poin;
	int			min;
	int			i;
	int			latest_dist;
}				t_dijkstra;

void	del_link(t_link **alst);
void	rooml_comp(t_link **link, t_room *end);
void	endl_compl(t_link **link, t_room *start);
void	link_compl(t_room **room, t_room *start, t_room *end);

t_way	*new_way(t_room *room);

t_room	*getroomout(t_room *room);
t_room	*getroomin(t_room *room);
t_room	*init_roomsplit(t_room *room);
void	room_split(t_room **room, t_room *start, t_room *end);

int		*queue(int size);
int		way_len(t_way *way);
void	path_push(t_path ***path, t_way *way, int num, t_map *map);
t_way	*way_prettify(t_way *way);
int		doublelink(t_room *room, char *name1, char *name2);
int		check_roomname(t_room *room, char *name);

size_t	namelen1(char *line);
size_t	namelen2(char *line);

int		islink(char *line, t_room *room);

int		get_rooms_count(t_map *map);
t_room	*find_room_by_num(t_map *map, int num);

int		**init_matrix(int size);
void	mat_delete(int **matrix, int size);
void	fill_matrix(int ***matrix, t_map *map);

void	dijkstra_q_push(int *q, int num);
int		dijkstra_q_pop(int *q);
int		*dijkstra_queue(int size);
void	init_dijkstra(t_dijkstra *dijkstra, t_map *map);
void	reset_dijkstra(t_dijkstra *dijkstra, t_map *map);
void	dij_delete(t_dijkstra *dijkstra);
void	init_search(t_map *map);
void	dijkstra_level_up(int **q, int **q1, int size);
int		dijkstra_add_dist(t_map *map, t_dijkstra *dijkstra);
t_way	*dijkstra(t_map *map, t_dijkstra *dijkstra);

int		mat_search(int ***matrix, t_way *way);
void	mat_copy(int ***matrix, int **add_matrix, int size);


void	init_rooms(t_map *map);

int		get_linked(t_dijkstra *dijkstra, int cur, int *linked);

int		get_limit(t_map *map);

int		check_overlap(t_way *way, t_map **map, t_dijkstra *dijkstra);

void	search_path(t_map *map);

void	rev_room(t_room **room);

t_room	*roomnew(char *name, t_point coords, t_link *link);
void	roomadd(t_room **room, t_room *new);
void	rev_link(t_link **link);
t_link	*linknew(t_room *room, float weight);
void	add_link(t_link **link, t_link *new);

int		iscoord1(char **line);
int		iscoord2(char **line);
size_t	namelen(char *line);

int		isname(char **line, t_room *room);
int		isroom(char *line, t_room *room);
int		iscomment(char *line);
int		iscommand(char *line);
int		isantnbr(char *line);

t_way	*init_way(t_room *room);
void	way_delete(t_way *way);
t_path	*init_path(void);
void	path_delete(t_path *path);

void	ans_wr(int i, t_room *room, char fl);
void	all_ants_one_way(t_map *map, t_path *path);

int		move_up(int dist, t_way *way, t_map *map, int j);
int		path_up(t_path *path, t_map *map);
void	lets_go(t_map *map, t_path *path, int ants, t_path *begin);

void	exit_w(int status);
void	del(void *elem, size_t size);
void	rooml_delete(t_link **link);
void	map_delete(t_map *map);
void	map_deletepath(t_map *map, t_path *path);

void	linker(t_room *room_1, t_room *room_2);

t_room	*getroom1(char *line, t_map map);
t_room	*getroom2(char *line, t_map map);

void	setlink(char *line, t_map *map);

t_point	getcoords(char *line);
char	*getroomname(char *line);
void		setroom(char *line, t_room **room);

void	read_err(t_map *map, int fd, char **line);
void	datarev(t_map *map);
int		readcommand(t_map *map, int fd, char **line);
void	readinput(t_map *map, int fd, char *line);
void	writeinput(t_list *buf);

int		val_part(t_map map);

void	initmap(t_map *map);

void	lem(int fd);

#endif
