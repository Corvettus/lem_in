/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 21:32:51 by wclayton          #+#    #+#             */
/*   Updated: 2019/11/02 07:19:31 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *s, int c)
{
	char			my_c;
	char			*str;

	my_c = (char)c;
	str = (char *)s;
	while (*str)
	{
		if (*str == my_c)
			return (str);
		str++;
	}
	if (*str == my_c)
		return (str);
	return (NULL);
}
