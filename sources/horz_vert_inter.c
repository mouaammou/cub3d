/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horz_vert_inter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:06:20 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/26 17:21:37 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_cords	horizontal_increment(t_cub3d *data, int *found_hit, t_cords step, int i)
{
	t_cords	wall_hit;
	t_cords	check;

	while (is_in_map(data, data->pos.x, data->pos.y))
	{
		check.x = data->pos.x;
		check.y = data->pos.y;
		if (is_ray_up(data->myray[i].ray_angle))
			check.y = data->pos.y - EPSILON;
		if (has_wall(check.x, check.y, data) == '1')
		{
			wall_hit.x = data->pos.x;
			wall_hit.y = data->pos.y;
			*found_hit = 1;
			break ;
		}
		data->pos.x += step.x;
		data->pos.y += step.y;
	}
	return (wall_hit);
}

t_cords	vertical_increment(t_cub3d *data, int *found_hit, t_cords result, int i)
{
	t_cords	wall_hit;
	t_cords	check;

	while (is_in_map(data, data->pos.x, data->pos.y))
	{
		check.x = data->pos.x;
		check.y = data->pos.y;
		if (is_ray_left(data->myray[i].ray_angle))
			check.x = data->pos.x - EPSILON;
		if (has_wall(check.x, check.y, data) == '1')
		{
			wall_hit.x = data->pos.x;
			wall_hit.y = data->pos.y;
			*found_hit = 1;
			break ;
		}
		data->pos.x += result.x;
		data->pos.y += result.y;
	}
	return (wall_hit);
}
