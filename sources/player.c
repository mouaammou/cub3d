/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:05:39 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/17 01:14:17 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	initialize_player(t_cub3d *data)
{
	data->myplayer.x = WINDOW_WIDTH / 2;
	data->myplayer.y = WINDOW_HEIGHT / 7;
	data->myplayer.turn_direction = 0;
	data->myplayer.walk_direction = 0;
	data->myplayer.rotation_angle = M_PI;
	data->myplayer.move_speed = 8;
	data->myplayer.rotation_speed = 8 * (M_PI / 180);
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
	data->myplayer.rotation_angle += data->myplayer.turn_direction * data->myplayer.rotation_speed;
	double	moveStep = data->myplayer.walk_direction * data->myplayer.move_speed;

	double	newPlayerX = round(data->myplayer.x + cos(data->myplayer.rotation_angle) * moveStep);
	double	newPlayerY = round(data->myplayer.y + sin(data->myplayer.rotation_angle) * moveStep);
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
	double x0, y0;
	double x1, y1;
		
	x0 = data->myplayer.x;
	y0 = data->myplayer.y;
	if (keycode == 53)
		exit(0);
	if (keycode == UP_KEY || keycode == DOWN_KEY
		|| keycode == RIGHT_KEY || keycode == LEFT_KEY)
	{
		delete_player(data, 0x222222);
		x1 = data->myplayer.x + cos(data->myplayer.rotation_angle) * 60;
		y1 = data->myplayer.y + sin(data->myplayer.rotation_angle) * 60;
		draw_line(x0, y0, x1, y1, data, 0x222222);
		key_pressed(data, keycode);
		update(data);
		x1 = data->myplayer.x + cos(data->myplayer.rotation_angle) * 60;
		y1 = data->myplayer.y + sin(data->myplayer.rotation_angle) * 60;
		draw_line(x0, y0, x1, y1, data, 0xffffff);
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

void	draw_line(double x0, double y0, double x1, double y1, t_cub3d *data, int color)
{
	double	dx;
	double	dy;
	double	steps;
	double	x_inc;
	double	y_inc;
	int		i;
	
	dx = x1 - x0;
	dy = y1 - y0;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	x_inc = (dx / (double)steps);
	y_inc = (dy / (double)steps);

	i = 0;
	while (i < steps)
	{
		mlx_pixel_put(data->mlx, data->win, x0, y0, color);
		x0 += x_inc; // increment in x at each step
		y0 += y_inc; // increment in y at each step
		i++;
	}
}
