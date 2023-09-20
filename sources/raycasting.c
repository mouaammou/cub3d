/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 01:20:08 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/20 12:09:44 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_cords	x_y_intercept(int flag, t_cub3d *data, int i)
{
	t_cords	result;

	if (flag == 1)
	{
		result.y = floor(data->myplayer.y / TILE_SIZE) * TILE_SIZE;
		if (isRayFacingDown(data->myray[i].ray_angle))
			result.y += TILE_SIZE;
		result.x = data->myplayer.x + (result.y - data->myplayer.y) / tan(data->myray[i].ray_angle);
	}
	else if (flag == 2)
	{
		result.x = floor(data->myplayer.x / TILE_SIZE) * TILE_SIZE;
		if (isRayFacingRight(data->myray[i].ray_angle))
			result.x += TILE_SIZE;
		result.y = data->myplayer.y + (result.x - data->myplayer.x) * tan(data->myray[i].ray_angle);
	}
	return (result);
}

t_cords	x_y_steps(int flag, t_cub3d *data, int i)
{
	double	xstep;
	double	ystep;

	if (flag == 1)
	{
		ystep = TILE_SIZE;
		if (isRayFacingUp(data->myray[i].ray_angle))
			ystep *= -1;
		xstep = TILE_SIZE / tan(data->myray[i].ray_angle);
		if (isRayFacingLeft(data->myray[i].ray_angle) && xstep > 0)
			xstep *= -1;
		if (isRayFacingRight(data->myray[i].ray_angle) && xstep < 0)
			xstep *= -1;
	}
	else if (flag == 2)
	{
		xstep = TILE_SIZE;
		if (isRayFacingLeft(data->myray[i].ray_angle))
			xstep *= -1;
		ystep = TILE_SIZE * tan(data->myray[i].ray_angle);
		if (isRayFacingUp(data->myray[i].ray_angle) && ystep > 0)
			ystep *= -1;
		if (isRayFacingDown(data->myray[i].ray_angle) && ystep < 0)
			ystep *= -1;
	}
	return ((t_cords){xstep, ystep});
}

t_cords	horizontal_increment(double nextHorzTouchX, double nextHorzTouchY,t_cub3d *data,
		int *foundHorzWallHit, t_cords step, int i)
{
	t_cords	wall_hit;
	while (isInsideMap(nextHorzTouchX, nextHorzTouchY))
	{
		double xToCheck = nextHorzTouchX;
		double yToCheck = nextHorzTouchY;
		if (isRayFacingUp(data->myray[i].ray_angle))
			yToCheck = nextHorzTouchY - EPSILON;

		if (hasWallAt(xToCheck, yToCheck, data))
		{
			wall_hit.x = nextHorzTouchX;
			wall_hit.y = nextHorzTouchY;
			*foundHorzWallHit = 1;
			break;
		}
		nextHorzTouchX += step.x;
		nextHorzTouchY += step.y;
	}
	return (wall_hit);
}

t_cords	vertical_increment(double nextVertTouchX, double nextVertTouchY,t_cub3d *data,
		int *foundVertWallHit, t_cords result, int i)
{
	t_cords	wall_hit;
	
	while (isInsideMap(nextVertTouchX, nextVertTouchY))
	{
		double xToCheck = nextVertTouchX;
		double yToCheck = nextVertTouchY;
		if (isRayFacingLeft(data->myray[i].ray_angle))
			xToCheck = nextVertTouchX - EPSILON;
		if (hasWallAt(xToCheck, yToCheck, data))
		{
			wall_hit.x = nextVertTouchX;
			wall_hit.y = nextVertTouchY;
			*foundVertWallHit = 1;
			break;
		}
		nextVertTouchX += result.x;
		nextVertTouchY += result.y;
	}
	return (wall_hit);
}

void	calcul_distance(t_cords vert, t_cords horz, t_cords found_wall_hit, t_cub3d *data, int i)
{
	double horzHitDistance = FLT_MAX;
	double vertHitDistance = FLT_MAX;

	if (found_wall_hit.x)
		horzHitDistance = distanceBetweenPoints(data->myplayer.x, data->myplayer.y, horz.x, horz.y);
	if (found_wall_hit.y)
		vertHitDistance = distanceBetweenPoints(data->myplayer.x, data->myplayer.y, vert.x, vert.y);

	if (vertHitDistance < horzHitDistance) {
		data->myray[i].distance = vertHitDistance;
		data->myray[i].wall_hit_x = vert.x;
		data->myray[i].wall_hit_y = vert.y;
		data->myray[i].was_hit_vertical = 1;
	} else {
		data->myray[i].distance = horzHitDistance;
		data->myray[i].wall_hit_x = horz.x;
		data->myray[i].wall_hit_y = horz.y;
		data->myray[i].was_hit_vertical = 0;
	}
}

void	castRay(double rayAngle, t_cub3d *data, int i)
{
	// HORIZONTAL
	int	foundHorzWallHit = 0;
	int foundVertWallHit = 0;
	rayAngle = normalize_ray_angle(rayAngle);
	data->myray[i].ray_angle = rayAngle;

	t_cords	horz_data, vert_data;
	t_cords	steps;
	t_cords	horz_wall_hit, vert_wall_hit;

	horz_data = x_y_intercept(1, data, i);
	steps = x_y_steps(1, data, i);
	horz_wall_hit = horizontal_increment(horz_data.x, horz_data.y, data, &foundHorzWallHit, steps, i);
	
	// VERTICAL
	vert_data =  x_y_intercept(2, data, i);
	steps = x_y_steps(2, data, i);
	vert_wall_hit = vertical_increment(vert_data.x, vert_data.y, data, &foundVertWallHit, steps, i);
	
	// Calculate both horizontal and vertical hit distances and choose the smallest one
	calcul_distance(vert_wall_hit, horz_wall_hit, (t_cords){foundHorzWallHit, foundVertWallHit}, data, i);
}

void	render_rays(t_cub3d *data)
{
	double ray_angle = data->myplayer.rotation_angle - (FOV_ANGLE / 2);
	
	int i = 0;
	while (i < NUM_RAYS)
	{
		castRay(ray_angle, data, i);
		draw_line(data->myplayer.x,
			data->myplayer.y,
			data->myray[i].wall_hit_x,
			data->myray[i].wall_hit_y,
			data, 0xffffff);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		i++;
	}
}
