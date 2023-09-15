/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:05:39 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/15 22:27:51 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	initialize_player(t_cub3d *data)
{
	data->myplayer.rotation_angle = 0;
	data->myplayer.x = WINDOW_WIDTH / 2;
	data->myplayer.y = WINDOW_HEIGHT / 7;
	data->myplayer.turn_direction = 0;
	data->myplayer.walk_direction = 0;
	data->myplayer.rotation_angle = 0;
	data->myplayer.move_speed = 8;
	data->myplayer.rotation_speed = 0.1 * (M_PI / 180);
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


// void	update_player(t_cub3d *data)
// {
// 	t_player	player;
// 	int			move_step;
// 	int			new_x;
// 	int			new_y;

// 	player = data->myplayer;
	
// 	player.rotation_angle += player.walk_direction * player.rotation_speed * (M_PI / 180);
	
// 	move_step = player.move_speed * player.walk_direction;
	
// 	new_x = player.x + cos(player.rotation_angle) * move_step;
// 	new_y = player.y + sin(player.rotation_angle) * move_step;
	
// 	if (hasWallAt(new_x, new_y, data) == 0)
// 	{
// 		data->myplayer.x = new_x;
// 		data->myplayer.y = new_y;
// 	}
// }

void	update(t_cub3d *data)
{
	
	t_player	player;
	
	player = data->myplayer;
	int x1, y1;

	data->myplayer.rotation_angle += player.turn_direction + player.rotation_speed;
	float	moveStep = player.walk_direction * player.move_speed;

	float	newPlayerX = player.x + cos(player.rotation_angle) * moveStep;
	float	newPlayerY = player.y + sin(player.rotation_angle) * moveStep;

	printf("X= %f, Y= %f, angle: %f\n", newPlayerX, newPlayerY, player.rotation_angle);
	if (!hasWallAt(newPlayerX, newPlayerY, data))
	{
		x1 = data->myplayer.x + cos(data->myplayer.rotation_angle) * 30;
		y1 = data->myplayer.y + sin(data->myplayer.rotation_angle) * 30;
		draw_line(data->myplayer.x, data->myplayer.y, x1, y1, data);
		data->myplayer.x = newPlayerX;
		data->myplayer.y = newPlayerY;
	}
}

void	key_pressed(t_cub3d *data, int key_code)
{
	int	x;
	int	y;
	
	x = data->myplayer.x;
	y = data->myplayer.y;
	data->myplayer.walk_direction = 0;
	data->myplayer.turn_direction = 0;
	if (key_code == UP_KEY)
	{
		data->myplayer.walk_direction = -1;
		// update(data);
		// if (hasWallAt(x, y, data))
		// 	return ;
	}
	else if (key_code == DOWN_KEY)
	{
		data->myplayer.walk_direction = 1;
		// update(data);
		// if (hasWallAt(x, y, data))
		// 	return ;
	}
	else if (key_code == RIGHT_KEY)
	{
		data->myplayer.turn_direction = -1;
		// update(data);
		// if (hasWallAt(x, y, data))
		// 	return ;
	}
	else if (key_code == LEFT_KEY)
	{
		data->myplayer.turn_direction = 1;
		// update(data);
		// if (hasWallAt(x, y, data))
		// 	return ;
	}
}

int	move_player(int keycode, t_cub3d *data)
{
	if (keycode == 53)
		exit(0);
	if (keycode == UP_KEY || keycode == DOWN_KEY
		|| keycode == RIGHT_KEY || keycode == LEFT_KEY)
	{
		delete_player(data, 0x222222);
		key_pressed(data, keycode);
		update(data);
		render_player(data);
	}
	return 0;
}

void	render_player(t_cub3d *data)
{
	int	x;
	int	y;
	int	x1;
	int	y1;

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

void	draw_line(int x0, int y0, int x1, int y1, t_cub3d *data)
{
	int		dx;
	int		dy;
	int		steps;
	float	x_inc;
	float	y_inc;
	int		i;
	
	dx = x1 - x0;
	dy = y1 - y0;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	x_inc = (float)dx / (float)steps;
	y_inc = (float)dy / (float)steps;

	i = 0;
	while (i < steps)
	{
		mlx_pixel_put(data->mlx, data->win, x0, y0, 0xffffff);
		x0 += x_inc; // increment in x at each step
		y0 += y_inc; // increment in y at each step
		i++;
	}
}
