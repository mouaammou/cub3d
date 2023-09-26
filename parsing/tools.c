/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennacir <rennacir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:23:42 by rennacir          #+#    #+#             */
/*   Updated: 2023/09/26 18:35:20 by rennacir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_list(t_list **list)
{
	free_2d_tab((*list)->map);
	free((*list)->NO);
	free((*list)->WE);
	free((*list)->EA);
	free((*list)->SO);
	free((*list));
}

void	error(	char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

void	free_data(t_cub3d **data)
{
	free_2d_tab((*data)->grid);
}

int	*return_dim(char **map)
{
	int	row;
	int	col;
	int	*dim;

	row = 0;
	dim = NULL;
	dim = malloc(8);
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (map[row][col] == 'N' || map[row][col] == 'S'
				|| map[row][col] == 'E' || map[row][col] == 'W')
			{
				dim[0] = row;
				dim[1] = col;
				return (dim);
			}
			col++;
		}
		row++;
	}
	return (dim);
}

int	check_four_sides(char **map, int i, int j)
{
	if (map[i][j - 1] == ' ' || map[i][j + 1] == ' '
		|| map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
		return (0);
	return (1);
}
