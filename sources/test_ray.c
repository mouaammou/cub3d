/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:01:45 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/19 11:33:05 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3d.h"

double	distanceBetweenPoints(double x1, double y1, double x2, double y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double	normalize_ray_angle(double angle) {
	angle = fmod(angle, 2.0 * M_PI);
	if (angle < 0)
		angle += 2.0 * M_PI;
	return angle;
}

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

void castRay(double rayAngle, t_cub3d *data)
{
	rayAngle = normalize_ray_angle(rayAngle);

	double xintercept, yintercept;
	double xstep, ystep;
	int foundHorzWallHit = 0;
	double horzWallHitX = 0;
	double horzWallHitY = 0; 

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

    double nextHorzTouchX = xintercept;
    double nextHorzTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (isInsideMap(nextHorzTouchX, nextHorzTouchY)) {
        double xToCheck = nextHorzTouchX;
        double yToCheck = nextHorzTouchY + (isRayFacingUp(rayAngle) ? -1 : 0);

        if (hasWallAt(xToCheck, yToCheck, data)) {
            // found a wall hit
            horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
            // horzWallTexture = getMapAt((int)floor(yToCheck / TILE_SIZE), (int)floor(xToCheck / TILE_SIZE));
            foundHorzWallHit = 1;
            break;
        } else {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
    }

    ///////////////////////////////////////////
    // VERTICAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    int foundVertWallHit = 0;
    double vertWallHitX = 0;
    double vertWallHitY = 0;
    int vertWallTexture = 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = floor(data->myplayer.x / TILE_SIZE) * TILE_SIZE;
    xintercept += isRayFacingRight(rayAngle) ? TILE_SIZE : 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    yintercept = data->myplayer.y + (xintercept - data->myplayer.x) * tan(rayAngle);

    // Calculate the increment xstep and ystep
    xstep = TILE_SIZE;
    xstep *= isRayFacingLeft(rayAngle) ? -1 : 1;

    ystep = TILE_SIZE * tan(rayAngle);
    ystep *= (isRayFacingUp(rayAngle) && ystep > 0) ? -1 : 1;
    ystep *= (isRayFacingDown(rayAngle) && ystep < 0) ? -1 : 1;

    double nextVertTouchX = xintercept;
    double nextVertTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (isInsideMap(nextVertTouchX, nextVertTouchY)) {
        double xToCheck = nextVertTouchX + (isRayFacingLeft(rayAngle) ? -1 : 0);
        double yToCheck = nextVertTouchY;

        if (hasWallAt(xToCheck, yToCheck, data)) {
            // found a wall hit
            vertWallHitX = nextVertTouchX;
            vertWallHitY = nextVertTouchY;
            // vertWallTexture = getMapAt((int)floor(yToCheck / TILE_SIZE), (int)floor(xToCheck / TILE_SIZE));
            foundVertWallHit = 1;
            break;
        } else {
            nextVertTouchX += xstep;
            nextVertTouchY += ystep;
        }
    }

    // Calculate both horizontal and vertical hit distances and choose the smallest one
    double horzHitDistance = foundHorzWallHit
        ? distanceBetweenPoints(data->myplayer.x, data->myplayer.y, horzWallHitX, horzWallHitY)
        : FLT_MAX;
    double vertHitDistance = foundVertWallHit
        ? distanceBetweenPoints(data->myplayer.x, data->myplayer.y, vertWallHitX, vertWallHitY)
        : FLT_MAX;

    if (vertHitDistance < horzHitDistance) {
        data->myray.distance = vertHitDistance;
        data->myray.wall_hit_x = vertWallHitX;
        data->myray.wall_hit_y = vertWallHitY;
        // data->myray.texture = vertWallTexture;
        data->myray.was_hit_vertical = 1;
        data->myray.ray_angle = rayAngle;
    } else {
        data->myray.distance = horzHitDistance;
        data->myray.wall_hit_x = horzWallHitX;
        data->myray.wall_hit_y = horzWallHitY;
        // data->myray.texture = horzWallTexture;
        data->myray.was_hit_vertical = 0;
        data->myray.ray_angle = rayAngle;
    }
}

void	render_rays(t_cub3d *data)
{
	double ray_angle = data->myplayer.rotation_angle - (FOV_ANGLE / 2);
	
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
