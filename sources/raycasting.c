/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:49:02 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/29 13:34:01 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_cords	x_y_intercept(int flag, t_cub3d *data, int i)
{
	t_cords	result;

	result.x = 0;
	result.y = 0;
	if (flag == 1)
	{
		result.y = floor(data->myplayer.y / TILE_SIZE) * TILE_SIZE;
		if (is_ray_down(data->myray[i].ray_angle))
			result.y += TILE_SIZE;
		result.x = data->myplayer.x
			+ (result.y - data->myplayer.y) / tan(data->myray[i].ray_angle);
	}
	else if (flag == 2)
	{
		result.x = floor(data->myplayer.x / TILE_SIZE) * TILE_SIZE;
		if (is_ray_right(data->myray[i].ray_angle))
			result.x += TILE_SIZE;
		result.y = data->myplayer.y
			+ (result.x - data->myplayer.x) * tan(data->myray[i].ray_angle);
	}
	return (result);
}

t_cords	x_y_steps(int flag, t_cub3d *data, int i)
{
	t_cords	step;

	step.x = 0;
	step.y = 0;
	if (flag == 1)
		step = x_step(data, i);
	else if (flag == 2)
		step = y_step(data, i);
	return (step);
}

char	has_wall_ray(double x, double y, t_cub3d *data)
{
	int	map_grid_x;
	int	map_grid_y;

	if (x < 0 || x > data->list->win_width || y < 0
		|| y > data->list->win_height)
		error("Error\n");
	map_grid_x = floor(x / TILE_SIZE);
	map_grid_y = floor(y / TILE_SIZE);
	if (map_grid_x >= data->list->num_col)
		map_grid_x--;
	if (map_grid_y >= data->list->num_row)
		map_grid_y--;
	if (data->grid[map_grid_y][map_grid_x] == '1')
		return ('1');
	else
		return ('0');
}

void	calcul_distance(t_hit hitwall,
	t_cords found_wall_hit, t_cub3d *data, int i)
{
	t_cords	dist;

	dist.x = INT_MAX;
	dist.y = INT_MAX;
	if (found_wall_hit.x)
		dist.x = distance(data->myplayer.x,
				data->myplayer.y, hitwall.horz.x, hitwall.horz.y);
	if (found_wall_hit.y)
		dist.y = distance(data->myplayer.x,
				data->myplayer.y, hitwall.vert.x, hitwall.vert.y);
	if (dist.y < dist.x)
	{
		data->myray[i].distance = dist.y;
		data->myray[i].wall_hit_x = hitwall.vert.x;
		data->myray[i].wall_hit_y = hitwall.vert.y;
		data->myray[i].was_hit_vertical = 1;
	}
	else
	{
		data->myray[i].distance = dist.x;
		data->myray[i].wall_hit_x = hitwall.horz.x;
		data->myray[i].wall_hit_y = hitwall.horz.y;
		data->myray[i].was_hit_vertical = 0;
	}
}

void	casting(double ray_angle, t_cub3d *data, int i)
{
	t_cords	steps;
	t_hit	hitwall;
	t_cords	found_hit;

	found_hit.x = 0;
	found_hit.y = 0;
	data->myray[i].ray_angle = normalize_ray_angle(ray_angle);
	data->pos = x_y_intercept(1, data, i);
	steps = x_y_steps(1, data, i);
	hitwall.horz = horizontal_increment(data, (int *)&found_hit.x, steps, i);
	data->pos = x_y_intercept(2, data, i);
	steps = x_y_steps(2, data, i);
	hitwall.vert = vertical_increment(data, (int *)&found_hit.y, steps, i);
	calcul_distance(hitwall, found_hit, data, i);
}
