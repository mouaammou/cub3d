/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 18:50:54 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/28 19:13:03 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_wall(t_cub3d *data, int x, int y)
{
	if (y < 0)
		y = 0;
	if (x < 0)
		x = 0;
	if (x > data->list->num_row * data->map.size
		|| y > data->list->num_col * data->map.size
		|| x < 0 || y < 0)
		return (0);
	if (x >= data->list->num_col)
		x = data->list->num_col - 1;
	if (y >= data->list->num_row)
		y = data->list->num_row - 1;
	if (data->grid[y][x] == '1')
		return (1);
	return (0);
}

void	render_map(t_cub3d *data)
{
	int	i;
	int	j;
	int	start_x;
	int	start_y;
	int	color;

	start_x = (data->myplayer.x * data->map.size / TILE_SIZE) - (MAP_SIZE / 2);
	start_y = (data->myplayer.y * data->map.size / TILE_SIZE) - (MAP_SIZE / 2);
	i = 0;
	while (i < MAP_SIZE)
	{
		j = 0;
		while (j < MAP_SIZE)
		{
			color = 0xc0c0c0;
			if (is_wall(data, (i + start_x) / data->map.size
					, (j + start_y) / data->map.size))
				color = 0x808080;
			put_color_map(data, i, j, color);
			j++;
		}
		i++;
	}
}
