/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:37:31 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/20 11:29:10 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int destroy_window(void *param)
{
	exit(0);
	return (0);
}

void	put_color(t_cub3d *data, int x, int y, int color)
{
	data->frame[y * WINDOW_WIDTH + x] = color;
}

int	render_img(t_cub3d *data)
{
	int	tmp;

	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	mlx_clear_window(data->mlx, data->win);
	
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->frame = (unsigned int *)mlx_get_data_addr(data->img, &tmp, &tmp, &tmp);
	
	render_map(data);
	render_player(data);
	render_rays(data);//all rays are stored in the table in this funcion

	mlx_put_image_to_window(data->mlx, data->win, data->img, 0 , 0);
	return (0);
}

int main ()
{
	t_cub3d	*data = malloc (sizeof (t_cub3d));
	if (!data)
		return (1);
	
	initialize_map(data);

	mlx_hook(data->win, ON_KEYDOWN, 0, move_player, data);
	mlx_hook(data->win, ON_DESTROY, 0, destroy_window, data);
	mlx_loop_hook(data->mlx, render_img, data);
	
	mlx_loop(data->mlx);
	return (0);
}
