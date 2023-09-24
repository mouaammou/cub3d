/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:04:22 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/24 11:28:44 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	initialize_map(t_cub3d *data, t_list *list)
{
	data->mlx = mlx_init();
	data->list = list;
	data->win = mlx_new_window(data->mlx, data->list->win_width, data->list->win_height, "cub3d");
	data->wall_strip_width = 1;
	data->num_ray = data->list->win_width / data->wall_strip_width;
	data->myray = malloc (sizeof(t_ray) * data->num_ray);
	if (!data->myray)
		return ;
	fill_my_map(data);
	initialize_player(data);
}

void	fill_my_map(t_cub3d *data)
{
	int	i;
	int	j;

	i = -1;
	data->grid = malloc (sizeof(char *) * (data->list->num_col + 1));
	if (!data->grid)
		puts("haaaa");
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

	if (x < 0 || x > data->list->win_width || y < 0 || y > data->list->win_height)
		return -1;
	map_grid_x = floor(x / TILE_SIZE);
	map_grid_y = floor(y / TILE_SIZE);
	return (data->grid[map_grid_y][map_grid_x]);
}

void	draw_case(t_cub3d *data, int tile_x, int tile_y, int tile_color)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCALE_MAP * TILE_SIZE)
	{
		j = 0;
		while (j < SCALE_MAP * TILE_SIZE)
		{
			put_color_map(data, (tile_x + i), tile_y + j, tile_color);
			j++;
		}
		i++;
	}
}

void	render_map(t_cub3d *data)
{
	int i, j;

	i = 0;
	while (i < data->list->num_row)
	{
		j = 0;
		while (j < data->list->num_col)
		{
			int tile_x = j * TILE_SIZE * SCALE_MAP;
			int tile_y = i * TILE_SIZE * SCALE_MAP;
			int tile_color =  0x222222;

			if (data->grid[i][j] == '1')
				tile_color = 0x2fff001;
			draw_case(data, tile_x, tile_y, tile_color);
			j++;
		}
		i++;
	}
}
