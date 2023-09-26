/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennacir <rennacir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:15:11 by rennacir          #+#    #+#             */
/*   Updated: 2023/09/26 17:33:32 by rennacir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_number_of_args(int argc)
{
	if (argc != 2)
		error("Error : Please Check number of arguments\n");
}

void	check_extension(char **argv)
{
	char	*extension;

	extension = argv[1] + ft_strlen(argv[1]) - 4;
	if (ft_strcmp(extension, ".cub"))
		error("Error : Please Check the extension\n");
}

char	**read_map(char **argv, int count)
{
	char	**map;
	char	*gnl;
	int		fd;
	int		i;

	i = 0;
	fd = open (argv[1], O_RDONLY);
	if (fd < 0)
		error("Error : Please choose an existing map\n");
	map = malloc(sizeof(char *) * (count + 1));
	if (!map)
		return (NULL);
	gnl = get_next_line(fd);
	while (gnl)
	{
		map[i] = gnl;
		i++;
		gnl = get_next_line(fd);
	}
	map[i] = NULL;
	return (map);
}

int	count_lines(int fd)
{
	char	*gnl;
	int		count;

	count = 0;
	gnl = get_next_line(fd);
	while (gnl)
	{
		count++;
		free(gnl);
		gnl = get_next_line(fd);
	}
	return (count);
}

char	**get_map(char **argv)
{
	int		fd;
	int		count;
	char	**map;

	count = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error("Error : Please choose an existing map\n");
	count = count_lines(fd);
	close(fd);
	map = read_map(argv, count);
	return (map);
}
