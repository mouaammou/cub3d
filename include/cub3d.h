/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:38:07 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/20 15:14:21 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H 

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <mlx.h>
# include <limits.h>
# include <float.h>
# include "../libft/libft.h"

#define FOV_ANGLE (60 * (M_PI / 180))
#define EPSILON 1e-9
#define SCALE_MAP 0.2

typedef enum screen_data
{
	UP_KEY				= 13,
	DOWN_KEY			= 1,
	RIGHT_KEY			= 124,
	LEFT_KEY			= 123,
	A_KEY				= 0,
	D_KEY				= 2,
	ON_KEYDOWN			= 2,
	ON_KEYUP			= 3,
	ON_DESTROY			= 17,
	TILE_SIZE			= 64,
	MAP_NUM_ROWS		= 11,
	MAP_NUM_COLS		= 15,
	WINDOW_WIDTH		= MAP_NUM_COLS * TILE_SIZE,
	WINDOW_HEIGHT		= MAP_NUM_ROWS * TILE_SIZE,
	WALL_STRIP_WIDTH	= 1,
	NUM_RAYS			= WINDOW_WIDTH / WALL_STRIP_WIDTH
}t_window_data;

typedef struct player
{
	int				turn_direction;
	int				walk_direction;
	int				a_flag;
	int				move_speed;
	double			rotation_angle;
	double			x;
	double			y;
	double			rotation_speed;
	
}t_player;

typedef struct s_ray_casting
{
	double	_x;
	double	_y;
	int		found_horz_hit;
	int		found_vert_hit;
	double	first_p_x;
	double	first_p_y;
	double	xstep;
	double	ystep;
}t_raycasting;

typedef struct distance
{
	double	x;
	double	y;
	double	distance;
}t_distance;

typedef struct ray
{
	double	ray_angle;
	double	wall_hit_x;
	double	wall_hit_y;
	double	distance;
	int		was_hit_vertical;
	double	hit_wall_color;
}t_ray;

typedef struct cub3d
{
	void			*mlx;
	void			*win;
	void			*img;
	unsigned int	*frame;
	int			grid[MAP_NUM_ROWS][MAP_NUM_COLS];
	double		scale_factor;
	t_player	myplayer;
	t_ray		myray[NUM_RAYS];
}t_cub3d;

typedef struct x
{
	double x;
	double y;
}t_cords;

//map.c functions
int		hasWallAt(double x, double y, t_cub3d *data);
void	render_map(t_cub3d *data);
void	fill_my_map(t_cub3d *data);
void	initialize_map(t_cub3d *data);

void	right_left_move(t_cub3d *data);

// player functions in c
void	initialize_player(t_cub3d *data);
void	render_player(t_cub3d *data);
void	draw_line(double x0, double y0, double x1, double y1, t_cub3d *data, int color);
int		move_player(int keycode, t_cub3d *data);
void	update_position_player(t_cub3d *data);
int		key_released(int key_code, t_cub3d *data);

//ray.c functions
void	render_rays(t_cub3d *data);
void	ray_casting(t_cub3d *data, int i);

//put color insted of put pixel
void	put_color(t_cub3d *data, int x, int y, int color);
double normalize_ray_angle(double angle);
double	distanceBetweenPoints(double x1, double y1, double x2, double y2);

//test ray
void castRay(double rayAngle, t_cub3d *data, int i);

//normalize angle
double	normalize_ray_angle(double angle);
int		isRayFacingDown(double angle);
int		isRayFacingUp(double angle);
int		isRayFacingRight(double angle);
int		isRayFacingLeft(double angle);
double	distanceBetweenPoints(double x1, double y1, double x2, double y2);
int		isInsideMap(double x, double y);

//render cube 3d projection
void	render_cube_3d(t_cub3d *data);

#endif
