/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:37:07 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/22 12:34:23 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	initialize_player(t_cub3d *data)
{
	data->myplayer.x = WINDOW_WIDTH / 2;
	data->myplayer.y = WINDOW_HEIGHT / 2;
	data->myplayer.turn_direction = 0;
	data->myplayer.walk_direction = 0;
	data->myplayer.a_flag = 0;
	data->myplayer.rotation_angle = M_PI / 2;
	data->myplayer.move_speed = 4;
	data->myplayer.rotation_speed = 3 * (M_PI / 180);
}

void	update_x_y(t_cub3d *data, t_cords *next, double move_step)
{
	double	angle_1;
	double	angle_2;

	if (data->myplayer.a_flag)
	{
		angle_1 = data->myplayer.rotation_angle + data->myplayer.a_flag * M_PI / 2;
		next->x += data->myplayer.move_speed * cos(angle_1);
		next->y += data->myplayer.move_speed * sin(angle_1);
	}
	else
	{
		angle_2 = data->myplayer.rotation_angle;
		next->x = (data->myplayer.x + cos(angle_2) * move_step);
		next->y = (data->myplayer.y + sin(angle_2) * move_step);
	}
}

void	update_position_player(t_cub3d *data)
{
	double	move_step;
	t_cords	next_cords;

	next_cords.x = data->myplayer.x;
	next_cords.y = data->myplayer.y;
	data->myplayer.rotation_angle += data->myplayer.turn_direction * data->myplayer.rotation_speed;
	move_step = data->myplayer.walk_direction * data->myplayer.move_speed;
	update_x_y(data, &next_cords, move_step);
	if (!hasWallAt(next_cords.x + 3, next_cords.y, data)
		&& !hasWallAt(next_cords.x - 3, next_cords.y, data)
		&& !hasWallAt(next_cords.x, next_cords.y + 3, data)
		&& !hasWallAt(next_cords.x, next_cords.y - 3, data))
	{
		data->myplayer.x = next_cords.x;
		data->myplayer.y = next_cords.y;
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
	if (key_code == UP_KEY || key_code == DOWN_KEY)
		data->myplayer.walk_direction = 0;
	else if (key_code == LEFT_KEY || key_code == RIGHT_KEY)
		data->myplayer.turn_direction = 0;
	else if (key_code == A_KEY || key_code == D_KEY)
		data->myplayer.a_flag = 0;
	return 0;
}

int	move_player(int keycode, t_cub3d *data)
{
	if (keycode == 53)
		exit(0);
	key_pressed(data, keycode);
	return (0);
}

void	render_player(t_cub3d *data)
{
	double	x;
	double	y;

	x = data->myplayer.x;
	y = data->myplayer.y;
	if (hasWallAt(x, y, data) == 0)
		put_color_map(data->frame_map, x, y, 0xFF0000);
}

void	draw_line(t_cords p0, t_cords p1, t_cub3d *data, int color)
{
	t_cords		delta;
	t_cords		inc;
	double		steps;
	int			i;

	delta.x = p1.x - p0.x;
	delta.y = p1.y - p0.y;
	if (fabs(delta.x) > fabs(delta.y))
		steps = fabs(delta.x);
	else
		steps = fabs(delta.y);
	inc.x = (delta.x / steps);
	inc.y = (delta.y / steps);
	i = 0;
	while (i <= steps)
	{
		put_color_map(data->frame_map, p0.x, p0.y, color);
		p0.x += inc.x;
		p0.y += inc.y;
		i++;
	}
}
