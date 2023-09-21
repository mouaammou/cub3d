/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:37:31 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/21 10:17:20 by mouaammo         ###   ########.fr       */
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
	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
		frame[y * WINDOW_WIDTH + x] = color;
}

void	put_color_map(unsigned int *frame, int x, int y, int color)
{
	int w = WINDOW_WIDTH * SCALE_MAP;
	if (x >= 0 && x < WINDOW_WIDTH * SCALE_MAP && y >= 0 && y < WINDOW_HEIGHT * SCALE_MAP)
		frame[y * w + x] = color;
}

int	render_img(t_cub3d *data)
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

	update_position_player(data);
	render_map(data);
	render_player(data);
	render_rays(data);//all rays are stored in the table in this funcion
	render_cube_3d(data);
	
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0 , 0);
	mlx_put_image_to_window(data->mlx, data->win, data->map_img, 0 , 0);
	return (0);
}

int main ()
{
	t_cub3d	*data = malloc (sizeof (t_cub3d));
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
