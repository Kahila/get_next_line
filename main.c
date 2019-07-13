/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalombo <akalombo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 10:28:51 by akalombo          #+#    #+#             */
/*   Updated: 2019/07/13 11:48:57 by akalombo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

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
				if (*line)
					free(line);
			}
		}
		free(line);
		close(fd);
	}
	return (0);
}
