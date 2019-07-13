/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalombo <akalombo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 11:18:19 by akalombo          #+#    #+#             */
/*   Updated: 2019/07/13 11:44:07 by akalombo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char				*read_line(ssize_t f, int fd, char *buff, char *temp)
{
	int		i;
	char	*tmp;

	i = 0;
	while (f > 0)
	{
		if (buff[i] == '\n')
			break ;
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

static int				check(char **line, t_var *var, int s)
{
	char		*new;
	ssize_t		w;

	w = 0;
	if (*line)
		free(*line);
	s = ft_strlen(var->temp) - var->j;
	new = ft_memalloc(sizeof(char) * (var->j + 1));
	while (var->temp[s] != '\0')
	{
		new[w] = var->temp[s];
		if (var->temp[s++] == '\n')
		{
			if (var->j-- && (*line = ft_memalloc(sizeof(char) * (w + 1))))
				*line = ft_strncpy(*line, new, w);
			free(new);
			return (0);
		}
		w++;
		var->j--;
	}
	free(var->temp);
	var->temp = ft_strdup(new);
	free(new);
	return (w);
}

static int				gnl(ssize_t i, int fd, char *buff, char **line)
{
	static t_var	var;
	char			*v;

	if (var.j > 0 && (i = check(line, &var, i)) == 0)
		return (LINE_FOUND);
	if (i == 0 || (i == 0 && var.temp))
	{
		free(var.temp);
		var.temp = ft_memalloc(sizeof(char) * (BUFF_SIZE + 1));
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
	i = ft_find_len(var.temp, '\n');
	if (var.j == 0 && (*line = ft_memalloc(sizeof(char) * (++i + 1))))
		*line = ft_strncat(*line, var.temp, i - 1);
	var.j = ft_strlen(var.temp) - i;
	return (LINE_FOUND);
}

int						get_next_line(const int fd, char **line)
{
	ssize_t		i;
	char		buff[BUFF_SIZE + 1];

	i = 0;
	if (fd < 0 || BUFF_SIZE < 1)
		return (INVALID);
	*line = NULL;
	ft_bzero(buff, BUFF_SIZE + 1);
	return (gnl(i, fd, buff, line));
}
