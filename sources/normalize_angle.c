/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_angle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 01:12:49 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/27 15:48:29 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_data(t_cub3d **data)
{
	free_2d_tab((*data)->grid);
	free(*data);
}

double	return_rotation_angle(t_cub3d *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->list->map[i])
	{
		j = 0;
		while (data->list->map[i][j])
		{
			if (data->list->map[i][j] == 'N')
				return (1.5);
			if (data->list->map[i][j] == 'S')
				return (0.5);
			if (data->list->map[i][j] == 'E')
				return (0);
			if (data->list->map[i][j] == 'W')
				return (1);
			j++;
		}
		i++;
	}
	return (4);
}

double	distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

int	is_in_map(t_cub3d *data, double x, double y)
{
	return (x >= 0 && x <= data->list->win_width
		&& y >= 0 && y <= data->list->win_height);
}

double	normalize_ray_angle(double angle)
{
	angle = fmod(angle, 2.0 * M_PI);
	if (angle < 0)
		angle += 2.0 * M_PI;
	return (angle);
}
