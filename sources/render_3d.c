/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennacir <rennacir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:49:13 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/26 19:38:41 by rennacir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	color_sky(t_cub3d *data)
{
	int	i;
	int	a;

	i = 0;
	while (i < data->num_ray)
	{
		a = 0;
		while (a < WINDOW_HEIGHT / 2)
		{
			put_color(data, i * data->wall_strip_width, a, data->list->c);
			a++;
		}
		i++;
	}
}

void	color_floor(t_cub3d *data)
{
	int	i;
	int	a;

	i = 0;
	while (i < data->num_ray)
	{
		a = 0;
		while (a < WINDOW_HEIGHT / 2)
		{
			put_color(data, i * data->wall_strip_width, a + WINDOW_HEIGHT / 2,
				data->list->f);
			a++;
		}
		i++;
	}
}

void	get_textures(t_cub3d *data)
{
	int	tmp;

	data->texture = malloc(sizeof(t_texture) * 4);
	if (!data->texture)
		error("Error\n");
	data->texture[0].tex = mlx_xpm_file_to_image(data->mlx,
			data->list->no, &data->texture[0].width, &data->texture[0].height);
	data->texture[1].tex = mlx_xpm_file_to_image(data->mlx,
			data->list->so, &data->texture[1].width, &data->texture[1].height);
	data->texture[2].tex = mlx_xpm_file_to_image(data->mlx,
			data->list->ea, &data->texture[2].width, &data->texture[2].height);
	data->texture[3].tex = mlx_xpm_file_to_image(data->mlx,
			data->list->we, &data->texture[3].width, &data->texture[3].height);
	if (!data->texture[0].tex || !data->texture[1].tex
		|| !data->texture[2].tex || !data->texture[3].tex)
		error("Error \n");
	data->texture[0].cast_texture
		= (uint32_t *)mlx_get_data_addr(data->texture[0].tex, &tmp, &tmp, &tmp);
	data->texture[1].cast_texture
		= (uint32_t *)mlx_get_data_addr(data->texture[1].tex, &tmp, &tmp, &tmp);
	data->texture[2].cast_texture
		= (uint32_t *)mlx_get_data_addr(data->texture[2].tex, &tmp, &tmp, &tmp);
	data->texture[3].cast_texture
		= (uint32_t *)mlx_get_data_addr(data->texture[3].tex, &tmp, &tmp, &tmp);
}

t_cords	texture_codrs(t_cub3d *data, int i, double *wall3d_height, int *max_top)
{
	double		distance;
	double		wall3d_distance;
	t_cords		tex_cords;

	distance = data->myray[i].distance * cos(data->myray[i].ray_angle
			- data->myplayer.rotation_angle);
	wall3d_distance = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
	*wall3d_height = (TILE_SIZE / distance) * wall3d_distance;
	tex_cords.y = (WINDOW_HEIGHT / 2) - (*wall3d_height / 2);
	if (tex_cords.y < 0)
	{
		tex_cords.y = 0;
		*max_top = WINDOW_HEIGHT;
	}
	else
		*max_top = *wall3d_height + (WINDOW_HEIGHT / 2) - (*wall3d_height / 2);
	if (data->myray[i].was_hit_vertical)
		tex_cords.x = (int)data->myray[i].wall_hit_y % TILE_SIZE;
	else
		tex_cords.x = (int)data->myray[i].wall_hit_x % TILE_SIZE;
	return (tex_cords);
}

void	render_textures(t_cub3d *data)
{
	t_var	var;

	var.i = 0;
	color_sky(data);
	color_floor(data);
	while (var.i < data->num_ray)
	{
		var.texture = what_direction(data, var.i);
		var.tex_cods = texture_codrs(data, var.i,
				&var.wall3d_height, &var.max_top);
		var.x_in_texture = (double)(var.tex_cods.x
				* var.texture.width) / TILE_SIZE;
		while (var.tex_cods.y < var.max_top)
		{
			var.d_from_top = var.tex_cods.y + (var.wall3d_height / 2)
				- (WINDOW_HEIGHT / 2);
			var.y_in_texture = (double)(var.d_from_top
					* var.texture.height) / var.wall3d_height;
			var.color = var.texture.cast_texture[(int)var.y_in_texture
				* var.texture.width + (int)var.x_in_texture];
			put_color(data, var.i, var.tex_cods.y, var.color);
			var.tex_cods.y++;
		}
		var.i++;
	}
}
