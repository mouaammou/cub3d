/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennacir <rennacir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:35:11 by rennacir          #+#    #+#             */
/*   Updated: 2023/09/26 19:23:36 by rennacir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*get_next_line(int fd)
{
	int		i;
	int		rd;
	char	c;
	char	*buf;

	i = 0;
	rd = 0;
	buf = malloc(100000);
	if (!buf)
		return (NULL);
	while (1)
	{
		rd = read(fd, &c, 1);
		if (c == '\n' || rd <= 0)
			break ;
		buf[i++] = c;
	}
	buf[i] = '\0';
	if (rd == -1 || (!buf[i - 1] && !rd))
	{
		return (free(buf), NULL);
	}
	return (buf);
}
