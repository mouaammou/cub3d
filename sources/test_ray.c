/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:01:45 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/19 10:27:18 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3d.h"

int isRayFacingDown(float angle) {
	return angle > 0 && angle < PI; 
}

int isRayFacingUp(float angle) {
	return !isRayFacingDown(angle);
}

int isRayFacingRight(float angle) {
	return angle < 0.5 * PI || angle > 1.5 * PI;
}

int isRayFacingLeft(float angle) {
	return !isRayFacingRight(angle);
}

int isInsideMap(float x, float y) {
	return (x >= 0 && x <= MAP_NUM_COLS * TILE_SIZE && y >= 0 && y <= MAP_NUM_ROWS * TILE_SIZE);
}

void castRay(float rayAngle, int stripId, t_cub3d *data) {
	rayAngle = normalize_ray_angle(rayAngle);

    float xintercept, yintercept;
    float xstep, ystep;

    ///////////////////////////////////////////
    // HORIZONTAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    int foundHorzWallHit = 0;
    float horzWallHitX = 0;
    float horzWallHitY = 0;
    int horzWallTexture = 0;

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

    float nextHorzTouchX = xintercept;
    float nextHorzTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (isInsideMap(nextHorzTouchX, nextHorzTouchY)) {
        float xToCheck = nextHorzTouchX;
        float yToCheck = nextHorzTouchY + (isRayFacingUp(rayAngle) ? -1 : 0);

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
    float vertWallHitX = 0;
    float vertWallHitY = 0;
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

    float nextVertTouchX = xintercept;
    float nextVertTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (isInsideMap(nextVertTouchX, nextVertTouchY)) {
        float xToCheck = nextVertTouchX + (isRayFacingLeft(rayAngle) ? -1 : 0);
        float yToCheck = nextVertTouchY;

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
    float horzHitDistance = foundHorzWallHit
        ? distanceBetweenPoints(data->myplayer.x, data->myplayer.y, horzWallHitX, horzWallHitY)
        : FLT_MAX;
    float vertHitDistance = foundVertWallHit
        ? distanceBetweenPoints(data->myplayer.x, data->myplayer.y, vertWallHitX, vertWallHitY)
        : FLT_MAX;

    if (vertHitDistance < horzHitDistance) {
        data->myrays[stripId].distance = vertHitDistance;
        data->myrays[stripId].wall_hit_x = vertWallHitX;
        data->myrays[stripId].wall_hit_y = vertWallHitY;
        // data->myrays[stripId].texture = vertWallTexture;
        data->myrays[stripId].was_hit_vertical = 1;
        data->myrays[stripId].ray_angle = rayAngle;
    } else {
        data->myrays[stripId].distance = horzHitDistance;
        data->myrays[stripId].wall_hit_x = horzWallHitX;
        data->myrays[stripId].wall_hit_y = horzWallHitY;
        // data->myrays[stripId].texture = horzWallTexture;
        data->myrays[stripId].was_hit_vertical = 0;
        data->myrays[stripId].ray_angle = rayAngle;
    }
}

void castAllRays(t_cub3d *data)
{
    for (int col = 0; col < NUM_RAYS; col++) {
        // float rayAngle = data->myplayer.rotation_angle + atan((col - NUM_RAYS/2) / DIST_PROJ_PLANE);
		double rayAngle = data->myplayer.rotation_angle - (FOV_ANGLE / 2);
        castRay(rayAngle, col, data);
		draw_line(data->myplayer.x,
            data->myplayer.y,
            data->myrays[col].wall_hit_x,
            data->myrays[col].wall_hit_y,
            data, 0xffffff);
    }
}

// void renderMapRays(t_cub3d *data)
// {
//     for (int i = 0; i < NUM_RAYS; i++) {
// 		draw_line(data->myplayer.x,
//             data->myplayer.y,
//             data->myrays[i].wall_hit_x,
//             data->myrays[i].wall_hit_y,
//             data, 0xffffff);
//     }
// }
