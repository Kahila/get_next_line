/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalombo <akalombo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:51:47 by akalombo          #+#    #+#             */
/*   Updated: 2019/07/01 11:38:45 by akalombo         ###   ########.fr       */
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
	static char *temp;
	char *buff;
	size_t i;
	size_t j = 0;
	int f;

	i = 0;
	//line = (char **)malloc(sizeof(char *));
	temp = ft_strnew(BUFF_SIZE);
	buff = ft_strnew(BUFF_SIZE);
	f = read(fd, buff, BUFF_SIZE);
	temp = ft_strcpy(temp, buff);
	while (f > 0)
	{
		if (i == BUFF_SIZE)
		{
			i = 0;
			f = read(fd, buff, BUFF_SIZE);
			if(f == 0)
				break;
			temp = ft_strjoin(temp, buff);
			j++;
		}
		i++;
	}
	printf("%s\n", temp);
	line = ft_strsplit(temp, '\n');

	i = 0;
	f = 0;
	while(temp[i] != '\0')
	{
		if (temp[i] == '\n')
			f++;
		i++;
	}
	printf("#lines = %d\n", f);
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
	//printf("%s\n", txt);
	get_next_line(i, &txt);
	get_next_line(i, &txt);
	//printf("%d\n", get_next_line(i, &txt));
	return (0);
}
