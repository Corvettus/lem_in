/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfreeone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 17:41:38 by wclayton          #+#    #+#             */
/*   Updated: 2019/11/02 07:17:28 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstfreeone(t_list **alst)
{
	if (!(alst && *alst))
		return ;
	(*alst)->content_size = 0;
	free((*alst)->content);
	free(*alst);
	*alst = 0;
}
