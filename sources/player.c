/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:05:39 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/16 18:08:02 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	initialize_player(t_cub3d *data)
{
	data->myplayer.x = WINDOW_WIDTH / 2;
	data->myplayer.y = WINDOW_HEIGHT / 7;
	data->myplayer.turn_direction = 0;
	data->myplayer.walk_direction = 0;
	data->myplayer.rotation_angle = 0;
	data->myplayer.move_speed = 8;
	data->myplayer.rotation_speed = 4 * (M_PI / 180);
}

void	delete_player(t_cub3d *data ,int background_color)
{
	int	x;
	int	y;

	x = data->myplayer.x;
	y = data->myplayer.y;
	if (hasWallAt(x, y, data) == 1)
		return ;
	mlx_pixel_put(data->mlx, data->win, x, y, background_color);
	mlx_pixel_put(data->mlx, data->win, x + 1, y, background_color);
	mlx_pixel_put(data->mlx, data->win, x, y + 1, background_color);
	mlx_pixel_put(data->mlx, data->win, x + 1, y + 1, background_color);
}

void	update(t_cub3d *data)
{
	printf("rotation speed: %f, turndirection: %d\n", data->myplayer.rotation_speed, data->myplayer.turn_direction);
	data->myplayer.rotation_angle += data->myplayer.turn_direction * data->myplayer.rotation_speed;
	float	moveStep = data->myplayer.walk_direction * data->myplayer.move_speed;

	float	newPlayerX = round(data->myplayer.x + cos(data->myplayer.rotation_angle) * moveStep);
	float	newPlayerY = round(data->myplayer.y + sin(data->myplayer.rotation_angle) * moveStep);

	printf("X= %f, Y= %f, angle: %f\n", newPlayerX, newPlayerY, data->myplayer.rotation_angle);
	if (!hasWallAt(newPlayerX, newPlayerY, data))
	{
		data->myplayer.x = newPlayerX;
		data->myplayer.y = newPlayerY;
	}
}

void	key_pressed(t_cub3d *data, int key_code)
{
	if (key_code == UP_KEY)
		data->myplayer.walk_direction = +1;
	else if (key_code == DOWN_KEY)
		data->myplayer.walk_direction = -1;
	else if (key_code == RIGHT_KEY)
		data->myplayer.turn_direction = 1;
	else if (key_code == LEFT_KEY)
		data->myplayer.turn_direction = -1;
}

void	key_released(t_cub3d *data, int key_code)
{
	if (key_code == UP_KEY)
		data->myplayer.walk_direction = 0;
	else if (key_code == DOWN_KEY)
		data->myplayer.walk_direction = 0;
	else if (key_code == RIGHT_KEY)
		data->myplayer.turn_direction = 0;
	else if (key_code == LEFT_KEY)
		data->myplayer.turn_direction = 0;
}

int	move_player(int keycode, t_cub3d *data)
{
	int x1, y1;
		
	if (keycode == 53)
		exit(0);
	if (keycode == UP_KEY || keycode == DOWN_KEY
		|| keycode == RIGHT_KEY || keycode == LEFT_KEY)
	{
		x1 = data->myplayer.x + cos(data->myplayer.rotation_angle) * 30;
		y1 = data->myplayer.y + sin(data->myplayer.rotation_angle) * 30;
		draw_line(data->myplayer.x, data->myplayer.y, x1, y1, data);
		delete_player(data, 0x222222);
		key_pressed(data, keycode);
		update(data);
		render_player(data);
		key_released(data, keycode);
	}
	return 0;
}

void	render_player(t_cub3d *data)
{
	int	x;
	int	y;

	x = data->myplayer.x;
	y = data->myplayer.y;
	if (hasWallAt(x, y, data) == 0)
	{
		mlx_pixel_put(data->mlx, data->win, x, y, 0xff0000);
		mlx_pixel_put(data->mlx, data->win, x + 1, y, 0xff0000);
		mlx_pixel_put(data->mlx, data->win, x, y + 1, 0xff0000);
		mlx_pixel_put(data->mlx, data->win, x + 1, y + 1, 0xff0000);
	}
}

void	dd_pixel(int x0, int y0, int x1, int y1, t_cub3d *data)
{
	int	i = 0;
	while (i < TILE_SIZE)
	{
		mlx_pixel_put(data->mlx, data->win,x0 + i,y0 + i,0xffffff);
		i++;
	}
}

void	draw_line(double x0, double y0, int x1, int y1, t_cub3d *data)
{
	double	dx;
	double	dy;
	int		steps;
	double	x_inc;
	double	y_inc;
	int		i;
	
	dx = x1 - x0;
	dy = y1 - y0;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	x_inc = round(dx / (double)steps);
	y_inc = round(dy / (double)steps);

	i = 0;
	while (i <= steps)
	{
		mlx_pixel_put(data->mlx, data->win, x0, y0, 0xffffff);
		x0 += x_inc; // increment in x at each step
		y0 += y_inc; // increment in y at each step
		i++;
	}
}
