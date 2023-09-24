/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 01:20:08 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/24 11:45:21 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_cords	x_y_intercept(int flag, t_cub3d *data, int i)
{
	t_cords	result;

	if (flag == 1)
	{
		result.y = floor(data->myplayer.y / TILE_SIZE) * TILE_SIZE;
		if (is_ray_down(data->myray[i].ray_angle))
			result.y += TILE_SIZE;
		result.x = data->myplayer.x + (result.y - data->myplayer.y) / tan(data->myray[i].ray_angle);
	}
	else if (flag == 2)
	{
		result.x = floor(data->myplayer.x / TILE_SIZE) * TILE_SIZE;
		if (is_ray_right(data->myray[i].ray_angle))
			result.x += TILE_SIZE;
		result.y = data->myplayer.y + (result.x - data->myplayer.x) * tan(data->myray[i].ray_angle);
	}
	return (result);
}

t_cords	x_y_steps(int flag, t_cub3d *data, int i)
{
	t_cords	step;

	if (flag == 1)
	{
		step.y = TILE_SIZE;
		if (is_ray_up(data->myray[i].ray_angle))
			step.y *= -1;
		step.x = TILE_SIZE / tan(data->myray[i].ray_angle);
		if (is_ray_left(data->myray[i].ray_angle) && step.x > 0)
			step.x *= -1;
		if (is_ray_right(data->myray[i].ray_angle) && step.x < 0)
			step.x *= -1;
	}
	else if (flag == 2)
	{
		step.x = TILE_SIZE;
		if (is_ray_left(data->myray[i].ray_angle))
			step.x *= -1;
		step.y = TILE_SIZE * tan(data->myray[i].ray_angle);
		if (is_ray_up(data->myray[i].ray_angle) && step.y > 0)
			step.y *= -1;
		if (is_ray_down(data->myray[i].ray_angle) && step.y < 0)
			step.y *= -1;
	}
	return (step);
}

t_cords	horizontal_increment(t_cub3d *data, int *found_hit, t_cords step, int i)
{
	t_cords	wall_hit;
	t_cords	check;

	while (is_in_map(data, data->pos.x, data->pos.y))
	{
		check.x = data->pos.x;
		check.y = data->pos.y;
		if (is_ray_up(data->myray[i].ray_angle))
			check.y = data->pos.y - EPSILON;
		if (has_wall(check.x, check.y, data) == '1')
		{
			wall_hit.x = data->pos.x;
			wall_hit.y = data->pos.y;
			*found_hit = 1;
			break;
		}
		data->pos.x += step.x;
		data->pos.y += step.y;
	}
	return (wall_hit);
}

t_cords	vertical_increment(t_cub3d *data, int *found_hit, t_cords result, int i)
{
	t_cords	wall_hit;
	t_cords	check;

	while (is_in_map(data, data->pos.x, data->pos.y))
	{
		check.x = data->pos.x;
		check.y = data->pos.y;
		if (is_ray_left(data->myray[i].ray_angle))
			check.x = data->pos.x - EPSILON;
		if (has_wall(check.x, check.y, data) == '1')
		{
			wall_hit.x = data->pos.x;
			wall_hit.y = data->pos.y;
			*found_hit = 1;
			break;
		}
		data->pos.x += result.x;
		data->pos.y += result.y;
	}
	return (wall_hit);
}

void	calcul_distance(t_cords vert, t_cords horz, t_cords found_wall_hit, t_cub3d *data, int i)
{
	t_cords	dist;

	dist.x = DBL_MAX;
	dist.y = DBL_MAX;
	if (found_wall_hit.x)
		dist.x = distance(data->myplayer.x, data->myplayer.y, horz.x, horz.y);
	if (found_wall_hit.y)
		dist.y = distance(data->myplayer.x, data->myplayer.y, vert.x, vert.y);

	if (dist.y < dist.x) {
		data->myray[i].distance = dist.y;
		data->myray[i].wall_hit_x = vert.x;
		data->myray[i].wall_hit_y = vert.y;
		data->myray[i].was_hit_vertical = 1;
	} else {
		data->myray[i].distance = dist.x;
		data->myray[i].wall_hit_x = horz.x;
		data->myray[i].wall_hit_y = horz.y;
		data->myray[i].was_hit_vertical = 0;
	}
}

void	casting(double ray_angle, t_cub3d *data, int i)
{
	t_cords	steps;
	t_cords	horz_wall_hit;
	t_cords	vert_wall_hit;
	t_cords	found_hit;

	found_hit.x = 0;
	found_hit.y = 0;
	
	data->myray[i].ray_angle = normalize_ray_angle(ray_angle);
	
	data->pos = x_y_intercept(1, data, i);
	steps = x_y_steps(1, data, i);
	horz_wall_hit = horizontal_increment(data, (int *)&found_hit.x, steps, i);
	
	data->pos =  x_y_intercept(2, data, i);
	steps = x_y_steps(2, data, i);
	vert_wall_hit = vertical_increment(data, (int *)&found_hit.y, steps, i);
	
	calcul_distance(vert_wall_hit, horz_wall_hit, found_hit, data, i);
}


void	render_rays(t_cub3d *data)
{
	double	ray_angle;
	int		i;
	t_cords	p0;
	t_cords	p1;

	ray_angle = data->myplayer.rotation_angle - (FOV_ANGLE / 2);
	i = 0;
	while (i < data->num_ray)
	{
		casting(ray_angle, data, i);

		p0.x = SCALE_MAP * data->myplayer.x;
		p0.y = SCALE_MAP * data->myplayer.y;
		p1.x = SCALE_MAP * data->myray[i].wall_hit_x;
		p1.y = SCALE_MAP * data->myray[i].wall_hit_y;
		
		draw_line(p0, p1, data, 0xffffff);

		ray_angle += FOV_ANGLE / data->num_ray;
		
		i++;
	}
}
