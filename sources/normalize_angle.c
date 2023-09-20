/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_angle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 01:12:49 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/20 01:18:31 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	distanceBetweenPoints(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int	isInsideMap(double x, double y)
{
	return (x >= 0 && x <= WINDOW_WIDTH && y >= 0 && y <= WINDOW_HEIGHT);
}

double	normalize_ray_angle(double angle)
{
	angle = fmod(angle, 2.0 * M_PI);
	if (angle < 0)
		angle += 2.0 * M_PI;
	return angle;
}

int	isRayFacingDown(double angle)
{
	return angle > 0 && angle < M_PI; 
}

int	isRayFacingUp(double angle)
{
	return !isRayFacingDown(angle);
}

int	isRayFacingRight(double angle)
{
	return angle < 0.5 * M_PI || angle > 1.5 * M_PI;
}

int	isRayFacingLeft(double angle)
{
	return !isRayFacingRight(angle);
}
