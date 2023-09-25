/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennacir <rennacir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:37:31 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/25 08:33:24 by rennacir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

void	error(	char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

int destroy_window(void *param)
{
	exit(0);
	return (0);
}

void	put_color(t_cub3d *data, int x, int y, int color)
{
	if (x >= 0 && x < WINDOW_WIDTH
		&& y >= 0 && y < WINDOW_HEIGHT)
	data->frame[y * WINDOW_WIDTH + x] = color;
}

void	put_color_map(t_cub3d *data, int x, int y, int color)
{
	int	w;

	w = data->list->win_width * SCALE_MAP;
	if (x >= 0 && x < data->list->win_width * SCALE_MAP
		&& y >= 0 && y < data->list->win_height * SCALE_MAP)
		data->frame_map[y * w + x] = color;
}

void	get_textures(t_cub3d *data)
{
	char	*t1[4];
	int tmp;
	data->texture = malloc(sizeof(t_texture) * 4);
	if (!data->texture)
	{
		ft_putstr_fd("Error\n", 2);
		return ;
	}
	t1[0] = mlx_xpm_file_to_image(data->mlx, "textures/said.xpm", &data->texture[0].width, &data->texture[0].height);
	t1[1] = mlx_xpm_file_to_image(data->mlx, "textures/wood1.xpm", &data->texture[1].width, &data->texture[1].height);
	t1[2] = mlx_xpm_file_to_image(data->mlx, "textures/wood2.xpm", &data->texture[2].width, &data->texture[2].height);
	t1[3] = mlx_xpm_file_to_image(data->mlx, "textures/wood3.xpm", &data->texture[3].width, &data->texture[3].height);

	if (!t1[0] || !t1[1] || !t1[2] || !t1[3])
	{
		ft_putstr_fd("Error\n", 2);
		return ;
	}
	data->texture[0].cast_texture = (uint32_t *)mlx_get_data_addr(t1[0], &tmp, &tmp, &tmp);
	data->texture[1].cast_texture = (uint32_t *)mlx_get_data_addr(t1[1], &tmp, &tmp, &tmp);
	data->texture[2].cast_texture = (uint32_t *)mlx_get_data_addr(t1[2], &tmp, &tmp, &tmp);
	data->texture[3].cast_texture = (uint32_t *)mlx_get_data_addr(t1[3], &tmp, &tmp, &tmp);
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

void	render_textures(t_cub3d *data)
{
	int i = 0;
	int	x_in_map;
	double	x_in_texture;
	int	y = 0;
	int color;
	double	y_in_texture;
	double	distance;
	double	wall3d_height;
	double	wall3d_distance;
	get_textures(data);
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
		//find x
		if (data->myray[i].was_hit_vertical)
			x_in_map = fmod(data->myray[i].wall_hit_y, TILE_SIZE);
		else
			x_in_map = fmod(data->myray[i].wall_hit_x ,TILE_SIZE);
		x_in_texture = (x_in_map * texture.width) / TILE_SIZE;
		while (y < wall3d_height + (WINDOW_HEIGHT / 2) - (wall3d_height / 2))
		{
			int	distance_from_top = y + (wall3d_height / 2) - (WINDOW_HEIGHT / 2);
			y_in_texture = (distance_from_top * texture.height) / wall3d_height;
			color = texture.cast_texture[(int)y_in_texture * texture.width + (int)x_in_texture];
			put_color(data, i, y, color);
			y++;
		}
		i++;
	 }
}

void	get_imgs_data(t_cub3d *data)
{
	int	tmp;

	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->map_img)
		mlx_destroy_image(data->mlx, data->map_img);
	mlx_clear_window(data->mlx, data->win);
	data->map_img = mlx_new_image(data->mlx, data->list->win_width * SCALE_MAP, data->list->win_height * SCALE_MAP);
	data->frame_map = (unsigned int *)mlx_get_data_addr(data->map_img, &tmp, &tmp, &tmp);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->frame = (unsigned int *)mlx_get_data_addr(data->img, &tmp, &tmp, &tmp);
}
int	render_img(t_cub3d *data)

{
	get_imgs_data(data);
	update_position_player(data);
	render_map(data);
	render_player(data);
	render_rays(data);
	// render_cube_3d(data);
	render_textures(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0 , 0);
	mlx_put_image_to_window(data->mlx, data->win, data->map_img, 0 , 0);
	return (0);
}

int main (int argc, char **argv)
{
	t_cub3d	*data;
	t_list	*list;

	data = malloc (sizeof (t_cub3d));
	if (!data)
		return (1);
	data->img = NULL;
	data->map_img = NULL;
	list = parsing(argc, argv);
	initialize_map(data, list);
	mlx_hook(data->win, ON_KEYDOWN, 0, move_player, data);
	mlx_hook(data->win, ON_KEYUP, 0, key_released, data);
	mlx_hook(data->win, ON_DESTROY, 0, destroy_window, data);
	mlx_loop_hook(data->mlx, render_img, data);
	mlx_loop(data->mlx);
	return (0);
}
