/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalombo <akalombo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:51:47 by akalombo          #+#    #+#             */
/*   Updated: 2019/06/29 05:01:44 by akalombo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char			*ft_realloc(char *str, char *temp)
{
	char *new;

	new = ft_strjoin(str, temp);
	ft_strdel(&temp);
	//free(str);
	return (new);
}

#include <stdlib.h>

int			get_next_line(const int fd, char **line)
{
	static char *temp;
	size_t i;
	size_t j;
	
	i = 0;
	j = 0;
	line = (char **)malloc(sizeof(char *) * 1 + 1);
	temp = ft_memalloc(BUFF_SIZE);
	read(fd, temp, BUFF_SIZE);
	*line = (char *)malloc(sizeof(char) * BUFF_SIZE + 1);
	ft_strcpy(*line, temp);
	while (line[0][i] != '\0')
	{
		///continiue from here
		while (temp != '\0')
		{
			if (temp == )
		}
		
		i++;
	}
	if (j == 0)
		read(fd, temp, BUFF_SIZE);

	//read(fd, temp, BUFF_SIZE);
	*line = ft_realloc(*line, temp);
	/*while (temp[i] != '\n')
	{
		*line[j] = temp[i];
		i++;
		j++;
		if (i == BUFF_SIZE)
		{
			i = 0;
			read(fd, temp, BUFF_SIZE);
			if (!(realloc(line[0], BUFF_SIZE)))
				exit(INVALID);
			ft_strcat(line[0], temp);
		}
	}*/
	printf("%s\n", *line);
	return (1);
}

#include <fcntl.h>
int main()
{
	char *txt;
	int i;
	
	i = open("file.txt", O_RDONLY);
	printf("%d\n", get_next_line(i, &txt));
	//printf("%d\n", get_next_line(i, &txt));
	return (0);
}
