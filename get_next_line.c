/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalombo <akalombo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:51:47 by akalombo          #+#    #+#             */
/*   Updated: 2019/07/06 13:56:31 by akalombo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int			get_next_line(const int fd, char **line)
{
	static t_var var;
	char buff[BUFF_SIZE + 1];
	char *new;
	size_t i;
	int t = 0;
 	int f = 0;
	int s = 0;

	i = 0;
    ft_bzero(buff, BUFF_SIZE + 1);
	if (var.j > 0){
		new = ft_memalloc(sizeof(char) * var.j);
		
		s = ft_strlen(var.temp) - var.j;
		f = s;	
		while (var.temp[s] != '\0' && i != var.j)
		{
			if (var.temp[s] == '\n')
			{
				*line = ft_memalloc(sizeof(char) * i);
				*line = ft_strncpy(*line, new, i - 1);
				var.j--;
				return (1);
			}
			new[i] = var.temp[s];
			s++;
			var.j--;
			i++;
		}
		s = f;
		*line = (char *)malloc(sizeof(char) * (i + var.j));
		while (var.temp[s] != '\0' && t != var.j)
		{
			line[0][t] = new[t];
			t++;
		}
	}
	i = 0;
	var.temp = ft_strnew(BUFF_SIZE);
	f = read(fd, buff, BUFF_SIZE);
	if (f == 0)
		return (0);
	var.temp = ft_strcpy(var.temp, buff);;
	while (f > 0)
	{
		if (buff[i] == '\n')
		{
			break;
		}
		if (i == BUFF_SIZE)
		{
			f = read(fd, buff, BUFF_SIZE);
			if (f == 0)
            {
				return (0);
            }
			var.temp = ft_strjoin(var.temp, buff);
			i = -1;
		}
		i++;
	}

	i = 0;
	if (var.temp[i])
	{
		while (var.temp[i] != '\n')
			i++;
	}
	i++;

	if(var.j == 0)
		*line = (char *)malloc(sizeof(char) * i);
	*line = ft_strncat(*line, var.temp, i - 1);
	var.j = ft_strlen(var.temp) - i;
	return (1);
}

#include <fcntl.h>
int main()
{
	char *txt;
	int i;
	int x = 1;
	int j = 0;
	
	i = open("bible.txt", O_RDONLY);
	while (x > 0)
	{
		x = get_next_line(i, &txt);
        printf("%s\n", txt);
	}
   // free(txt);
	return (0);
}
