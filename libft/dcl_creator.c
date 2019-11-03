/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dcl_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 18:56:39 by wclayton          #+#    #+#             */
/*   Updated: 2019/11/02 07:14:40 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dcl			*dcl_creator(char c, int n)
{
	t_dcl *new;

	new = (t_dcl *)malloc(sizeof(t_dcl));
	new->c = c;
	new->n = n;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}
