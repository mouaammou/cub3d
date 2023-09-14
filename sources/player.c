/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:05:39 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/14 23:42:00 by mouaammo         ###   ########.fr       */
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
	data->myplayer.move_speed = 3;
	data->myplayer.rotation_speed = 3 * (M_PI / 180);
}

void	update_position(t_player *character, t_cub3d *map)
{
	int	move_step;
	int	new_player_x = 0;
	int	new_player_y = 0;

	character->rotation_angle += character->turn_direction * character->rotation_speed;
	
	move_step = character->walk_direction * character->move_speed;
	new_player_x = character->x + cos(character->rotation_angle) * move_step;
	new_player_x = character->y + sin(character->rotation_angle) * move_step;

	if (!hasWallAt(new_player_x, new_player_y, map))
	{
		character->x = new_player_x;
		character->y = new_player_y;
	}
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

void	dd_draw_line(int x0, int y0, int x1, int y1, t_cub3d *data)
{
}
