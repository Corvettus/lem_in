/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 19:15:05 by wclayton          #+#    #+#             */
/*   Updated: 2019/11/02 07:13:27 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				calc(char *expr)
{
	int		result;
	t_dcl	*t_expr;

	if (ft_check_brackets(expr) == 0)
	{
		write(1, "BAD BRACKETS! ", 14);
		return (0);
	}
	t_expr = make_rpn(expr);
	dcl_begin(&t_expr);
	result = dcl_rpn(t_expr);
	return (result);
}
