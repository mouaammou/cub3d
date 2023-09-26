/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennacir <rennacir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:28:43 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/26 19:27:44 by rennacir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	put_color(t_cub3d *data, int x, int y, int color)
{
	if (x >= 0 && x < WINDOW_WIDTH
		&& y >= 0 && y < WINDOW_HEIGHT)
		data->frame[y * WINDOW_WIDTH + x] = color;
}

void	put_color_map(t_cub3d *data, int x, int y, int color)
{
	int	w;

	w = data->list->num_col * data->map.size;
	if (x >= 0 && x < data->list->num_col * data->map.size
		&& y >= 0 && y < data->list->num_row * data->map.size)
		data->frame_map[y * w + x] = color;
}
