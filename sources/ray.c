/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:36:44 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/18 22:37:17 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	initialize_ray(t_cub3d *data)
{
	data->myray.wall_hit_x = 0;
	data->myray.wall_hit_y = 0;
	data->myray.distance = 0;
	data->myray.was_hit_vertical = 0;
}

double normalize_ray_angle(double angle) {
	angle = fmod(angle, 2.0 * M_PI);
	if (angle < 0)
		angle += 2.0 * M_PI;
	return angle;
}

void	construct_ray(t_cub3d *data, double ray_angle)
{
	initialize_ray(data);
	data->myray.ray_angle = normalize_ray_angle(ray_angle);
	data->myray.is_ray_down = data->myray.ray_angle > 0 && data->myray.ray_angle < M_PI;
	data->myray.is_ray_up = !data->myray.is_ray_down;

	data->myray.is_ray_left = (data->myray.ray_angle > 0.5 * M_PI && data->myray.ray_angle < 1.5 * M_PI);
	data->myray.is_ray_right = !data->myray.is_ray_left;
}


void	render_rays(t_cub3d *data, int color)
{
	double ray_angle = data->myplayer.rotation_angle - (data->myplayer.fov / 2);
	
	int i = 0;
	while (i < NUM_RAYS)
	{
		construct_ray(data, ray_angle);
		
		ray_casting(data);
		
		draw_line(data->myplayer.x, data->myplayer.y,
			data->myray.wall_hit_x ,
			data->myray.wall_hit_y,
			data, color);
		
		ray_angle += data->myplayer.fov / NUM_RAYS;
		i++;
	}
}

// void horizontal_intersection(t_cub3d *data, double *horizontal_x, double *horizontal_y, double *distance) {
//     // Horizontal intersection calculation code here
//     // Modify horz_x, horz_y, and horz_distance accordingly
// 	double	horz_x;
// 	double	horz_y;
// 	int		found_horz_hit = 0;
// 	double	first_p_x;
// 	double	first_p_y;
// 	double	xstep, ystep;
// 	double	next_point_x;
// 	double	next_point_y;

// 	/*************************************
// 			HORIZONTAL RAY-GRID INTERSECTION CODE
// 	**************************************/
// 	first_p_y = floor(data->myplayer.y / TILE_SIZE) * TILE_SIZE;
// 	if (data->myray.is_ray_down)
// 		first_p_y += TILE_SIZE;

// 	first_p_x = data->myplayer.x + (first_p_y - data->myplayer.y / tan(data->myray.ray_angle));

// 	ystep = TILE_SIZE;
// 	if (data->myray.is_ray_up)
// 		ystep *= -1;
// 	xstep = TILE_SIZE / tan(data->myray.ray_angle);
// 	if (data->myray.is_ray_left && xstep > 0)
// 		xstep *= -1;
// 	if (data->myray.is_ray_right && xstep < 0)
// 		xstep *= -1;
	
// 	next_point_x = first_p_x;
// 	next_point_y = first_p_y;

// 	double	tmp_point;
// 	while (next_point_x >= 0 && next_point_x <= WINDOW_WIDTH
// 		&& next_point_y >= 0 && next_point_y <= WINDOW_HEIGHT)
// 	{
// 		tmp_point = next_point_y;
// 		if (data->myray.is_ray_up)
// 			tmp_point += -1;
// 		if (hasWallAt(next_point_x, next_point_y, data) == 1)
// 		{
// 			horz_x = next_point_x;
// 			horz_y = next_point_y;
// 			found_horz_hit = 1;
// 			break;
// 		}
// 		next_point_x += xstep;
// 		next_point_y += ystep;
// 	}
// }

// void vertical_intersection(t_cub3d *data) {
//     // Vertical intersection calculation code here
//     // Modify vert_x, vert_y, and vert_distance accordingly
// }

void	ray_casting(t_cub3d *data)
{
	double	horz_x;
	double	horz_y;
	int		found_horz_hit = 0;
	double	first_p_x;
	double	first_p_y;
	double	xstep, ystep;
	double	next_point_x;
	double	next_point_y;

	/*************************************
			HORIZONTAL RAY-GRID INTERSECTION CODE
	**************************************/
	first_p_y = floor(data->myplayer.y / TILE_SIZE) * TILE_SIZE;
	if (data->myray.is_ray_down)
		first_p_y += TILE_SIZE;

	first_p_x = data->myplayer.x + (first_p_y - data->myplayer.y / tan(data->myray.ray_angle));

	ystep = TILE_SIZE;
	if (data->myray.is_ray_up)
		ystep *= -1;
	xstep = TILE_SIZE / tan(data->myray.ray_angle);
	if (data->myray.is_ray_left && xstep > 0)
		xstep *= -1;
	if (data->myray.is_ray_right && xstep < 0)
		xstep *= -1;

	next_point_x = first_p_x;
	next_point_y = first_p_y;

	double	tmp_point;
	while (next_point_x >= 0 && next_point_x <= WINDOW_WIDTH
		&& next_point_y >= 0 && next_point_y <= WINDOW_HEIGHT)
	{
		tmp_point = next_point_y;
		if (data->myray.is_ray_up)
			tmp_point += -1;
		if (hasWallAt(next_point_x, tmp_point, data) == 1)
		{
			horz_x = (next_point_x);
			horz_y = (next_point_y);
			found_horz_hit = 1;
			break;
		}
		next_point_x += xstep;
		next_point_y += ystep;
	}

	/*************************************
			VERTICAL RAY-GRID INTERSECTION CODE
	**************************************/
	double	vert_x;
	double	vert_y;
	int		found_vert_hit = 0;

	double first_p_vert_x = floor(data->myplayer.x / TILE_SIZE) * TILE_SIZE;
	if (data->myray.is_ray_right)
		first_p_vert_x += TILE_SIZE;
	double first_p_vert_y = data->myplayer.y + (first_p_vert_x - data->myplayer.x) * tan(data->myray.ray_angle);

	xstep = TILE_SIZE;
	if (data->myray.is_ray_left)
		xstep *= -1;


	ystep = TILE_SIZE * tan(data->myray.ray_angle);
	if (data->myray.is_ray_up && ystep > 0)
		ystep *= -1;
	if (data->myray.is_ray_down && ystep < 0)
		ystep *= -1;

	next_point_x = first_p_vert_x;
	next_point_y = first_p_vert_y;

	while (next_point_x >= 0 && next_point_x <= WINDOW_WIDTH
		&& next_point_y >= 0 && next_point_y <= WINDOW_HEIGHT)
	{
		tmp_point = next_point_x;
		if (data->myray.is_ray_left)
			tmp_point += -1;
		if (hasWallAt(tmp_point, next_point_y, data) == 1)
		{
			vert_x = next_point_x;
			vert_y = next_point_y;
			found_vert_hit = 1;
			break;
		}
		next_point_x += xstep;
		next_point_y += ystep;
	}

	// Calculate both horizontal and vertical distances and choose the smallest value
	double horz_distance = DBL_MAX, vert_distance = DBL_MAX;
	if (found_horz_hit == 1)
		horz_distance = sqrt(pow(horz_x - data->myplayer.x, 2) + pow(horz_y - data->myplayer.y, 2));
	if (found_vert_hit == 1)
		vert_distance = sqrt(pow(vert_x - data->myplayer.x, 2) + pow(vert_y - data->myplayer.y, 2));

	if (vert_distance < horz_distance)
	{
		data->myray.wall_hit_x = (vert_x);
		data->myray.wall_hit_y = (vert_y);
		data->myray.distance = vert_distance;
		data->myray.was_hit_vertical = 1;
	}
	else
	{
		data->myray.wall_hit_x = (horz_x);
		data->myray.wall_hit_y = (horz_y);
		data->myray.distance = horz_distance;
		data->myray.was_hit_vertical = 0;
	}
}
