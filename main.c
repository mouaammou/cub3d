/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:34:19 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/18 01:39:27 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

// int	hook(t_cub3d *data)
// {
// 	// t_cub3d *data = (t_cub3d *) aa;
// 	mlx_clear_window(data->mlx, data->win);
// 	render_map(data);
// 	render_player(data);
// 	mlx_hook(data->win, ON_KEYDOWN, 0, move_player, data);
// 	return (1);
// }

int	render_img(t_cub3d *data)
{
	// mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0 , 0);
	return (0);
}

void	put_color(t_cub3d *data, int x, int y, uint32_t color)
{
	data->frame[y * WINDOW_WIDTH + x] = color; // White pixel
}

int main ()
{
	t_cub3d	mygrid;
	int tmp;

	initialize_map(&mygrid);
	mygrid.img = mlx_new_image(mygrid.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mygrid.frame = (uint32_t *)mlx_get_data_addr(mygrid.img, &tmp, &tmp, &tmp);
	render_map(&mygrid);
	render_player(&mygrid);
	render_rays(&mygrid, 0xffffff);
	

	mlx_hook(mygrid.win, ON_KEYDOWN, 0, move_player, &mygrid);
	mlx_loop_hook(mygrid.mlx, render_img, &mygrid);

	mlx_loop(mygrid.mlx);
	return (0);
}
