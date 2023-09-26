/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:34:38 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/26 17:34:17 by mouaammo         ###   ########.fr       */
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
	if (data->list->win_height > WINDOW_WIDTH * 50)
		data->map.size = 4;
	else if (data->list->num_col * data->map.size >= WINDOW_WIDTH
		|| data->list->num_row * data->map.size >= WINDOW_HEIGHT)
		data->map.size = 2;
	else
		data->map.size = MAP_SIZE;
	data->map_img = mlx_new_image(data->mlx,
			data->list->num_col * data->map.size,
			data->list->num_row * data->map.size);
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
	render_rays(data);
	render_textures(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->map_img, 0, 0);
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
	mlx_hook(data->win, ON_KEYUP, 0, key_released, data);
	mlx_hook(data->win, ON_DESTROY, 0, destroy_window, data);
	get_textures(data);
	mlx_loop_hook(data->mlx, render_img, data);
	mlx_loop(data->mlx);
	free_list(&list);
	free_data(&data);
	return (0);
}
