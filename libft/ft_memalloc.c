/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 22:49:26 by wclayton          #+#    #+#             */
/*   Updated: 2019/11/02 07:17:52 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define SIZE_T_MAX 65535

void		*ft_memalloc(size_t size)
{
	void	*area;

	if (!(area = malloc(size)))
		return (0);
	if (size == SIZE_T_MAX)
		size--;
	ft_memset(area, 0, size);
	return (area);
}
