/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalombo <akalombo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:51:47 by akalombo          #+#    #+#             */
/*   Updated: 2019/07/06 22:57:11 by akalombo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#include <stdio.h>

int			get_next_line(const int fd, char **line)
{
	static t_var var;
	char buff[BUFF_SIZE + 1];
	char *new;
	int i;
 	int f = 0;
	int s = 0;
    int w = 0;
    i = 0;

    if (fd <  0 || line == NULL)
        return (INVALID);
    ft_bzero(buff, BUFF_SIZE + 1);
	if (var.j > 0){
		new = ft_memalloc(sizeof(char) * (var.j + 1));
	    if (!new)
            return (INVALID);
		s = ft_strlen(var.temp) - var.j;
		f = s;
        w = var.j;
		while (var.temp[s] != '\0')
		{
			if (var.temp[s] == '\n')
			{
				if(!(*line = ft_memalloc(sizeof(char) * (i + 1))))
                    return (INVALID);
				*line = ft_strncpy(*line, new, i);
				var.j--;
                free(new);
				return (LINE_FOUND);
			}
			new[i] = var.temp[s];
			s++;
			var.j--;
			i++;
		}
		s = f;
        var.temp = ft_strdup(new);
	}
	i = 0;
    if (w == 0)
	    var.temp = ft_strnew(BUFF_SIZE);
	f = read(fd, buff, BUFF_SIZE);
	if (f == 0)
		return (LINE_NOT_FOUND);
	var.temp = ft_strjoin(var.temp, buff);
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
				return (LINE_NOT_FOUND);
            }
			var.temp = ft_strjoin(var.temp, buff);
			i = 0;
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
		*line = (char *)malloc(sizeof(char) * (i + 1));
	*line = ft_strncat(*line, var.temp, i - 1);
	var.j = ft_strlen(var.temp) - i;
	return (LINE_FOUND);
}

#include <stdio.h>
#include <fcntl.h>
/*int main()
{
	char *txt;
	int i;
	int x = 1;
	int j = 0;
	
	i = open("file.txt", O_RDONLY);
	while (j < 9)
	{
		x = get_next_line(i, &txt);
        printf("%s\n", txt);
        j++;
	}
   // free(txt);
	return (0);
}*/

/*int		main(int argc, char **argv)
{
	int		fd;
	char	*line;
    int x = 0;

    if (argc > 1)
    {
	    fd = open(argv[1], O_RDONLY);
    	while ((x = get_next_line(fd, &line)) == 1)
		    printf("%s\n", line);
	    close(fd);
        printf("%s\n", line);
    }
	return (0);
}
*/
