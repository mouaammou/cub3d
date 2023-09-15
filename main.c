/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:34:19 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/15 01:18:18 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int main ()
{
	t_cub3d	mygrid;

	initialize_map(&mygrid);
	render_map(&mygrid);
	render_player(&mygrid);
	// dd_draw_line(mygrid.myplayer.x, mygrid.myplayer.y,0, 0, &mygrid);
	mlx_hook(mygrid.win, ON_KEYDOWN, 0, move_player, &mygrid);
	mlx_loop(mygrid.mlx);
	return (0);
}
