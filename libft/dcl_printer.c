/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dcl_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 18:54:59 by wclayton          #+#    #+#             */
/*   Updated: 2019/11/02 07:15:41 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			dcl_printer(t_dcl *elem)
{
	while (elem)
	{
		dcl_el_printer(elem);
		elem = elem->next;
	}
}
