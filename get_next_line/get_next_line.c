/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:35:11 by rennacir          #+#    #+#             */
/*   Updated: 2023/09/27 15:51:17 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*get_next_line(int fd)
{
	char	*join;
	char	*buffer;
	int		bytes;

	join = NULL;
	while (1)
	{
		buffer = malloc (sizeof(char) * 2);
		if (!buffer)
			return (NULL);
		bytes = read(fd, buffer, 1);
		buffer[bytes] = '\0';
		if (buffer[0] == '\n')
		{
			buffer[0] = '\0';
			break ;
		}
		if (bytes <= 0)
			return (free(buffer), join);
		join = ft_strjoin(join, buffer);
	}
	join = ft_strjoin(join, buffer);
	return (join);
}
