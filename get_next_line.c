/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalombo <akalombo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:51:47 by akalombo          #+#    #+#             */
/*   Updated: 2019/07/03 15:22:39 by akalombo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int			get_next_line(const int fd, char **line)
{
	static char *temp;
	char *buff;
	char *new;
	size_t i;
	int t = 0;
	static int  j = 0;
 	int f = 0;
	int s = 0;

	i = 0;
	line = (char **)malloc(sizeof(char*) * 1);
	if (j > 0){
		new = ft_memalloc(sizeof(char) * j);
		s = ft_strlen(temp) - j;
		f = s;	
		while (temp[s] != '\0' && i != j)
		{
			if (temp[s] == '\n')
			{
				*line = ft_memalloc(sizeof(char) * i);
				*line = ft_strncpy(*line, new, i - 1);
				printf("%s\n", *line);
				j--;
				return (1);
			}
			new[i] = temp[s];
			s++;
			j--;
			i++;
		}
		s = f;
		*line = (char *)malloc(sizeof(char) * (i + j));
		while (temp[s] != '\0' && t != j)
		{
			line[0][t] = new[t];
			t++;
		}
	}
	i = 0;
	temp = ft_strnew(BUFF_SIZE);
	buff = ft_strnew(BUFF_SIZE);
	f = read(fd, buff, BUFF_SIZE);
	temp = ft_strcpy(temp, buff);;
	while (f > 0)
	{
		if (buff[i] == '\n')
		{
			break;
		}
		if (i == BUFF_SIZE)
		{
			f = read(fd, buff, BUFF_SIZE);
			temp = ft_strjoin(temp, buff);
			i = -1;
		}
		i++;
	}

	i = 0;
	while (temp[i] != '\n')
		i++;
	i++;

	if(j == 0)
		*line = (char *)malloc(sizeof(char) * i);
	*line = ft_strncat(*line, temp, i - 1);
	printf("%s\n", *line);
	free(*line);
	j = ft_strlen(temp) - i;
	return (1);
}

#include <fcntl.h>
int main()
{
	char *txt;
	int i;
	int j = 0;
	
	i = open("bible.txt", O_RDONLY);
	while (i > 0)
	{
		get_next_line(i, &txt);
	}
	return (0);
}
