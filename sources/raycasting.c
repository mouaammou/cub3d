/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 01:20:08 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/20 04:12:38 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_cords	x_y_intercept(int flag, t_cub3d *data, int i)
{
	t_cords	result;

	if (flag == 1)
	{
		result.y = floor(data->myplayer.y / TILE_SIZE) * TILE_SIZE;
		result.y += isRayFacingDown(data->myray[i].ray_angle) ? TILE_SIZE : 0;
		result.x = data->myplayer.x + (result.y - data->myplayer.y) / tan(data->myray[i].ray_angle);
	}
	else if (flag == 2)
	{
		result.x = floor(data->myplayer.x / TILE_SIZE) * TILE_SIZE;
		result.x += isRayFacingRight(data->myray[i].ray_angle) ? TILE_SIZE : 0;
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
		ystep *= isRayFacingUp(data->myray[i].ray_angle) ? -1 : 1;

		xstep = TILE_SIZE / tan(data->myray[i].ray_angle);
		xstep *= (isRayFacingLeft(data->myray[i].ray_angle) && xstep > 0) ? -1 : 1;
		xstep *= (isRayFacingRight(data->myray[i].ray_angle) && xstep < 0) ? -1 : 1;
	}
	else if (flag == 2)
	{
		xstep = TILE_SIZE;
		xstep *= isRayFacingLeft(data->myray[i].ray_angle) ? -1 : 1;

		ystep = TILE_SIZE * tan(data->myray[i].ray_angle);
		ystep *= (isRayFacingUp(data->myray[i].ray_angle) && ystep > 0) ? -1 : 1;
		ystep *= (isRayFacingDown(data->myray[i].ray_angle) && ystep < 0) ? -1 : 1;
	}
	return ((t_cords){xstep, ystep});
}

t_cords	horizontal_increment(double nextHorzTouchX, double nextHorzTouchY,t_cub3d *data,
		int *foundHorzWallHit, t_cords result, int i)
{
	t_cords	wall_hit;
	while (isInsideMap(nextHorzTouchX, nextHorzTouchY))
	{
		double xToCheck = nextHorzTouchX;
		double yToCheck = nextHorzTouchY + (isRayFacingUp(data->myray[i].ray_angle) ? -EPSILON : 0);

		if (hasWallAt(xToCheck, yToCheck, data))
		{
			wall_hit.x = nextHorzTouchX;
			wall_hit.y = nextHorzTouchY;
			*foundHorzWallHit = 1;
			break;
		}
		else
		{
			nextHorzTouchX += result.x;
			nextHorzTouchY += result.y;
			wall_hit.x = -1;
			wall_hit.y = -1;
		}
	}
	return (wall_hit);
}

t_cords	vertical_increment(double nextVertTouchX, double nextVertTouchY,t_cub3d *data,
		int *foundVertWallHit, t_cords result, int i)
{
	t_cords	wall_hit;
	
	while (isInsideMap(nextVertTouchX, nextVertTouchY))
	{
		double xToCheck = nextVertTouchX + (isRayFacingLeft(data->myray[i].ray_angle) ? -EPSILON : 0);
		double yToCheck = nextVertTouchY;

		if (hasWallAt(xToCheck, yToCheck, data))
		{
			wall_hit.x = nextVertTouchX;
			wall_hit.y = nextVertTouchY;
			*foundVertWallHit = 1;
			break;
		}
		else
		{
			nextVertTouchX += result.x;
			nextVertTouchY += result.y;
			wall_hit.x = -1;
			wall_hit.y = -1;
		}
	}
	return (wall_hit);
}

void	calcul_distance(t_cords vert, t_cords horz, t_cords found_wall_hit, t_cub3d *data, int i)
{
	double horzHitDistance = found_wall_hit.x
		? distanceBetweenPoints(data->myplayer.x, data->myplayer.y, horz.x, horz.y)
		: FLT_MAX;
	double vertHitDistance = found_wall_hit.y
		? distanceBetweenPoints(data->myplayer.x, data->myplayer.y, vert.x, vert.y)
		: FLT_MAX;

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
		ray_angle += (double)FOV_ANGLE / NUM_RAYS;
		i++;
	}
}
