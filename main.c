/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 03:55:40 by tlynesse          #+#    #+#             */
/*   Updated: 2019/10/30 02:32:26 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				main(int argc, char **argv)
{
	//(void) argv;
	//if (argc == 1)
	//	lem_in(0);
	//else if (argc == 2)
	//	lem_in(open(argv[1], O_RDONLY));
	//else
	//	terminate(-1);
	int				*FD;
	int				i;
	t_inp_val_data	inp_data;

	i = 1;
	FD = (int*)malloc(argc * sizeof(int));
	if (argc == 1)
		FD = 0;
	else
		while (i < argc)
		{
			FD = open(argv[i], O_RDONLY);
			main_input(FD);
			++i;
		}
	
	return (0);
}
