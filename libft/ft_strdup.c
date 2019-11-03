/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 21:25:20 by wclayton          #+#    #+#             */
/*   Updated: 2019/11/02 07:19:52 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strdup(const char *src)
{
	char	*duplicate;

	if ((duplicate = (char*)malloc(sizeof(*duplicate) * (ft_strlen(src) + 1))))
	{
		duplicate = ft_strcpy(duplicate, src);
		return (duplicate);
	}
	return (NULL);
}
