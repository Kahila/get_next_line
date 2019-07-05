/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalombo <akalombo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 11:18:19 by akalombo          #+#    #+#             */
/*   Updated: 2019/07/05 16:16:40 by akalombo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char			*find_line(int i, const int fd, char *buff, char *temp)
{
	int j;

 	j = 0;
	i = read(fd, buff, BUFF_SIZE);
	temp = ft_strdup(buff);
	while (i > 0)
	{
		if (j == BUFF_SIZE)
		{
			i = read(fd, buff, BUFF_SIZE);
			temp = ft_strjoin(temp, buff);
			j = -1;
		}
		if (buff[j] == '\n')
			return (temp);
		j++;
	}
	return (0);
}

char		*line_return(char *temp, char *line)
{
	int i;

	i = 0;
	while (temp[i] != '\n')
		i++;
	line = ft_memalloc(sizeof(char) * (i + 1));
	line = ft_strncat(line, temp, i);
	return (line);
}

char		*check_static(char *temp, char *line)
{
	int i;

	i = 0;
	while (temp[i] != '\n')
		i++;
	if (i == ft_strlen(temp))
		line = ft_strdup(temp);
	else
		line = line_return(temp, line);
	return (line);
}

int			get_next_line(const int fd, char **line)
{
	char buff[BUFF_SIZE + 1];
	static char *temp;
	int i;

	i = 0;
	if (!temp)
	{
		ft_bzero(buff, BUFF_SIZE + 1);
		temp = find_line(i, fd, buff, temp);
		*line = line_return(temp, *line);
		temp = ft_memchr(temp, '\n', ft_strlen(temp));
		temp++;
		return (1);
	}
	else
		*line = check_static(temp, *line);
}

#include <fcntl.h>
int 		main()
{
	int fd;
	char *line;

	fd = open("file.txt", O_RDONLY);
	get_next_line(fd, &line);
	printf("%s\n", line);
	get_next_line(fd, &line);
	printf("%s\n", line);
	return (0);
}
