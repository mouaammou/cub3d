/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennacir <rennacir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:34:19 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/18 18:20:52 by rennacir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int	render_img(t_cub3d *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0 , 0);
	return (0);
}

void	put_color(t_cub3d *data, int x, int y, uint32_t color)
{
	data->frame[y * WINDOW_WIDTH + x] = color;
}

int destroy_window(void *param)
{
	exit(0);
	return (0);
}

int main ()
{
	t_cub3d	mygrid;

	initialize_map(&mygrid);
	render_map(&mygrid);
	render_player(&mygrid);
	// render_rays(&mygrid, 0xffffff);

	mlx_hook(mygrid.win, ON_KEYDOWN, 0, move_player, &mygrid);
	mlx_hook(mygrid.win, ON_DESTROY, 0, destroy_window, &mygrid);
	mlx_loop_hook(mygrid.mlx, render_img, &mygrid);

	mlx_loop(mygrid.mlx);
	return (0);
}
