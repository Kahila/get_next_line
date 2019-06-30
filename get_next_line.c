/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalombo <akalombo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:51:47 by akalombo          #+#    #+#             */
/*   Updated: 2019/06/30 14:16:24 by akalombo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>


size_t			find_line(char *str)
{
	size_t count;

	count = 0;
	while (str[count] != '\n')
		count++;
	return (count);
}

int			get_next_line(const int fd, char **line)
{
	char *temp;
	char *buff;
	size_t i;
	size_t j;

	i = 0;
	line = (char **)malloc(sizeof(char *));
	temp = ft_strnew(BUFF_SIZE);
	buff = ft_strnew(BUFF_SIZE);
	read(fd, buff, BUFF_SIZE);
	temp = ft_strjoin(temp, buff);
	while (buff[i] != '\n')
	{
		if (i == BUFF_SIZE)
		{
			i = -1;
			read(fd, buff, BUFF_SIZE);
			temp = ft_strjoin(temp, buff);
		}
		i++;
	}
	j = find_line(temp);
	*line = ft_memalloc(sizeof(char) * j + 1);
	ft_strncpy(*line, temp, j);
	printf("%s\n", *line);
	free(buff);
	return (1);
}

#include <fcntl.h>
int main()
{
	char *txt;
	int i;
	
	i = open("file.txt", O_RDONLY);
	//printf("%d\n", get_next_line(i, &txt));
	printf("%s\n", txt);
	get_next_line(i, &txt);
	get_next_line(i, &txt);
	//printf("%d\n", get_next_line(i, &txt));
	return (0);
}
