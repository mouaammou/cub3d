/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:34:19 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/14 23:37:36 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int main ()
{
	t_cub3d	mygrid;

	initialize_map(&mygrid);


	render_map(&mygrid);
	render_player(&mygrid);
	dd_draw_line(mygrid.myplayer.x, mygrid.myplayer.y,0, 0, &mygrid);
	mlx_loop(mygrid.mlx);
	return (0);
}
