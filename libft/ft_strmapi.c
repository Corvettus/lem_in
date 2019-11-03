/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 22:51:35 by wclayton          #+#    #+#             */
/*   Updated: 2019/11/02 07:20:32 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*fresh;

	i = 0;
	fresh = 0;
	if (s && f)
		if ((fresh = ft_strnew(ft_strlen(s))))
			while (s[i])
			{
				fresh[i] = f(i, (char)s[i]);
				i++;
			}
	return (fresh);
}
