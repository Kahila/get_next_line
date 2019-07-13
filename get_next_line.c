/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalombo <akalombo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 11:18:19 by akalombo          #+#    #+#             */
/*   Updated: 2019/07/13 05:59:42 by akalombo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char      *read_line(ssize_t f, int fd, char *buff, char *temp)
{
    int 	i;
	char 	*tmp;

    i = 0;
    while (f > 0)
    {
        if (buff[i] == '\n')
            break;
        else if (i == BUFF_SIZE)
        {
            f = read(fd, buff, BUFF_SIZE);
            if (f == 0)
                return ((char *)LINE_NOT_FOUND);
			tmp = temp;
            temp = ft_strjoin(temp, buff);
			if (tmp)
				free(tmp);
            i = -1;
        }
        i++;
    }
    return (temp);
}

static int         check(char **line, t_var *var, int s)
{
  	char *new;
    ssize_t w;
    
    w = 0;
	if (*line)
		free(*line);
    s = ft_strlen(var->temp) - var->j;
	new = ft_memalloc(sizeof(char) * (var->j + 1));
    while (var->temp[s] != '\0')
    {
        new[w] = var->temp[s];
        if (var->temp[s] == '\n')
        {
            if (var->j--)
			    *line = ft_memalloc(sizeof(char) * (w + 1));
            *line = ft_strncpy(*line, new, w);
			free(new);
            return (0);
        }
        s++;
        w++;
        var->j--;
    }
	free(var->temp);
    var->temp = ft_strdup(new);
	free(new);
    return (w);
}

static int				gnl(int fd, char **line, ssize_t i, int s, char *buff)
{
    static t_var var;
	char *v;

    if (var.j > 0)
    {
        i = check(line, &var ,s);
        if (i == 0)
            return (LINE_FOUND);
    }
    if (i == 0)
	{
		if (var.temp)
			free(var.temp);
        var.temp = ft_memalloc(sizeof(char) * (BUFF_SIZE  + 1));
	}
    if ((i = read(fd, buff, BUFF_SIZE)) == 0)
    {
        free(var.temp);
        return (LINE_NOT_FOUND);
    }
	v = var.temp;
    var.temp = ft_strjoin(var.temp, buff);
	free(v);
    if ((var.temp = read_line(i, fd, buff, var.temp)) == (char *)LINE_NOT_FOUND)
        return (LINE_NOT_FOUND);
    if (var.temp[(s = 0)])
        while (var.temp[s] != '\n')
            s++;
	if (*line && var.j == 0)
		free(*line);
    if (var.j == 0 && (*line = ft_memalloc(sizeof(char) * (++s + 1))))
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

    *line = NULL;
    ft_bzero(buff, BUFF_SIZE + 1);
    if (fd <  0)
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
            x = get_next_line(fd, &line);
            if (x > 0)
			{
                printf("%s\n", line);
			//	free(line);
			//time--;
            if (*line)
                free(line);
            }
        }
	//if (*line)
        free(line);
        close(fd);
    }
    return (0);
}
