/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:38:07 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/14 23:38:03 by mouaammo         ###   ########.fr       */
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
	TILE_SIZE				= 32,
	MAP_NUM_ROWS		= 11,
	MAP_NUM_COLS		= 15,
	WINDOW_WIDTH		= MAP_NUM_COLS * TILE_SIZE,
	WINDOW_HEIGHT		= MAP_NUM_ROWS * TILE_SIZE,
	WALL_STRIP_WIDTH	= 1,
	NUM_RAYS			= WINDOW_WIDTH / WALL_STRIP_WIDTH
}t_window_data;


typedef struct player
{
	int		x;
	int		y;
	int		radius;
	int		turn_direction;
	int		walk_direction;
	float	rotation_angle;
	int		move_speed;
	float	rotation_speed;
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
void	update_position(t_player *character, t_cub3d *map);
void	render_player(t_cub3d *data);
void	dd_draw_line(int x0, int y0, int x1, int y1, t_cub3d *data);
#endif
