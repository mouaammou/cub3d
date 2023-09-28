/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:37:31 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/28 19:21:25 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

void	error(	char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

void	get_imgs_data(t_cub3d *data)
{
	int	tmp;

	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->map_img)
		mlx_destroy_image(data->mlx, data->map_img);
	mlx_clear_window(data->mlx, data->win);
	data->map.size = 15;
	data->map_img = mlx_new_image(data->mlx, MAP_SIZE, MAP_SIZE);
	data->frame_map = (unsigned int *)mlx_get_data_addr(data->map_img,
			&tmp, &tmp, &tmp);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->frame = (unsigned int *)mlx_get_data_addr(data->img,
			&tmp, &tmp, &tmp);
}

int	render_img(t_cub3d *data)
{
	get_imgs_data(data);
	update_position_player(data);
	render_map(data);
	render_player(data);
	render_rays(data);
	render_textures(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->map_img, 0, 0);
	return (0);
}

int	mouse_hook(int x, int y, t_cub3d *data)
{
	static int	old_x;

	if (x > 0 && x < WINDOW_WIDTH && y > 0 && y < WINDOW_HEIGHT)
	{
		if (x - old_x <= 0)
			data->myplayer.rotation_angle -= 1 * data->myplayer.rotation_speed;
		else
			data->myplayer.rotation_angle += 1 * data->myplayer.rotation_speed;
		old_x = x;
	}
	return (0);
}

int	main(int argc, char **argv)
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
	mlx_hook(data->win, ON_KEYDOWN, 0, key_pressed, data);
	mlx_hook(data->win, 6, 0, mouse_hook, data);
	mlx_hook(data->win, ON_KEYUP, 0, key_released, data);
	mlx_hook(data->win, ON_DESTROY, 0, destroy_window, data);
	get_textures(data);
	mlx_loop_hook(data->mlx, render_img, data);
	mlx_loop(data->mlx);
	free_list(&list);
	free_data(&data);
	return (0);
}
