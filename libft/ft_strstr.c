/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 22:29:18 by wclayton          #+#    #+#             */
/*   Updated: 2019/11/02 07:21:59 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static int	ft_comparator(unsigned char *s1, unsigned char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (!*s2)
		return (1);
	return (0);
}

char		*ft_strstr(const char *haystack, const char *needle)
{
	if (!*needle)
		return ((char *)haystack);
	while (*haystack)
	{
		if (ft_comparator((unsigned char *)haystack, (unsigned char*)needle))
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
