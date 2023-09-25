/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:58:34 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/25 17:58:50 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_line(t_cords p0, t_cords p1, t_cub3d *data, int color)
{
	t_cords		delta;
	t_cords		inc;
	double		steps;
	int			i;

	delta.x = p1.x - p0.x;
	delta.y = p1.y - p0.y;
	if (fabs(delta.x) > fabs(delta.y))
		steps = fabs(delta.x);
	else
		steps = fabs(delta.y);
	inc.x = (delta.x / steps);
	inc.y = (delta.y / steps);
	i = 0;
	while (i <= steps)
	{
		put_color_map(data, p0.x, p0.y, color);
		p0.x += inc.x;
		p0.y += inc.y;
		i++;
	}
}
