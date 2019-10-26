/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 03:55:40 by tlynesse          #+#    #+#             */
/*   Updated: 2019/10/25 08:50:17 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	lem_in()
{
	
}

int				main(int argc, char **argv)
{
	(void) argv;
	if (argc == 1)
		lem_in(0);
	else if (argc == 2)
		lem_in(open(argv[1], O_RDONLY));
	else
		terminate(-1);
}
