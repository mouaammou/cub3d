/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:37:07 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/21 10:32:58 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	initialize_player(t_cub3d *data)
{
	data->myplayer.x = WINDOW_WIDTH / 2;
	data->myplayer.y = WINDOW_HEIGHT / 7;
	data->myplayer.turn_direction = 0;
	data->myplayer.walk_direction = 0;
	data->myplayer.a_flag = 0;
	
	data->myplayer.rotation_angle = 0;
	data->myplayer.move_speed = 6;
	data->myplayer.rotation_speed = 2 * (M_PI / 180);
}

void	update_position_player(t_cub3d *data)
{
	double	newPlayerX = data->myplayer.x;
	double	newPlayerY = data->myplayer.y;
	data->myplayer.rotation_angle += data->myplayer.turn_direction * data->myplayer.rotation_speed;
	double	moveStep = data->myplayer.walk_direction * data->myplayer.move_speed;
	if (data->myplayer.a_flag)
	{
		newPlayerX += data->myplayer.move_speed * cos(data->myplayer.rotation_angle + data->myplayer.a_flag * M_PI / 2);
		newPlayerY += data->myplayer.move_speed * sin(data->myplayer.rotation_angle + data->myplayer.a_flag * M_PI / 2);
	}
	else
	{
		newPlayerX = (data->myplayer.x + cos(data->myplayer.rotation_angle) * moveStep);
		newPlayerY = (data->myplayer.y + sin(data->myplayer.rotation_angle) * moveStep);
	}
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
	else if (key_code == A_KEY)
		data->myplayer.a_flag = -1;
	else if (key_code == D_KEY)
		data->myplayer.a_flag = +1;
		
}

int	key_released(int key_code, t_cub3d *data)
{
	if (key_code == UP_KEY)
		data->myplayer.walk_direction = 0;
	else if (key_code == DOWN_KEY)
		data->myplayer.walk_direction = 0;
	else if (key_code == RIGHT_KEY)
		data->myplayer.turn_direction = 0;
	else if (key_code == LEFT_KEY)
		data->myplayer.turn_direction = 0;
	else if (key_code == A_KEY || key_code == D_KEY)
		data->myplayer.a_flag = 0;
	return 0;
}

void	right_left_move(t_cub3d *data)
{

}

int	move_player(int keycode, t_cub3d *data)
{
	if (keycode == 53)
		exit(0);
	key_pressed(data, keycode);
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
		put_color_map(data->frame_map, x, y, 0xFF0000);
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
	x_inc = (dx / steps);
	y_inc = (dy / steps);

	i = 0;
	while (i <= steps)
	{
		put_color_map(data->frame_map, (x0), (y0), color);
		x0 += x_inc; // increment in x at each step
		y0 += y_inc; // increment in y at each step
		i++;
	}
}
