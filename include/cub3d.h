/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:38:07 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/17 00:06:51 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H 

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <mlx.h>

typedef enum screen_data
{
	UP_KEY				= 126,
	DOWN_KEY			= 125,
	RIGHT_KEY			= 124,
	LEFT_KEY			= 123,
	ON_KEYDOWN			= 2,
	ON_DESTROY			= 17,
	TILE_SIZE			= 32,
	MAP_NUM_ROWS		= 11,
	MAP_NUM_COLS		= 15,
	WINDOW_WIDTH		= MAP_NUM_COLS * TILE_SIZE,
	WINDOW_HEIGHT		= MAP_NUM_ROWS * TILE_SIZE,
	WALL_STRIP_WIDTH	= 1,
	NUM_RAYS			= WINDOW_WIDTH / WALL_STRIP_WIDTH
}t_window_data;

typedef struct player
{
	int				x;
	int				y;
	int				turn_direction;
	int				walk_direction;
	double			rotation_angle;
	int				move_speed;
	double			rotation_speed;
}t_player;

typedef struct ray
{
	int	ray_angle;
	int	wall_hit_x;
	int	wall_hit_y;
	int	distance;
	int	was_hit_vertical;
	int	hit_wall_color;
	int	is_ray_down;
	int	is_ray_up;
	int	is_ray_right;
	int	is_ray_left;
}t_ray;

typedef struct cub3d
{
	void		*mlx;
	void		*win;
	int			grid[MAP_NUM_ROWS][MAP_NUM_COLS];
	float		scale_factor;
	t_player	myplayer;
}t_cub3d;

//map.c functions
int		hasWallAt(int x, int y, t_cub3d *data);
void	render_map(t_cub3d *data);
void	fill_my_map(t_cub3d *data, int array2d[MAP_NUM_ROWS][MAP_NUM_COLS]);
void	initialize_map(t_cub3d *data);

// player functions in c
void	initialize_player(t_cub3d *data);
void	render_player(t_cub3d *data);
void	draw_line(double x0, double y0, double x1, double y1, t_cub3d *data);
int		move_player(int keycode, t_cub3d *data);
void	dd_pixel(double x0, double y0, double x1, double y1, t_cub3d *data, double rotation_speed);
#endif
