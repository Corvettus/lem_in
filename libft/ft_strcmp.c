/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:13:14 by wclayton          #+#    #+#             */
/*   Updated: 2019/11/02 07:19:40 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 == *s2)
		{
			s1++;
			s2++;
			continue ;
		}
		else
			return ((unsigned char)*s1 - (unsigned char)*s2);
	}
	if (*s1)
		return (1);
	if (*s2)
		return (-1);
	return (0);
}
