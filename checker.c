/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 01:46:33 by tlynesse          #+#    #+#             */
/*   Updated: 2019/11/04 02:27:56 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		iscomment(char *line)
{
	if (line[0] == '#' && line[1] != '#')
		return (1);
	return (0);
}

int		iscommand(char *line)
{
	if (line[0] == '#' && line[1] == '#')
		return (1);
	return (0);
}

int		isantnbr(char *line)
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

void	exit_w(int status)
{
	if (status == -1)
		ft_putstr_fd("ERROR\n", 2);
	if (status != -1)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}
