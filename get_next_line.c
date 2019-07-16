/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalombo <akalombo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 06:33:11 by akalombo          #+#    #+#             */
/*   Updated: 2019/07/16 18:33:57 by akalombo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	        *ft_join(char *buff, char *tmp)
{
    size_t	i;
    t_var	var;

    i = 0;
    var.j = 0;
    if (buff)
        i = ft_strlen(buff);
    if (tmp)
        var.j = ft_strlen(tmp);
    var.temp = (char *)malloc(sizeof(char) * (i + var.j + 1));
    ft_memcpy(var.temp, buff, i);
    ft_memcpy(var.temp + i, tmp, var.j);
    var.temp[i + var.j] = '\0';
    return (var.temp);
}

static int	find_line(char *buff)
{
    int		i;

    i = 0;
    while (buff[i] != '\n' && buff[i] != '\0')
        i++;
    if (buff[i] == '\n')
    {
        buff[i] = '\0';
        return (i);
    }
    return (INVALID);
}

static int	save_line(char **buff, char **tmp, char **line)
{
    int		i;

    *buff = ft_join(*buff, *tmp);
    i = find_line(*buff);
    if (i > -1)
    {
        *line = ft_strdup(*buff);
        *buff = ft_strdup(*buff + i + 1);
        return (LINE_FOUND);
    }
    return (LINE_NOT_FOUND);
}

int			get_next_line(int const fd, char **line)
{
    static char *buff[BUFF_SIZE];
    t_var       var;  

    var.temp = ft_strnew(BUFF_SIZE);
    if (!line || BUFF_SIZE <= 0 || fd < 0 || (read(fd, var.temp, 0)) < 0)
        return (INVALID);
    while ((read(fd, var.temp, BUFF_SIZE)) > 0)
    {
        var.j = save_line(&buff[fd], &var.temp, line);
        if (var.j == 1)
            return (LINE_FOUND);
    }
    if ((var.j = save_line(&buff[fd], &var.temp, line) > 0))
        return (LINE_FOUND);
    else if (ft_strlen(buff[fd]) > 0)
    {
        *line = ft_strdup(buff[fd]);
        ft_strdel(&buff[fd]);
        return (LINE_FOUND);
    }
    return (var.j);
}
