/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:28:43 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/29 15:44:50 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	destroy_window(void *param)
{
	(void)param;
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

	w = MAP_SIZE;
	if (x >= 0 && x < MAP_SIZE
		&& y >= 0 && y < MAP_SIZE)
		data->frame_map[y * w + x] = color;
}
