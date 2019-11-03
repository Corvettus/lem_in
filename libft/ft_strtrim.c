/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 13:26:04 by wclayton          #+#    #+#             */
/*   Updated: 2019/11/02 07:22:09 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			is_sp(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

char				*ft_strtrim(char const *s)
{
	size_t			len;
	unsigned int	start;
	char			*fresh;

	len = 0;
	start = 0;
	if (!s)
		return (0);
	fresh = (char*)s;
	while (is_sp(*fresh++))
		start++;
	fresh--;
	if (*fresh == '\0')
		return (ft_strnew(0));
	while (*fresh++)
		len++;
	fresh--;
	while (is_sp(*--fresh))
		len--;
	if (!(fresh = ft_strsub(s, start, len)))
		return (0);
	return (fresh);
}
