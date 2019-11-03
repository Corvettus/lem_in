/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 11:13:51 by wclayton          #+#    #+#             */
/*   Updated: 2019/11/02 07:21:02 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnew(size_t size)
{
	char	*new_s;

	if ((new_s = (char *)malloc(size + 1)))
	{
		ft_bzero(new_s, size + 1);
		return (new_s);
	}
	return (NULL);
}
