/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dcl_push_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 18:57:32 by wclayton          #+#    #+#             */
/*   Updated: 2019/11/02 07:26:21 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			dcl_push_back(t_dcl **first, t_dcl *next)
{
	dcl_end(first);
	(*first)->next = next;
	next->previous = *first;
}
