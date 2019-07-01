/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalombo <akalombo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:51:47 by akalombo          #+#    #+#             */
/*   Updated: 2019/07/01 16:55:26 by akalombo         ###   ########.fr       */
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
	//printf(">>>>>>>>>>>>>>>>>>>>>>>>|%s|<<<<<<<<<<<<<<<<<<<<<<\n", temp);
	if (j > 0){
		*line = (char *)malloc(sizeof(char ) * j);
		new = ft_memalloc(sizeof(char) * j);
	}
	//j = ft_strlen(temp) - j;
	//while(temp[])
	if (j > 0)
	{
		s = ft_strlen(temp) - j;
		while (temp[s] != '\0' && i != j)
		{
			new[i] = temp[s];
		//	printf("_______________|%s|_______________", new);
			s++;
			i++;

		}
		//printf("\n");
		
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

	if (j > 0)
	{
		s = ft_strlen(temp) - j;
		*line = (char *)malloc(sizeof(char) * (i + j));
		while (temp[s] != '\0' && t != j)
		{
		//	*line = (char *)malloc(sizeof(char) * (i + j))
			line[0][t] = new[t];
		//	printf("_______________|%c|_______________", new[t]);
			//s++;
			t++;

		}
	}
	else
		*line = (char *)malloc(sizeof(char) * i);
	//printf("%s<<<<<<<<<<<<<<", new);
	*line = ft_strncat(*line, temp, i);
//	printf("%d\n", f);
	printf("%s\n", *line);
	free(*line);
	j = ft_strlen(temp) - i;
//	printf("%d\n", j);
	return (1);
}

#include <fcntl.h>
int main()
{
	char *txt;
	int i;
	
	i = open("file.txt", O_RDONLY);
	//printf("%d\n", get_next_line(i, &txt));
	//printf("%s\n", txt);
	get_next_line(i, &txt);
	get_next_line(i, &txt);
	//get_next_line(i, &txt);
	//printf("%d\n", get_next_line(i, &txt));
	return (0);
}
