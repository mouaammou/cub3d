/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:37:07 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/29 11:48:19 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	initialize_player(t_cub3d *data)
{
	data->myplayer.x = data->list->player_y * TILE_SIZE + (TILE_SIZE / 2);
	data->myplayer.y = data->list->player_x * TILE_SIZE + (TILE_SIZE / 2);
	data->map.px = data->list->player_y * data->map.size + (data->map.size / 2);
	data->map.py = data->list->player_x * data->map.size + (data->map.size / 2);
	data->myplayer.turn_direction = 0;
	data->myplayer.walk_direction = 0;
	data->myplayer.a_flag = 0;
	data->myplayer.rotation_angle = M_PI * return_rotation_angle(data);
	data->myplayer.move_speed = TILE_SIZE / 10;
	data->myplayer.rotation_speed = 3 * (M_PI / 180);
}

void	update_x_y(t_cub3d *data, t_cords *next, double move_step)
{
	double	angle;

	if (data->myplayer.a_flag)
	{
		angle = data->myplayer.rotation_angle
			+ data->myplayer.a_flag * M_PI / 2;
		next->x += data->myplayer.move_speed * cos(angle);
		next->y += data->myplayer.move_speed * sin(angle);
	}
	else
	{
		angle = data->myplayer.rotation_angle;
		next->x = data->myplayer.x + cos(angle) * move_step;
		next->y = data->myplayer.y + sin(angle) * move_step;
	}
}

void	update_position_player(t_cub3d *data)
{
	double	move_step;
	t_cords	next_cords;

	next_cords.x = data->myplayer.x;
	next_cords.y = data->myplayer.y;
	data->myplayer.rotation_angle += data->myplayer.turn_direction
		* data->myplayer.rotation_speed;
	move_step = data->myplayer.walk_direction * data->myplayer.move_speed;
	update_x_y(data, &next_cords, move_step);
	if (has_wall(next_cords.x + 50, next_cords.y, data) == '0'
		&& has_wall(next_cords.x - 50, next_cords.y, data) == '0'
		&& has_wall(next_cords.x, next_cords.y + 50, data) == '0'
		&& has_wall(next_cords.x, next_cords.y - 50, data) == '0')
	{
		data->myplayer.x = next_cords.x;
		data->myplayer.y = next_cords.y;
		data->map.px = data->myplayer.x / TILE_SIZE * data->map.size;
		data->map.py = data->myplayer.y / TILE_SIZE * data->map.size;
	}
}

int	key_pressed(int key_code, t_cub3d *data)
{
	if (key_code == 53)
		exit(0);
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
	return (0);
}

int	key_released(int key_code, t_cub3d *data)
{
	if (key_code == UP_KEY || key_code == DOWN_KEY)
		data->myplayer.walk_direction = 0;
	else if (key_code == LEFT_KEY || key_code == RIGHT_KEY)
		data->myplayer.turn_direction = 0;
	else if (key_code == A_KEY || key_code == D_KEY)
		data->myplayer.a_flag = 0;
	return (0);
}
