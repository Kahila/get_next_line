/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalombo <akalombo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 11:18:19 by akalombo          #+#    #+#             */
/*   Updated: 2019/07/19 06:45:16 by akalombo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*read_line(char **lines, char *tmp)
{
    t_var       var;

    var.j = 0;
    while (tmp[var.j] != '\0' && tmp[var.j] != '\n')
        var.j++;
    *lines = ft_strsub(tmp, 0, var.j);
    if (ft_strcmp(*lines, tmp) == 0)
        tmp = NULL;
    else
    {
        var.temp = tmp;
        tmp = ft_strsub(tmp, var.j + 1, ft_strlen(tmp + var.j + 1));
        free(var.temp);
    }
    return (tmp);
}

int				get_next_line(const int fd, char **line)
{
    static char	*s_line[1024];
    char		character[BUFF_SIZE + 1];
    t_var       var;

    if (fd < 0 || !line || read(fd, character, 0) < 0)
        return (INVALID);
    if (!s_line[fd])
        s_line[fd] = ft_strnew(BUFF_SIZE);
    while ((var.j = read(fd, character, BUFF_SIZE)) > 0)
    {
        character[var.j] = '\0';
        var.temp = ft_strjoin(s_line[fd], character);
        free(s_line[fd]);
        s_line[fd] = var.temp;
        if (ft_strchr(s_line[fd], '\n'))
            break ;
    }
    if ((var.j < BUFF_SIZE) && !ft_strlen(s_line[fd]))
        return (LINE_NOT_FOUND);
    s_line[fd] = read_line(line, s_line[fd]);
    return (LINE_FOUND);
}

