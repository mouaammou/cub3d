/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennacir <rennacir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:58:50 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/24 00:11:12 by rennacir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	color_sky(t_cub3d *data)
{
	int i = 0;
	while (i < data->num_ray)
	{
		int a = 0;
		while (a < data->list->win_height / 2)
		{
			put_color(data, i * data->wall_strip_width, a, 0x5DADE2);
			a++;
		}
		i++;
	}
}

void	color_floor(t_cub3d *data)
{
	int i = 0;
	while (i < data->num_ray)
	{
		int a = 0;
		while (a < data->list->win_height / 2)
		{
			put_color(data, i * data->wall_strip_width, a + data->list->win_height / 2, 0xBFC9CA);
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
	while (i < data->num_ray)
	{
		distance = data->myray[i].distance * cos(data->myray[i].ray_angle - data->myplayer.rotation_angle);
		wall3d_distance = (data->list->win_width / 2) / tan(FOV_ANGLE / 2);
		wall3d_height = (TILE_SIZE / distance) * wall3d_distance;

		int a = 0;
		if (data->myray[i].was_hit_vertical)
			color = 0x229954;
		else
			color = 0x7D6608;
		if (wall3d_height >= data->list->win_height)//for test
			wall3d_height = data->list->win_height;
		while (a < wall3d_height)
		{
			put_color(data, i * data->wall_strip_width, a +( data->list->win_height / 2) - (wall3d_height / 2), color);
			a++;
		}
		i++;
	}
}
