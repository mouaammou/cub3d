/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_angle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:56:54 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/26 17:10:06 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_ray_down(double angle)
{
	return (angle > 0 && angle < M_PI);
}

int	is_ray_up(double angle)
{
	return (!is_ray_down(angle));
}

int	is_ray_right(double angle)
{
	return (angle < 0.5 * M_PI || angle > 1.5 * M_PI);
}

int	is_ray_left(double angle)
{
	return (!is_ray_right(angle));
}

void	render_rays(t_cub3d *data)
{
	double	ray_angle;
	int		i;
	t_cords	p0;
	t_cords	p1;

	ray_angle = data->myplayer.rotation_angle - (FOV_ANGLE / 2);
	i = 0;
	while (i < data->num_ray)
	{
		casting(ray_angle, data, i);
		p0.x = data->myplayer.x / TILE_SIZE * data->map.size;
		p0.y = data->myplayer.y / TILE_SIZE * data->map.size;
		p1.x = data->myray[i].wall_hit_x / TILE_SIZE * data->map.size;
		p1.y = data->myray[i].wall_hit_y / TILE_SIZE * data->map.size;
		draw_line(p0, p1, data, 0xff0000);
		ray_angle += FOV_ANGLE / data->num_ray;
		i++;
	}
}
