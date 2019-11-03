/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 18:23:01 by wclayton          #+#    #+#             */
/*   Updated: 2019/11/02 07:22:04 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new_s;
	int		i;

	if (!s)
		return (NULL);
	s += start;
	i = 0;
	if ((new_s = (char *)malloc(len + 1)))
	{
		while (len)
		{
			new_s[i] = *s;
			i++;
			s++;
			len--;
		}
		new_s[i] = 0;
		return (new_s);
	}
	else
		return (NULL);
}
