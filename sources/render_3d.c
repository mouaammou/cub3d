/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennacir <rennacir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:58:50 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/25 23:19:19 by rennacir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	color_sky(t_cub3d *data)
{
	int i = 0;
	while (i < data->num_ray)
	{
		int a = 0;
		while (a < WINDOW_HEIGHT / 2)
		{
			put_color(data, i * data->wall_strip_width, a, data->list->C);
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
		while (a < WINDOW_HEIGHT / 2)
		{
			put_color(data, i * data->wall_strip_width, a + WINDOW_HEIGHT / 2, data->list->F);
			a++;
		}
		i++;
	}
}

void	up_down_direction(t_cub3d *data, int i, t_texture *tex)
{
	if (is_ray_up(data->myray[i].ray_angle) && !data->myray[i].was_hit_vertical)
	{
		tex->cast_texture = data->texture[0].cast_texture;
		tex->width = data->texture[0].width;
		tex->height = data->texture[0].height;
	}
	else if (is_ray_down(data->myray[i].ray_angle) && !data->myray[i].was_hit_vertical)
	{
		tex->cast_texture = data->texture[1].cast_texture;
		tex->width = data->texture[1].width;
		tex->height = data->texture[1].height;
	}
}

void	left_right_direction(t_cub3d *data, int i, t_texture *tex)
{
	if (is_ray_right(data->myray[i].ray_angle) && data->myray[i].was_hit_vertical)
	{
		tex->cast_texture = data->texture[2].cast_texture;
		tex->width = data->texture[2].width;
		tex->height = data->texture[2].height;
	}
	else if (is_ray_left(data->myray[i].ray_angle) && data->myray[i].was_hit_vertical)
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

void	get_textures(t_cub3d *data)
{
	int tmp;
	data->texture = malloc(sizeof(t_texture) * 4);
	if (!data->texture)
		error("Error\n");
	data->texture[0].tex = mlx_xpm_file_to_image(data->mlx, data->list->NO, &data->texture[0].width, &data->texture[0].height);
	data->texture[1].tex = mlx_xpm_file_to_image(data->mlx, data->list->SO, &data->texture[1].width, &data->texture[1].height);
	data->texture[2].tex = mlx_xpm_file_to_image(data->mlx, data->list->EA, &data->texture[2].width, &data->texture[2].height);
	data->texture[3].tex = mlx_xpm_file_to_image(data->mlx, data->list->WE, &data->texture[3].width, &data->texture[3].height);
	if (!data->texture[0].tex || !data->texture[1].tex || !data->texture[2].tex || !data->texture[3].tex)
		error("Error \n");
	data->texture[0].cast_texture = (uint32_t *)mlx_get_data_addr(data->texture[0].tex, &tmp, &tmp, &tmp);
	data->texture[1].cast_texture = (uint32_t *)mlx_get_data_addr(data->texture[1].tex, &tmp, &tmp, &tmp);
	data->texture[2].cast_texture = (uint32_t *)mlx_get_data_addr(data->texture[2].tex, &tmp, &tmp, &tmp);
	data->texture[3].cast_texture = (uint32_t *)mlx_get_data_addr(data->texture[3].tex, &tmp, &tmp, &tmp);
}


void	 render_textures(t_cub3d *data)
{
	int i = 0;
	int h3d;
	float	x_in_map;
	double	x_in_texture;
	int	y = 0;
	int color;
	double	y_in_texture;
	double	distance;
	double	wall3d_height;
	double	wall3d_distance;
	color_sky(data);
	color_floor(data);
	t_texture	texture;
	i = 0;

	while (i < data->num_ray)
	{
		texture = what_direction(data, i);

		distance = data->myray[i].distance * cos(data->myray[i].ray_angle - data->myplayer.rotation_angle);
		wall3d_distance = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
		wall3d_height = (TILE_SIZE / distance) * wall3d_distance;
		y = (WINDOW_HEIGHT / 2) - (wall3d_height / 2);
		if (y < 0)
		{
			y = 0;
			h3d = WINDOW_HEIGHT;
		}
		else
			h3d = wall3d_height + (WINDOW_HEIGHT / 2) - (wall3d_height / 2);
		if (data->myray[i].was_hit_vertical)
			x_in_map = (int)data->myray[i].wall_hit_y % TILE_SIZE;
		else
			x_in_map = (int)data->myray[i].wall_hit_x % TILE_SIZE;

		x_in_texture = (double)(x_in_map * texture.width) / TILE_SIZE;
		while (y < h3d)
		{
			int	distance_from_top = y + (wall3d_height / 2) - (WINDOW_HEIGHT / 2);
			y_in_texture = (double)(distance_from_top * texture.height) / wall3d_height;
			color = texture.cast_texture[(int)y_in_texture * texture.width + (int)x_in_texture];
			put_color(data, i, y, color);
			y++;
		}
		i++;
	}
	i = 0;
}

