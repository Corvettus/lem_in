/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dcl_printer_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 18:56:13 by wclayton          #+#    #+#             */
/*   Updated: 2019/11/02 07:15:33 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			dcl_printer_back(t_dcl *elem)
{
	while (elem)
	{
		dcl_el_printer(elem);
		elem = elem->previous;
	}
}
