/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:26:07 by wclayton          #+#    #+#             */
/*   Updated: 2019/11/02 07:18:23 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char			*my_dst;
	const unsigned char		*my_src;

	if (!dst && !src)
		return (NULL);
	my_dst = (unsigned char *)dst;
	my_src = (unsigned char *)src;
	if (my_src < my_dst)
	{
		while (len)
		{
			len--;
			*(my_dst + len) = *(my_src + len);
		}
	}
	else if (my_dst < my_src)
		ft_memcpy(dst, src, len);
	return (dst);
}
