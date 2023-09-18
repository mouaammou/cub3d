#include <math.h>
#include <float.h>

#define TILE_SIZE 32
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef struct {
    double x;
    double y;
    double radius;
    int turnDirection; // -1 if left, +1 if right
    int walkDirection; // -1 if back, +1 if front
    double rotationAngle;
    double moveSpeed;
    double rotationSpeed;
} Player;

typedef struct {
    // Define the grid and wall detection functions here if needed
    // Function signature: int getWallContentAt(double x, double y);
} Grid;

typedef struct {
    double wallHitX;
    double wallHitY;
    double distance;
    int hitWallColor;
    int wasHitVertical;
} Ray;

Ray cast(Player *player, Grid grid, double rayAngle) {
    double xintercept, yintercept;
    double xstep, ystep;

    ///////////////////////////////////////////
    // HORIZONTAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    int foundHorzWallHit = 0;
    double horzWallHitX = 0;
    double horzWallHitY = 0;
    int horzWallColor = 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    yintercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
    yintercept += player->walkDirection == 1 ? TILE_SIZE : 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = player->x + (yintercept - player->y) / tan(rayAngle);

    // Calculate the increment xstep and ystep
    ystep = TILE_SIZE;
    ystep *= player->walkDirection == -1 ? -1 : 1;

    xstep = TILE_SIZE / tan(rayAngle);
    xstep *= (player->turnDirection == -1 && xstep > 0) ? -1 : 1;
    xstep *= (player->turnDirection == 1 && xstep < 0) ? -1 : 1;

    double nextHorzTouchX = xintercept;
    double nextHorzTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextHorzTouchX >= 0 && nextHorzTouchX <= WINDOW_WIDTH
		&& nextHorzTouchY >= 0 && nextHorzTouchY <= WINDOW_HEIGHT) {
        int wallGridContent = grid.getWallContentAt(
            nextHorzTouchX,
            nextHorzTouchY + (player->walkDirection == -1 ? -1 : 0)
        );
        if (wallGridContent != 0) {
            foundHorzWallHit = 1;
            horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
            horzWallColor = wallGridContent;
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
    int vertWallColor = 0;

    // Find the x-coordinate of the closest vertical grid intersection
    xintercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
    xintercept += player->turnDirection == 1 ? TILE_SIZE : 0;

    // Find the y-coordinate of the closest vertical grid intersection
    yintercept = player->y + (xintercept - player->x) * tan(rayAngle);

    // Calculate the increment xstep and ystep
    xstep = TILE_SIZE;
    xstep *= player->turnDirection == -1 ? -1 : 1;

    ystep = TILE_SIZE * tan(rayAngle);
    ystep *= (player->walkDirection == -1 && ystep > 0) ? -1 : 1;
    ystep *= (player->walkDirection == 1 && ystep < 0) ? -1 : 1;

    double nextVertTouchX = xintercept;
    double nextVertTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextVertTouchX >= 0 && nextVertTouchX <= WINDOW_WIDTH && nextVertTouchY >= 0 && nextVertTouchY <= WINDOW_HEIGHT) {
        int wallGridContent = grid.getWallContentAt(
            nextVertTouchX + (player->turnDirection == -1 ? -1 : 0),
            nextVertTouchY
        );
        if (wallGridContent != 0) {
            foundVertWallHit = 1;
            vertWallHitX = nextVertTouchX;
            vertWallHitY = nextVertTouchY;
            vertWallColor = wallGridContent;
            break;
        } else {
            nextVertTouchX += xstep;
            nextVertTouchY += ystep;
        }
    }

    // Calculate both horizontal and vertical distances and choose the smallest value
    double horzHitDistance = (foundHorzWallHit)
        ? sqrt(pow(player->x - horzWallHitX, 2) + pow(player->y - horzWallHitY, 2))
        : DBL_MAX;
    double vertHitDistance = (foundVertWallHit)
        ? sqrt(pow(player->x - vertWallHitX, 2) + pow(player->y - vertWallHitY, 2))
        : DBL_MAX;

    Ray result;
    if (vertHitDistance < horzHitDistance) {
        result.wallHitX = vertWallHitX;
        result.wallHitY = vertWallHitY;
        result.distance = vertHitDistance;
        result.hitWallColor = vertWallColor;
        result.wasHitVertical = 1;
    } else {
        result.wallHitX = horzWallHitX;
        result.wallHitY = horzWallHitY;
        result.distance = horzHitDistance;
        result.hitWallColor = horzWallColor;
        result.wasHitVertical = 0;
    }

    return result;
}
