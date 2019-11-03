/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 21:32:51 by wclayton          #+#    #+#             */
/*   Updated: 2019/11/02 07:21:10 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	char			my_c;
	char			*ptr;
	char			*str;

	my_c = (char)c;
	ptr = NULL;
	str = (char *)s;
	while (*str)
	{
		if (*str == my_c)
			ptr = str;
		str++;
	}
	if (*str == my_c)
		ptr = str;
	if (ptr)
		return (ptr);
	return (NULL);
}
