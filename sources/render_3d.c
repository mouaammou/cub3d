/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:58:50 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/23 01:17:56 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	color_sky(t_cub3d *data)
{
	int i = 0;
	while (i < NUM_RAYS)
	{
		int a = 0;
		while (a < WINDOW_HEIGHT / 2)
		{
			put_color(data->frame, i * WALL_STRIP_WIDTH, a, 0x5DADE2);
			a++;
		}
		i++;
	}
}

void	color_floor(t_cub3d *data)
{
	int i = 0;
	while (i < NUM_RAYS)
	{
		int a = 0;
		while (a < WINDOW_HEIGHT / 2)
		{
			put_color(data->frame, i * WALL_STRIP_WIDTH, a + WINDOW_HEIGHT / 2, 0xBFC9CA);
			a++;
		}
		i++;
	}
}

void	render_cube_3d(t_cub3d *data)
{
	int	i;
	double	distance;
	double	wall3d_height;
	double	wall3d_distance;
	int		color;

	i = 0;
	color_sky(data);
	color_floor(data);
	while (i < NUM_RAYS)
	{
		distance = data->myray[i].distance * cos(data->myray[i].ray_angle - data->myplayer.rotation_angle);
		wall3d_distance = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
		wall3d_height = (TILE_SIZE / distance) * wall3d_distance;

		int a = 0;
		if (data->myray[i].was_hit_vertical)
			color = 0x229954;
		else
			color = 0x7D6608;
		if (wall3d_height >= WINDOW_HEIGHT)//for test
			wall3d_height = WINDOW_HEIGHT;
		while (a < wall3d_height)
		{
			put_color(data->frame, i * WALL_STRIP_WIDTH, a +( WINDOW_HEIGHT / 2) - (wall3d_height / 2), color);
			a++;
		}
		i++;
	}
}
