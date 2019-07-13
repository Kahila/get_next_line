/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalombo <akalombo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 16:00:34 by akalombo          #+#    #+#             */
/*   Updated: 2019/07/13 11:47:59 by akalombo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# define BUFF_SIZE 128
# include "libft/libft.h"

enum				e_return_code
{
	LINE_NOT_FOUND,
	LINE_FOUND,
	INVALID = -1
};
typedef struct		s_var
{
	char	*temp;
	int		j;
}					t_var;
int					get_next_line(const int fd, char **line);
#endif
