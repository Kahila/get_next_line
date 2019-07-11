/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalombo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 09:41:32 by akalombo          #+#    #+#             */
/*   Updated: 2019/07/11 03:50:45 by akalombo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnew(size_t size)
{
	char *str;

	str = ft_memalloc(size + 1);
    ft_bzero(str, size + 1);
	if (!str)
		return (NULL);
	str[ft_strlen(str) + 1] = '\0';
	return (str);
}
