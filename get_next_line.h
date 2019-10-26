/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 18:39:47 by tlynesse          #+#    #+#             */
/*   Updated: 2019/01/22 18:35:59 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 21
# define FD_MAX_NUM 4864

# include <sys/types.h>
# include "./libft/includes/libft.h"

int	get_next_line(const int fd, char **line);

#endif
