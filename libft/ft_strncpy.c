/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 20:26:18 by wclayton          #+#    #+#             */
/*   Updated: 2019/11/02 07:20:53 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char		*ft_strncpy(char *dst, const char *src, size_t len)
{
	int i;

	i = 0;
	while (*src && len)
	{
		dst[i] = *src;
		i++;
		src++;
		len--;
	}
	while (len)
	{
		dst[i] = 0;
		i++;
		len--;
	}
	return (dst);
}
