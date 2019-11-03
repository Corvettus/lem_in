/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 18:03:53 by wclayton          #+#    #+#             */
/*   Updated: 2019/11/02 07:20:26 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	size_t	len;
	char	*new_s;
	int		i;

	if ((!s) || (!f))
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	if ((new_s = (char *)malloc(sizeof(char) * (len + 1))))
	{
		while (*s)
		{
			new_s[i] = f(*s);
			i++;
			s++;
		}
		new_s[i] = 0;
	}
	return (new_s);
}
