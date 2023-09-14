/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:04:22 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/14 16:56:03 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	hasWallAt(int x, int y, t_cub3d *data)
{
	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
		return 0;
	//check if the x,y position has the value 1 or 0
	return (data->grid[y][x]);
}

void	render_map(t_cub3d *data)
{
	int i, j;

	for (i = 0; i < MAP_NUM_ROWS; i++)
	{
		for (j = 0; j < MAP_NUM_COLS; j++)
		{
			int tileX = j * SIZE;
			int tileY = i * SIZE;
			int tileColor = data->grid[i][j] != 0 ? 0x222222 : 0xFFFFFF; // Hexadecimal color values

			// Draw the rectangle by filling individual pixels
			for (int x = 0; x < SIZE * data->scale_factor; x++)
			{
				for (int y = 0; y < SIZE * data->scale_factor; y++)
				{
					mlx_pixel_put(
						data->mlx, data->win,
						tileX * data->scale_factor + x,
						tileY * data->scale_factor + y,
						tileColor
					);
				}
			}
		}
	}
}
