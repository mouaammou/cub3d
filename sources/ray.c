/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:36:44 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/19 10:52:06 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	initialize_ray(t_cub3d *data, int i)
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

void	construct_ray(t_cub3d *data, double ray_angle, int i)
{
	initialize_ray(data, i);
	data->myray.ray_angle = normalize_ray_angle(ray_angle);
	data->myray.is_ray_down = data->myray.ray_angle > 0 && data->myray.ray_angle < M_PI;
	data->myray.is_ray_up = !data->myray.is_ray_down;

	data->myray.is_ray_left = (data->myray.ray_angle > 0.5 * M_PI && data->myray.ray_angle < 1.5 * M_PI);
	data->myray.is_ray_right = !data->myray.is_ray_left;
}


void	horizontal_intersection(t_cub3d *data, t_raycasting *ray_info, int i)
{
	ray_info->found_horz_hit = 0;
	
	ray_info->first_p_y = floor(data->myplayer.y / TILE_SIZE) * TILE_SIZE;//found the y coordinate of first point
	if (data->myray.is_ray_down)//check if ray is rendering down
		ray_info->first_p_y += TILE_SIZE;
	
	ray_info->first_p_x = data->myplayer.x + (ray_info->first_p_y - data->myplayer.y / tan(data->myray.ray_angle));
	
	ray_info->ystep = TILE_SIZE;//find the ystep to increment the y coordinate
	if (data->myray.is_ray_up)//negative value for move up
		ray_info->ystep *= -1;
	
	ray_info->xstep = TILE_SIZE / tan(data->myray.ray_angle);//find the xstep to increment the x coordinate
	if (data->myray.is_ray_left && ray_info->xstep > 0)
		ray_info->xstep *= -1;
	else if (data->myray.is_ray_right && ray_info->xstep < 0)
		ray_info->xstep *= -1;
}

void	vertical_intersection(t_cub3d *data, t_raycasting *ray_info, int i)
{
	ray_info->found_vert_hit = 0;
	
	ray_info->first_p_x = floor(data->myplayer.x / TILE_SIZE) * TILE_SIZE;//found the x coordinate of first point
	if (data->myray.is_ray_right)//check if ray is rendering left
		ray_info->first_p_x += TILE_SIZE;
	
	//found the y coordinate of first point
	ray_info->first_p_y = data->myplayer.y + (ray_info->first_p_x - data->myplayer.x * tan(data->myray.ray_angle));

	ray_info->xstep = TILE_SIZE;//find the xstep to increment the x coordinate
	if (data->myray.is_ray_left)//negative value for move left
		ray_info->xstep *= -1;
	
	ray_info->ystep = TILE_SIZE * tan(data->myray.ray_angle);//find the xstep to increment the x coordinate
	if (data->myray.is_ray_up && ray_info->ystep > 0)
		ray_info->ystep *= -1;
	if (data->myray.is_ray_down && ray_info->ystep < 0)
		ray_info->ystep *= -1;
}

double	distanceBetweenPoints(double x1, double y1, double x2, double y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void	horizontal_increment(t_cub3d *data, t_distance *horz_dist, int i)
{
	t_raycasting	ray_info;

	horizontal_intersection(data, &ray_info, i);

	while (ray_info.first_p_x >= 0 && ray_info.first_p_x <= WINDOW_WIDTH
		&& ray_info.first_p_y >= 0 && ray_info.first_p_y <= WINDOW_HEIGHT)
	{
		if (hasWallAt(ray_info.first_p_x, ray_info.first_p_y - data->myray.is_ray_up, data) == 1)
		{
			ray_info._x = ray_info.first_p_x;
			ray_info._y = ray_info.first_p_y;
			ray_info.found_horz_hit = 1;
			break;
		}
		ray_info.first_p_x += ray_info.xstep;
		ray_info.first_p_y += ray_info.ystep;
	}

	horz_dist->x = ray_info._x;
	horz_dist->y = ray_info._y;
	if (ray_info.found_horz_hit == 1)
		horz_dist->distance = distanceBetweenPoints(data->myplayer.x, data->myplayer.y, ray_info._x, ray_info._y);
	else
		horz_dist->distance = INT_MAX;
}

void	vertical_increment(t_cub3d *data, t_distance *vert_dist, int i)
{
	t_raycasting	ray_info;
	double			tmp_point;

	vertical_intersection(data, &ray_info, i);

	while (ray_info.first_p_x >= 0 && ray_info.first_p_x <= WINDOW_WIDTH
		&& ray_info.first_p_y >= 0 && ray_info.first_p_y <= WINDOW_HEIGHT)
	{
		tmp_point = ray_info.first_p_x;
		if (data->myray.is_ray_left)
			tmp_point += -1;
		// else if (data->myray.is_ray_right)
		// 	tmp_point += 1;
		if (hasWallAt(tmp_point, ray_info.first_p_y, data) == 1)
		{
			ray_info._x = ray_info.first_p_x;
			ray_info._y = ray_info.first_p_y;
			ray_info.found_vert_hit = 1;
			break;
		}
		ray_info.first_p_x += ray_info.xstep;
		ray_info.first_p_y += ray_info.ystep;
	}

	vert_dist->x = ray_info._x;
	vert_dist->y = ray_info._y;
	if (ray_info.found_vert_hit == 1)
		vert_dist->distance = distanceBetweenPoints(data->myplayer.x, data->myplayer.y, ray_info._x, ray_info._y);
	else
		vert_dist->distance = INT_MAX;
}


void	ray_casting(t_cub3d *data, int i)
{
	t_distance horz_dist, vert_dist;

	horizontal_increment(data, &horz_dist, i);
	
	vertical_increment(data, &vert_dist, i);
	if (vert_dist.distance < horz_dist.distance)
	{
		data->myray.wall_hit_x = vert_dist.x;
		data->myray.wall_hit_y = vert_dist.y;
		data->myray.distance = vert_dist.distance;
		data->myray.was_hit_vertical = 1;
	}
	else
	{
		data->myray.wall_hit_x = horz_dist.x;
		data->myray.wall_hit_y = horz_dist.y;
		data->myray.distance = horz_dist.distance;
		data->myray.was_hit_vertical = 0;
	}
}
