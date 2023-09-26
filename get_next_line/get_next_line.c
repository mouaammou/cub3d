/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennacir <rennacir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:35:11 by rennacir          #+#    #+#             */
/*   Updated: 2023/09/26 15:44:31 by rennacir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char *get_next_line(int fd)
{
	int		i;
	int		rd;
	char	character;
	char	*buffer;

	i = 0;
	rd = 0;
	buffer = malloc(100000);
	if (!buffer)
		return (NULL);
	while ((rd = read(fd, &character, 1)) > 0)
	{
		if (character == '\n')
			break;
		buffer[i++] = character;
	}
	buffer[i] = '\0';
	if (rd == -1 || (!buffer[i - 1] && !rd))
	{
		return (free(buffer), NULL);
	}
	return (buffer);
}
