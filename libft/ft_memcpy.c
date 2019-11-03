/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 12:48:01 by wclayton          #+#    #+#             */
/*   Updated: 2019/11/02 07:18:14 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*ft_dst;
	char		*ft_src;

	if (!dst && !src)
		return (NULL);
	ft_dst = (char *)dst;
	ft_src = (char *)src;
	while (n)
	{
		*(ft_dst++) = *(ft_src++);
		n--;
	}
	return (dst);
}
