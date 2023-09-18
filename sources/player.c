/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:37:07 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/18 22:37:25 by mouaammo         ###   ########.fr       */
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
	data->myplayer.rotation_speed = 8 * (M_PI / 180);
	data->myplayer.fov = 60 * (M_PI / 180);
}

void	delete_player(t_cub3d *data ,int background_color)
{
	int	x;
	int	y;

	x = data->myplayer.x;
	y = data->myplayer.y;
	if (hasWallAt(x, y, data) == 1)
		return ;
	put_color(data, x, y, background_color);
	put_color(data, x + 1, y, background_color);
	put_color(data, x, y + 1, background_color);
	put_color(data, x + 1, y + 1, background_color);
}

void	update_position_player(t_cub3d *data)
{
	data->myplayer.rotation_angle += data->myplayer.turn_direction * data->myplayer.rotation_speed;
	double	moveStep = data->myplayer.walk_direction * data->myplayer.move_speed;

	double	newPlayerX = (data->myplayer.x + cos(data->myplayer.rotation_angle) * moveStep);
	double	newPlayerY = (data->myplayer.y + sin(data->myplayer.rotation_angle) * moveStep);
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
		data->myplayer.turn_direction = +1;
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

void	delete_old_position(t_cub3d *data)
{
	double x1, y1;

	x1 = data->myplayer.x + cos(data->myplayer.rotation_angle) * 30;
	y1 = data->myplayer.y + sin(data->myplayer.rotation_angle) * 30;
	draw_line(data->myplayer.x, data->myplayer.y, x1, y1, data, 0x222222);
}

int	move_player(int keycode, t_cub3d *data)
{
	if (keycode == 53)
		exit(0);
	if (keycode == UP_KEY || keycode == DOWN_KEY
		|| keycode == RIGHT_KEY || keycode == LEFT_KEY)
	{
		render_rays(data, 0x222222);
		delete_player(data, 0x222222);
		delete_old_position(data);
		key_pressed(data, keycode);
		update_position_player(data);
		render_player(data);
		key_released(data, keycode);
		render_rays(data, 0xffffff);
	}
	return 0;
}

void	render_player(t_cub3d *data)
{
	double	x;
	double	y;
	double x1, y1;

	x = data->myplayer.x;
	y = data->myplayer.y;
	if (hasWallAt(x, y, data) == 0)
	{
		put_color(data, x, y, 0xFF0000);
		put_color(data, x + 1, y, 0xFF0000);
		put_color(data, x, y + 1, 0xFF0000);
		put_color(data, x + 1, y + 1, 0xFF0000);

		x1 = data->myplayer.x + cos(data->myplayer.rotation_angle) * 30;
		y1 = data->myplayer.y + sin(data->myplayer.rotation_angle) * 30;
		draw_line(data->myplayer.x, data->myplayer.y, x1, y1, data, 0xffffff);
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
		put_color(data, x0, y0, color);
		x0 += x_inc; // increment in x at each step
		y0 += y_inc; // increment in y at each step
		i++;
	}
}
