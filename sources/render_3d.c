/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:49:13 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/27 16:27:03 by mouaammo         ###   ########.fr       */
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
			put_color(data, i, a, data->list->c);
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
			put_color(data, i, a + WINDOW_HEIGHT / 2,
				data->list->f);
			a++;
		}
		i++;
	}
}

void	render_textures(t_cub3d *data)
{
	t_var	var;
	int		i;
	int		color;

	i = 0;
	color_sky(data);
	color_floor(data);
	while (i < data->num_ray)
	{
		var = x_y_textures(data, i);
		while (var.tex_cods.y < var.max_top)
		{
			var.d_from_top = var.tex_cods.y + (var.wall3d_height / 2)
				- (WINDOW_HEIGHT / 2);
			var.x_y_tex.y = (double)(var.d_from_top
					* var.texture.height) / var.wall3d_height;
			color = var.texture.cast_texture[(int)var.x_y_tex.y
				* var.texture.width + (int)var.x_y_tex.x];
			put_color(data, i, var.tex_cods.y, color);
			var.tex_cods.y++;
		}
		i++;
	}
}
