/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:34:19 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/14 01:52:27 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int	hasWallAt(int x, int y, int **grid)
{
	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
		return 0;
	//check if the x,y position has the value 1 or 0
	return (grid[y][x] == 1);
}

int	getWallContent(int x, int y, int **grid)
{
	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
		return 0;
	return(grid[y][x]);
}

void render(t_cub3d *data)
{
	int i, j;

	for (i = 0; i < MAP_NUM_ROWS; i++) {
		for (j = 0; j < MAP_NUM_COLS; j++) {
			int tileX = j * SIZE;
			int tileY = i * SIZE;
			int tileColor = data->grid[i][j] != 0 ? 0x222222 : 0xFFFFFF; // Hexadecimal color values

			// Draw the rectangle by filling individual pixels
			for (int x = 0; x < SIZE * data->scale_factor; x++) {
				for (int y = 0; y < SIZE * data->scale_factor; y++) {
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

int main ()
{
	t_cub3d mygrid;

	mygrid.scale_factor = 0.2;
	mygrid.mlx = mlx_init();
	mygrid.win = mlx_new_window(mygrid.mlx, SIZE * MAP_NUM_COLS, SIZE * MAP_NUM_ROWS, "MiniMap");

	// Initialize your grid mygrid here


	int i, j;
	int array2D[MAP_NUM_ROWS][MAP_NUM_COLS] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1},
		{1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
	//fill my grid array with array2d
	i = 0;
	while (i < MAP_NUM_ROWS)
	{
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			mygrid.grid[i][j] = array2D[i][j];
			j++;
		}
		i++;
	}

	
	render(&mygrid);
	mlx_loop(mygrid.mlx);
	return (0);
}
