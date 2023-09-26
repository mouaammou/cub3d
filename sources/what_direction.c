/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_direction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennacir <rennacir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:19:00 by rennacir          #+#    #+#             */
/*   Updated: 2023/09/26 19:33:42 by rennacir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	up_down_direction(t_cub3d *data, int i, t_texture *tex)
{
	if (is_ray_up(data->myray[i].ray_angle) && !data->myray[i].was_hit_vertical)
	{
		tex->cast_texture = data->texture[0].cast_texture;
		tex->width = data->texture[0].width;
		tex->height = data->texture[0].height;
	}
	else if (is_ray_down(data->myray[i].ray_angle)
		&& !data->myray[i].was_hit_vertical)
	{
		tex->cast_texture = data->texture[1].cast_texture;
		tex->width = data->texture[1].width;
		tex->height = data->texture[1].height;
	}
}

void	left_right_direction(t_cub3d *data, int i, t_texture *tex)
{
	if (is_ray_right(data->myray[i].ray_angle)
		&& data->myray[i].was_hit_vertical)
	{
		tex->cast_texture = data->texture[2].cast_texture;
		tex->width = data->texture[2].width;
		tex->height = data->texture[2].height;
	}
	else if (is_ray_left(data->myray[i].ray_angle)
		&& data->myray[i].was_hit_vertical)
	{
		tex->cast_texture = data->texture[3].cast_texture;
		tex->width = data->texture[3].width;
		tex->height = data->texture[3].height;
	}
}

t_texture	what_direction(t_cub3d *data, int i)
{
	t_texture	tex;

	up_down_direction(data, i, &tex);
	left_right_direction(data, i, &tex);
	return (tex);
}
