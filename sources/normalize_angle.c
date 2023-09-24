/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_angle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 01:12:49 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/24 11:42:17 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	distance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int	is_in_map(t_cub3d *data, double x, double y)
{
	return (x >= 0 && x <= data->list->win_width && y >= 0 && y <= data->list->win_height);
}

double	normalize_ray_angle(double angle)
{
	angle = fmod(angle, 2.0 * M_PI);
	if (angle < 0)
		angle += 2.0 * M_PI;
	return angle;
}

int	is_ray_down(double angle)
{
	return angle > 0 && angle < M_PI;
}

int	is_ray_up(double angle)
{
	return !is_ray_down(angle);
}

int	is_ray_right(double angle)
{
	return angle < 0.5 * M_PI || angle > 1.5 * M_PI;
}

int	is_ray_left(double angle)
{
	return !is_ray_right(angle);
}
