/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:04:22 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/19 09:38:12 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	initialize_map(t_cub3d *data)
{
	// Initialize your grid data->here
	int tmp;
	
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "MiniMap");
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->frame = (unsigned int *)mlx_get_data_addr(data->img, &tmp, &tmp, &tmp);

	fill_my_map(data);
	initialize_player(data);
}

void	fill_my_map(t_cub3d *data)
{
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
	int	i = 0;
	int	j;
	while (i < MAP_NUM_ROWS)
	{
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			data->grid[i][j] = array2D[i][j];
			j++;
		}
		i++;
	}
}

int	hasWallAt(double x, double y, t_cub3d *data)
{
	int	map_grid_x;
	int	map_grid_y;

	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
		return 0;
	map_grid_x = floor(x / TILE_SIZE);
	map_grid_y = floor(y / TILE_SIZE);
	return (data->grid[map_grid_y][map_grid_x]);
}

void	draw_case(t_cub3d *data, int tile_x, int tile_y, int tile_color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			// put_color(data->mlx, data->win,tile_x + i,tile_y + j,tile_color);
			put_color(data, tile_x + i, tile_y + j, tile_color);
			j++;
		}
		i++;
	}
}

void	render_map(t_cub3d *data)
{
	int i, j;
	
	i = 0;
	while (i < MAP_NUM_ROWS)
	{
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			int tile_x = j * TILE_SIZE;
			int tile_y = i * TILE_SIZE;
			int tile_color =  0x222222;

			if (data->grid[i][j] == 1)
				tile_color = 0x2fff001;
			draw_case(data, tile_x, tile_y, tile_color);
			j++;
		}
		i++;
	}
}
