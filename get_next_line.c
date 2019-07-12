/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalombo <akalombo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 11:18:19 by akalombo          #+#    #+#             */
/*   Updated: 2019/07/12 13:48:43 by akalombo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char      *read_line(ssize_t f, int fd, char *buff, char *temp)
{
    int i;

    i = 0;
    while (f > 0)
    {
        if (buff[i] == '\n')
            break;
        else if (i == BUFF_SIZE)
        {
            f = read(fd, buff, BUFF_SIZE);
            if (f == 0)
            {
                if (BUFF_SIZE == 1)
                    return (temp);		
                return ((char *)LINE_NOT_FOUND);
            }
            temp = ft_strjoin(temp, buff);
            i = -1;
        }
        i++;
    }
    return (temp);
}

int         check(char ***line, t_var *var, int s)
{
    char new[sizeof(char) * (var->j +1)];
    ssize_t w;
    w = 0;

    s = ft_strlen(var->temp) - var->j;
    ft_bzero(new, var->j + 1);
    while (var->temp[s] != '\0')
    {
        new[w] = var->temp[s];
        if (var->temp[s] == '\n')
        {
            if (var->j--)
				**line = ft_memalloc(sizeof(char) * (w + 1));
            **line = ft_strncpy(**line, new, w);
            return (0);
        }
        s++;
        w++;
        var->j--;
    }
	free(var->temp);
    var->temp = ft_strdup(new);
    return (w);
}

int				gnl(int fd, char **line, ssize_t i, int s, char *buff)
{
    static t_var var;

    if (var.j > 0)
    {
        i = check(&line, &var ,s);
        if (i == 0)
            return (LINE_FOUND);
    }
    if (i == 0)
        var.temp = ft_memalloc(sizeof(char) * (BUFF_SIZE  + 1));
    if ((i = read(fd, buff, BUFF_SIZE)) == 0)
	{
		free(var.temp);
        return (LINE_NOT_FOUND);
	}
    var.temp = ft_strjoin(var.temp, buff);
    if ((var.temp = read_line(i, fd, buff, var.temp)) == (char *)LINE_NOT_FOUND)
        return (LINE_NOT_FOUND);
    if (var.temp[(s = 0)])
        while (var.temp[s] != '\n')
            s++;
    s++;
    if (var.j == 0 && (*line = (char *)malloc(sizeof(char) * (s + 1))))
        *line = ft_strncat(*line, var.temp, s - 1);
    var.j = ft_strlen(var.temp) - s;
    return (LINE_FOUND);
}

int			get_next_line(const int fd, char **line)
{
    ssize_t i;  
    int s ;
    char buff[BUFF_SIZE + 1];

    i = 0;
    s = 0;
    ft_bzero(buff, BUFF_SIZE + 1);
    if (fd <  0 || line == NULL)
        return (INVALID);
    return gnl(fd, line, i, s, buff);
}

#include <stdio.h>
#include <fcntl.h>
int     main(int argc, char **argv)
{
    int     fd;
    char    *line;
    int     x = 1;
	int		time = 101;
    if (argc > 1)
    {
        fd = open(argv[1], O_RDONLY);
       while (x == 1)
        {
			/*if (time < 1)
			{
				while (1)
				{
				}
			}*/
            x = get_next_line(fd, &line);
            if (x > 0)
                printf("%s\n", line);
			//time--;
        }
		free(line);
        close(fd);
    }
	while (1)
	{}
    return (0);
}
