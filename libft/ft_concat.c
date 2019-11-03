/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 03:50:45 by bharrold          #+#    #+#             */
/*   Updated: 2019/10/07 03:50:57 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_concat(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new;

	if (!s1)
		return (ft_strdup(s2));
	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	new = (char *)malloc(sizeof(char) * (i + j + 2));
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	new[i++] = '\n';
	j = -1;
	while (s2[++j])
		new[i++] = s2[j];
	new[i] = '\0';
	free(s1);
	return (new);
}
