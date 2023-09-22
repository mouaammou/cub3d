/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennacir <rennacir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:37:31 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/22 20:34:01 by rennacir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int destroy_window(void *param)
{
	exit(0);
	return (0);
}

void	put_color(unsigned int *frame, int x, int y, int color)
{
	if (x >= 0 && x < WINDOW_WIDTH
		&& y >= 0 && y < WINDOW_HEIGHT)
		frame[y * WINDOW_WIDTH + x] = color;
}

void	put_color_map(unsigned int *frame, int x, int y, int color)
{
	int	w;

	w = WINDOW_WIDTH * SCALE_MAP;
	if (x >= 0 && x < WINDOW_WIDTH * SCALE_MAP
		&& y >= 0 && y < WINDOW_HEIGHT * SCALE_MAP)
		frame[y * w + x] = color;
}

void	fill_texture(t_texture *texture1, t_texture *texture2, t_texture *texture3, t_texture *texture4, t_cub3d *data)
{
	char	*texture_ptr1;
	char	*texture_ptr2;
	char	*texture_ptr3;
	char	*texture_ptr4;
	int tmp;
	texture_ptr1 = mlx_xpm_file_to_image(data->mlx, "wall_1.xpm", &(*texture1).width, &(*texture1).height);
	texture_ptr2 = mlx_xpm_file_to_image(data->mlx, "wall_2.xpm", &(*texture2).width, &(*texture2).height);
	texture_ptr3 = mlx_xpm_file_to_image(data->mlx, "wall_3.xpm", &(*texture3).width, &(*texture3).height);
	texture_ptr4 = mlx_xpm_file_to_image(data->mlx, "wall_4.xpm", &(*texture4).width, &(*texture4).height);
	(*texture1).cast_texture = (uint32_t *)mlx_get_data_addr(texture_ptr1, &tmp, &tmp, &tmp);
	(*texture2).cast_texture = (uint32_t *)mlx_get_data_addr(texture_ptr2, &tmp, &tmp, &tmp);
	(*texture3).cast_texture = (uint32_t *)mlx_get_data_addr(texture_ptr3, &tmp, &tmp, &tmp);
	(*texture4).cast_texture = (uint32_t *)mlx_get_data_addr(texture_ptr4, &tmp, &tmp, &tmp);
}


void	render_textures(t_cub3d *data)
{
	int cast_width;
	int cast_height;
	int i = 0;
	int	x_in_map;
	int	x_in_texture;
	int	y = 0;
	int color;
	int	y_in_texture;
	double	distance;
	double	wall3d_height;
	double	wall3d_distance;
	char	*texture_ptr;
	char	*texture_ptr1;
	char	*texture_ptr2;
	char	*texture_ptr3;
	t_texture texture1;
	t_texture texture2;
	t_texture texture3;
	t_texture texture4;
	uint32_t *cast;
	int tmp;
	fill_texture(&texture1, &texture2, &texture3, &texture4, data);
	color_sky(data);
	color_floor(data);
	i = 0;
	while (i < NUM_RAYS)
	{
		if (isRayFacingUp(data->myray[i].ray_angle) && !data->myray[i].was_hit_vertical)
		{
			cast = texture1.cast_texture;
			cast_width = texture1.width;
			cast_height = texture1.height;
		}
		else if (isRayFacingDown(data->myray[i].ray_angle) && !data->myray[i].was_hit_vertical)
		{
			cast = texture2.cast_texture;
			cast_width = texture2.width;
			cast_height = texture2.height;
		}
		else if (isRayFacingRight(data->myray[i].ray_angle) && data->myray[i].was_hit_vertical)
		{
			cast = texture3.cast_texture;
			cast_width = texture3.width;
			cast_height = texture3.height;
		}
		else if (isRayFacingLeft(data->myray[i].ray_angle) && data->myray[i].was_hit_vertical)
		{
			cast = texture4.cast_texture;
			cast_width = texture4.width;
			cast_height = texture4.height;
		}
		distance = data->myray[i].distance * cos(data->myray[i].ray_angle - data->myplayer.rotation_angle);
		wall3d_distance = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
		wall3d_height = (TILE_SIZE / distance) * wall3d_distance;
		y = (WINDOW_HEIGHT / 2) - (wall3d_height / 2);
		//find x
		if (data->myray[i].was_hit_vertical)
			x_in_map = (int)data->myray[i].wall_hit_y % TILE_SIZE;
		else
			x_in_map = (int)data->myray[i].wall_hit_x % TILE_SIZE;
		x_in_texture = (x_in_map * cast_width) / WINDOW_WIDTH;
		// find y
		while (y < wall3d_height + (WINDOW_HEIGHT / 2) - (wall3d_height / 2))
		{
			int	distance_from_top = y + (wall3d_height / 2) - (WINDOW_HEIGHT / 2);
			y_in_texture = (distance_from_top * cast_height) / wall3d_height;
			color = cast[y_in_texture * cast_width + x_in_texture];
			put_color(data->frame, i, y, color);
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
	data->map_img = mlx_new_image(data->mlx, WINDOW_WIDTH * SCALE_MAP, WINDOW_HEIGHT * SCALE_MAP);
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

int main ()
{
	t_cub3d	*data;

	data = malloc (sizeof (t_cub3d));
	if (!data)
		return (1);
	initialize_map(data);
	mlx_hook(data->win, ON_KEYDOWN, 0, move_player, data);
	mlx_hook(data->win, ON_KEYUP, 0, key_released, data);
	mlx_hook(data->win, ON_DESTROY, 0, destroy_window, data);
	mlx_loop_hook(data->mlx, render_img, data);
	mlx_loop(data->mlx);
	return (0);
}
