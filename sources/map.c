/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:04:22 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/29 11:45:22 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	initialize_map(t_cub3d *data, t_list *list)
{
	data->mlx = mlx_init();
	data->list = list;
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	data->num_ray = WINDOW_WIDTH;
	data->myray = malloc (sizeof(t_ray) * data->num_ray);
	if (!data->myray)
		return ;
	fill_my_map(data);
	initialize_player(data);
}

void	fill_my_map(t_cub3d *data)
{
	int	i;

	i = -1;
	data->grid = malloc (sizeof(char *) * (data->list->num_row + 1));
	if (!data->grid)
		error("Error : about allocation\n");
	i = -1;
	while (data->list->map[++i])
	{
		data->grid[i] = ft_strdup(data->list->map[i]);
	}
	data->grid[i] = NULL;
}

char	has_wall(double x, double y, t_cub3d *data)
{
	int	map_grid_x;
	int	map_grid_y;

	if (y < 0)
		y = 0;
	if (x < 0)
		x = 0;
	if (x > data->list->win_width || y > data->list->win_height)
		return ('1');
	map_grid_x = floor(x / TILE_SIZE);
	map_grid_y = floor(y / TILE_SIZE);
	if (map_grid_x >= data->list->num_col)
		map_grid_x = data->list->num_col - 1;
	if (map_grid_y >= data->list->num_row)
		map_grid_y = data->list->num_row - 1;
	if (data->grid[map_grid_y][map_grid_x] == '1')
		return ('1');
	else
		return ('0');
}

void	draw_case(t_cub3d *data, int tile_x, int tile_y, int tile_color)
{
	int	i;
	int	j;

	tile_x -= data->map.size / 2;
	tile_y -= data->map.size / 2;
	i = 0;
	while (i < data->map.size)
	{
		j = 0;
		while (j < data->map.size)
		{
			put_color_map(data, (tile_x + i), tile_y + j, tile_color);
			j++;
		}
		i++;
	}
}

void	render_player(t_cub3d *data)
{
	int	x;
	int	y;

	x = (MAP_SIZE / 2);
	y = (MAP_SIZE / 2);
	draw_case(data, x, y, 0xff00000);
}
