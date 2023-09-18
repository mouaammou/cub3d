/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:38:07 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/18 06:28:38 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H 

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <mlx.h>
#include <float.h>

typedef enum screen_data
{
	UP_KEY				= 126,
	DOWN_KEY			= 125,
	RIGHT_KEY			= 124,
	LEFT_KEY			= 123,
	ON_KEYDOWN			= 2,
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
	int				move_speed;
	double			rotation_angle;
	double			x;
	double			y;
	double			rotation_speed;
	double			fov;
}t_player;

typedef struct ray
{
	double	ray_angle;
	double	wall_hit_x;
	double	wall_hit_y;
	double	distance;
	int		was_hit_vertical;
	double	hit_wall_color;
	int		is_ray_down;
	int		is_ray_up;
	int		is_ray_right;
	int		is_ray_left;
}t_ray;

typedef struct cub3d
{
	void		*mlx;
	void		*win;
	void		*img;
	unsigned int	*frame;
	int			grid[MAP_NUM_ROWS][MAP_NUM_COLS];
	float		scale_factor;
	t_player	myplayer;
	t_ray		myray;
}t_cub3d;

//map.c functions
int		hasWallAt(double x, double y, t_cub3d *data);
void	render_map(t_cub3d *data);
void	fill_my_map(t_cub3d *data, int array2d[MAP_NUM_ROWS][MAP_NUM_COLS]);
void	initialize_map(t_cub3d *data);

// player functions in c
void	initialize_player(t_cub3d *data);
void	render_player(t_cub3d *data);
void	draw_line(double x0, double y0, double x1, double y1, t_cub3d *data, int color);
int		move_player(int keycode, t_cub3d *data);

//ray.c functions
void	render_rays(t_cub3d *data, int color);
void	ray_casting(t_cub3d *data);

//put color insted of put pixel
void	put_color(t_cub3d *data, int x, int y, uint32_t color);

#endif
