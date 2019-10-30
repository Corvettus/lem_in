/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 17:17:52 by tlynesse          #+#    #+#             */
/*   Updated: 2019/10/30 03:09:00 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "get_next_line.h"


t_room_list_rough	*rooms_rough_new(t_room_data *data, int start, int end)
{
	t_room_list_rough	*new_lst;

	if (!(new_lst = (t_room_list_rough*)malloc(sizeof(t_room_list_rough))))
		return (0);
	if (!data)
		new_lst->data = 0;
	else
	{
		if (!(new_lst->data = (t_room_data*)malloc(sizeof(t_room_data))))
		{
			free(new_lst);
			new_lst = 0;
			return (0);
		}
		ft_memcpy(new_lst->data, data, sizeof(data)); //?
	}
	new_lst->next = 0;
	return (new_lst);
}

t_link_list_rough	*link_rough_new(char *name1, char *name2)
{
	t_link_list_rough	*new_lst;

	if (!(new_lst = (t_link_list_rough*)malloc(sizeof(t_link_list_rough))))
		return (0);
	if (!name1)
		new_lst->name1 = 0;
    if (!name1)
		new_lst->name2 = 0;
	else
	{
		if (!((new_lst->name1 = (char*)malloc(sizeof(char) * ft_strlen(name1)))
            && (new_lst->name2 = (char*)malloc(sizeof(char) * ft_strlen(name2)))))
		{
			free(new_lst);
			new_lst = 0;
			return (0);
		}
		ft_memcpy(new_lst->name1, name1, sizeof(char) * ft_strlen(name1));
        ft_memcpy(new_lst->name2, name2, sizeof(char) * ft_strlen(name2)); //?
	}
	new_lst->next = 0;
    new_lst->prev = 0;
	return (new_lst);
}

void	roomlistr_pushback(t_room_list_rough **alst, t_room_list_rough *new)
{
	t_room_list_rough	*tmp;

	if (alst && new)
	{
		if (*alst)
		{
			tmp = *alst;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
			new->next = 0;
		}
		else
		{
			*alst = new;
			(*alst)->next = 0;
		}
	}
}

void	linklistr_pushback(t_link_list_rough **alst, t_link_list_rough *new)
{
	t_link_list_rough	*tmp;

	if (alst && new)
	{
		if (*alst)
		{
			tmp = *alst;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
			new->next = 0;
            new->prev = tmp;
		}
		else
		{
			*alst = new;
			(*alst)->next = 0;
            (*alst)->prev = 0;
		}
	}
}

void    f_error(void)
{
    write(1, "sosi hui\n", 9);
}

void    get_ants_entity(char *line)
{
    int i; //utility
    int ants_entity;

    i = 0;
    while (line[i])
    {
        if (!(ft_isdigit(line[i])))
        {
            f_error();
            exit(0);
        }
        ++i;
    }
    ants_entity = ft_atoi(line);
}

int     str_isdigit(char *str)
{
    int i;

    i = 0;
    if (str)
    {
        while (str[i])
        {
            if (!(ft_isdigit(str[i])))
                return (0);
            ++i;
        }
        return (1);
    }
    return (0);
}


int     isroom(char **room)
{
    int i;

    if (room[0])
    {
        if (room[0][0] != 'L')
        {
            if (room[1] && str_isdigit(room[1]))
            {
                if (room[2] && str_isdigit(room[2]))
                {
                    if (room[3] == 0)
                        return (1);
                }
                return (0);
            }
            return (0);
        }
        return (0);
    }
    return(0);
}

int     islink(char **link)
{
    if (link[0])
    {
        if (link[1] && !link[2])
            return(1);
        return (0);
    }
    return(0);
}

int    parse_room(char *line, t_inp_val_data *util_valdata)
{
    char                **temp;
    t_room_data         data;
    t_room_list_rough   *r_lr;

    temp = ft_strsplit((const char*)line, ' ');
    if (isroom(temp))
    {
        data.name = temp[0];
        data.x = ft_atoi(temp[1]);
        data.y = ft_atoi(temp[2]);
        data.height = -1;
        r_lr = rooms_rough_new(&data, util_valdata->wait_start, util_valdata->wait_end);
        if (util_valdata->wait_start == 1)
        {
            util_valdata->wait_start = 0;
            util_valdata->start_pres = 1;
        }
        if (util_valdata->wait_end == 1)
        {
            util_valdata->wait_end = 0;
            util_valdata->end_pres = 1;
        }
        roomlistr_pushback(&(util_valdata->r_lr), r_lr);
        util_valdata->r_count += 1;
        return (1);
    }
    return (0);
}

int    parse_link(char *line, t_inp_val_data *util_valdata)
{
    char                **temp;
    t_link_list_rough   *l_lr;

    temp = ft_strsplit((const char*)line, '-');
    if (islink(temp))
    {
        l_lr = link_rough_new(temp[0], temp[1]);
        linklistr_pushback(&(util_valdata->l_lr), l_lr);
        return (1);
    }
    return (0);
}

void    parse_line(char *line, int counter, t_inp_val_data *util_valdata)
{
    if (counter == 0)
        get_ants_entity(line);
    else
        {
            if (util_valdata->block_switch == 0)
            {
                if (!parse_room(line, util_valdata))
                {
                    if (parse_link(line, util_valdata))
                        util_valdata->block_switch = 1;
                    else
                        util_valdata->err_pres = 1;
                }                    
            }
            else
            {
                if (!parse_link(line, util_valdata))
                    util_valdata->err_pres = 1;
            }
        }
}

int     validate_xy(t_inp_val_data util_valdata)
{
    t_room_list_rough *i;
    t_room_list_rough *j;

    if (!(util_valdata.r_lr))
        return (0);
    
    i = util_valdata.r_lr;
    while (i->next != 0)
    {
        j = i->next;
        while(j != 0)
        {
            if (((j->data->x == i->data->x) && (j->data->y == i->data->y)) 
            || (j->data->name == i->data->name))
                return (0);
            j = j->next;
        }
        i = i->next;
    }
    return (1);
}

int     main_input(int FD)
{
    int                 counter;
    char                *line;
    t_inp_val_data      util_valdata;

    counter = 0;

    //init valdata
    util_valdata.block_switch = 0; //
    util_valdata.end_pres = 0;     //
    util_valdata.err_pres = 0;     //
    util_valdata.start_pres = 0;   //
    util_valdata.wait_end = 0;
    util_valdata.wait_start = 0;
    util_valdata.l_lr = 0;
    util_valdata.r_lr = 0;
    util_valdata.r_count = 0;
    util_valdata.input_seq = 0;

    while(get_next_line(FD, &line))
    {
        if (line)
        {
            if (!util_valdata.input_seq)
                util_valdata.input_seq = ft_lstnew(line, ft_strlen(line));
            else
                ft_lstaddback(&(util_valdata.input_seq), ft_lstnew(line, ft_strlen(line)));
            if (!(line[0] == '#' && line[1] != '#'))
            {
                
                if (line[0] == '#' && line[1] == '#')
                {
                    if (ft_strcmp((const char*)(&(line[2])), "start") == 0)
                        util_valdata.wait_start = 1;
                    else if (ft_strcmp((const char*)(&(line[2])), "end") == 0)
                        util_valdata.wait_end = 1;
                }
                else
                {
                    parse_line(line, counter, &util_valdata);
                    ++counter;
                }
            }
        }
    }
    if (!(util_valdata.r_lr) || !(util_valdata.l_lr) 
    || util_valdata.end_pres == 0 || util_valdata.start_pres == 0 
    || util_valdata.block_switch == 0)
        util_valdata.err_pres = 1;

    util_valdata.err_pres += validate_xy(util_valdata);
    
    //debug
    printf("worked fine\n");
    return (1);
    //debug
}
