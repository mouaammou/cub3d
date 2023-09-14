/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:05:39 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/14 17:45:25 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	update_position(t_player *character, t_cub3d *map)
{
	int	move_step;
	int	new_player_x;
	int	new_player_y;

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

void	render_player(int x, int y, t_cub3d *data)
{
	if (hasWallAt(x, y, data) == 0)
	{
		mlx_pixel_put(data->mlx, data->win,
			x + 1 + SIZE ,
			y + SIZE ,
			0xFF0000
		);
		mlx_pixel_put(data->mlx, data->win,
			x - 1 + SIZE ,
			y + SIZE ,
			0xFF0000
		);
		mlx_pixel_put(data->mlx, data->win,
			x + SIZE ,
			y + SIZE ,
			0xFF0000
		);
		mlx_pixel_put(data->mlx, data->win,
			x + SIZE ,
			y + 1 + SIZE ,
			0xFF0000
		);
		mlx_pixel_put(data->mlx, data->win,
			x + SIZE ,
			y - 1 + SIZE ,
			0xFF0000
		);
	}
}
