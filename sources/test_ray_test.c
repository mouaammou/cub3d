/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ray_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:01:45 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/19 11:26:58 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3d.h"

int isRayFacingDown(double angle) {
	return angle > 0 && angle < M_PI; 
}

int isRayFacingUp(double angle) {
	return !isRayFacingDown(angle);
}

int isRayFacingRight(double angle) {
	return angle < 0.5 * M_PI || angle > 1.5 * M_PI;
}

int isRayFacingLeft(double angle) {
	return !isRayFacingRight(angle);
}

int isInsideMap(double x, double y) {
	return (x >= 0 && x <= MAP_NUM_COLS * TILE_SIZE && y >= 0 && y <= MAP_NUM_ROWS * TILE_SIZE);
}

void	horizontal_intersection(t_cub3d *data, t_raycasting *r, double rayAngle)
{
	rayAngle = normalize_ray_angle(rayAngle);
	
	data->myray.ray_angle = rayAngle;

	double xintercept, yintercept;
	double xstep, ystep;

	///////////////////////////////////////////
	// HORIZONTAL RAY-GRID INTERSECTION CODE
	///////////////////////////////////////////

	// Find the y-coordinate of the closest horizontal grid intersection
	yintercept = floor(data->myplayer.y / TILE_SIZE) * TILE_SIZE;
	yintercept += isRayFacingDown(rayAngle) ? TILE_SIZE : 0;

	// Find the x-coordinate of the closest horizontal grid intersection
	xintercept = data->myplayer.x + (yintercept - data->myplayer.y) / tan(rayAngle);

	// Calculate the increment xstep and ystep
	ystep = TILE_SIZE;
	ystep *= isRayFacingUp(rayAngle) ? -1 : 1;

	xstep = TILE_SIZE / tan(rayAngle);
	xstep *= (isRayFacingLeft(rayAngle) && xstep > 0) ? -1 : 1;
	xstep *= (isRayFacingRight(rayAngle) && xstep < 0) ? -1 : 1;

	r->first_p_x = xintercept;
	r->first_p_y = yintercept;
	r->xstep = xstep;
	r->ystep = ystep;
	r->found_horz_hit = 0;
}

void	horizontal_increment(t_cub3d *data, t_distance *horz_dist, t_raycasting *r)
{
	double nextHorzTouchX = r->first_p_x;
	double nextHorzTouchY = r->first_p_y;

	// Increment xstep and ystep until we find a wall
	while (isInsideMap(nextHorzTouchX, nextHorzTouchY)) {
		double xToCheck = nextHorzTouchX;
		double yToCheck = nextHorzTouchY + (isRayFacingUp(data->myray.ray_angle) ? -1 : 0);

		if (hasWallAt(xToCheck, yToCheck, data)) {
			// found a wall hit
			r->_x = nextHorzTouchX;
			r->_y = nextHorzTouchY;
			r->found_horz_hit = 1;
			break;
		} else {
			nextHorzTouchX += r->xstep;
			nextHorzTouchY += r->ystep;
		}
	}

	horz_dist->distance = r->found_horz_hit
	? distanceBetweenPoints(data->myplayer.x, data->myplayer.y, r->_x, r->_y)
	: FLT_MAX;
}

void	vertical_intersection(t_cub3d *data, t_raycasting *r, double rayAngle) 
{
	///////////////////////////////////////////
	// VERTICAL RAY-GRID INTERSECTION CODE
	///////////////////////////////////////////

	rayAngle = normalize_ray_angle(rayAngle);
	data->myray.ray_angle = rayAngle;

    // Find the x-coordinate of the closest horizontal grid intersection
    r->first_p_x = floor(data->myplayer.x / TILE_SIZE) * TILE_SIZE;
    r->first_p_x += isRayFacingRight(rayAngle) ? TILE_SIZE : 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    r->first_p_y = data->myplayer.y + (r->first_p_x - data->myplayer.x) * tan(rayAngle);

    // Calculate the increment xstep and ystep
    r->xstep = TILE_SIZE;
    r->xstep *= isRayFacingLeft(rayAngle) ? -1 : 1;

    r->ystep = TILE_SIZE * tan(rayAngle);
    r->ystep *= (isRayFacingUp(rayAngle) && r->ystep > 0) ? -1 : 1;
    r->ystep *= (isRayFacingDown(rayAngle) && r->ystep < 0) ? -1 : 1;
	r->found_vert_hit = 0;
}

void	vertical_increment(t_cub3d *data, t_distance *vert_dist, t_raycasting *r)
{
	double nextVertTouchX = r->first_p_x;
	double nextVertTouchY = r->first_p_y;

	// Increment xstep and ystep until we find a wall
	while (isInsideMap(nextVertTouchX, nextVertTouchY)) {
		double xToCheck = nextVertTouchX + (isRayFacingLeft(data->myray.ray_angle) ? -1 : 0);
		double yToCheck = nextVertTouchY;

		if (hasWallAt(xToCheck, yToCheck, data)) {
			// found a wall hit
			r->_x = nextVertTouchX;
			r->_y = nextVertTouchY;
			r->found_vert_hit = 1;
			break;
		} else {
			nextVertTouchX += r->xstep;
			nextVertTouchY += r->ystep;
		}
	}

	vert_dist->distance = r->found_vert_hit
		? distanceBetweenPoints(data->myplayer.x, data->myplayer.y, r->_x, r->_y)
		: FLT_MAX;
}

void castRay(double rayAngle, t_cub3d *data)
{
	t_raycasting r1, r2;
	t_distance	vert_dist, horz_dist;

	horizontal_intersection(data, &r1, rayAngle);
	horizontal_increment(data, &horz_dist, &r1);

	vertical_intersection(data, &r2, rayAngle);
	vertical_increment(data, &vert_dist, &r2);
	
	if (vert_dist.distance < horz_dist.distance) {
		data->myray.distance = vert_dist.distance;
		data->myray.wall_hit_x = r1._x;
		data->myray.wall_hit_y = r1._y;
		// data->myray.texture = vertWallTexture;
		data->myray.was_hit_vertical = 1;
		data->myray.ray_angle = rayAngle;
	} else {
		data->myray.distance = horz_dist.distance;
		data->myray.wall_hit_x = r2.xstep;
		data->myray.wall_hit_y = r2._y;
		// data->myray.texture = horzWallTexture;
		data->myray.was_hit_vertical = 0;
		data->myray.ray_angle = rayAngle;
	}
}

void	render_rays(t_cub3d *data)
{
	double ray_angle = data->myplayer.rotation_angle - (data->myplayer.fov / 2);
	
	int i = 0;

	while (i < NUM_RAYS)
	{
		castRay(ray_angle, data);
		draw_line(data->myplayer.x,
            data->myplayer.y,
            data->myray.wall_hit_x,
            data->myray.wall_hit_y,
            data, 0xffffff);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		i++;
	}
}
