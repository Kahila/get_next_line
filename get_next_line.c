/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaloyi <mbaloyi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:51:47 by akalombo          #+#    #+#             */
/*   Updated: 2019/07/11 05:12:12 by akalombo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char      *read_line(int f, int fd, char *buff, char *temp)
{
    int i;

    i = 0;
    while (f > 0)
    {
        if (buff[i] == '\n'){
            break;
        }
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
    char *new;
    int w;

    w = 0;
    s = ft_strlen(var->temp) - var->j;
    new = ft_memalloc(sizeof(char) * (var->j + 1));
    while (var->temp[s] != '\0' )
    {
        new[w] = var->temp[s];
        if (var->temp[s] == '\n')
        {
            if(var->j--)
            **line = ft_memalloc(sizeof(char) * (w + 1));
            **line = ft_strncpy(**line, new, w);
            return (0);
        }
        s++;
        w++;
        var->j--;
    }
    var->temp = ft_strdup(new);
    return (w);
}

int				gnl(int fd, char **line, int i, int s){
    static t_var var;
    char buff[BUFF_SIZE + 1];

    i = 0;
    ft_bzero(buff, BUFF_SIZE + 1);
    if (var.j > 0)
    {
        i = check(&line, &var ,s);
        if (i == 0)
            return (1);
    }
    if (i == 0 )
        var.temp = ft_memalloc(BUFF_SIZE  + 1);
    if ((i = read(fd, buff, BUFF_SIZE)) == 0)
        return (LINE_NOT_FOUND);
    var.temp = ft_strjoin(var.temp, buff);
    if ((var.temp = read_line(i, fd, buff, var.temp)) == (char *)LINE_NOT_FOUND)
        return (0);
    if (var.temp[(s = 0)])
        while (var.temp[s] != '\n')
            s++;
    s++;
    if(var.j == 0 && (*line = (char *)malloc(sizeof(char) * (s + 1))))
        *line = ft_strncat(*line, var.temp, s - 1);
    var.j = ft_strlen(var.temp) - s;
    return (LINE_FOUND);
}

int			get_next_line(const int fd, char **line)
{
    int i;  
    int s ;

    i = 0;
    s = 0;
    if (fd <  0 || line == NULL)
        return (INVALID);
    return gnl(fd,line,i,s);
}

#include <stdio.h>
#include <fcntl.h>
int     main(int argc, char **argv)
{
    int     fd;
    char    *line;
    int     x = 1;

    if (argc > 1)
    {
        fd = open(argv[1], O_RDONLY);
        while (x == 1)
        {
            x = get_next_line(fd, &line);
            if (x > 0)
                printf("%s\n", line);
        }
        close(fd);
    }
    return (0);
}
