/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_angle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:56:54 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/28 19:07:50 by mouaammo         ###   ########.fr       */
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

	ray_angle = data->myplayer.rotation_angle - (FOV_ANGLE / 2);
	i = 0;
	while (i < data->num_ray)
	{
		casting(ray_angle, data, i);
		ray_angle += FOV_ANGLE / data->num_ray;
		i++;
	}
}
