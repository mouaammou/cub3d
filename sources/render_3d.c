/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:58:50 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/20 13:37:54 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	render_cube_3d(t_cub3d *data)
{
	int	i;
	double	distance;
	double	wall3d_height;
	double	wall3d_distance;

	i = 0;
	while (i < NUM_RAYS)
	{
		distance = data->myray[i].distance * cos(data->myray[i].ray_angle - data->myplayer.rotation_angle);
		wall3d_distance = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
		wall3d_height = (TILE_SIZE / distance) * wall3d_distance;
		// draw_line(i * WALL_STRIP_WIDTH, (WINDOW_HEIGHT / 2.0) - (wall3d_height / 2.0), WALL_STRIP_WIDTH, wall3d_height, data, 0xffffff);
		int a = 0;
		while (a < wall3d_height)
		{
			put_color(data, i * WALL_STRIP_WIDTH, a + WINDOW_HEIGHT / 2 - wall3d_height / 2, 0xffffff);
			a++;
		}
		i++;
	}
}
