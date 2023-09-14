/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:38:07 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/14 01:52:35 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <mlx.h>

typedef enum screen_data
{
	SIZE = 64,
	MAP_NUM_ROWS = 11,
	MAP_NUM_COLS = 15,
	WINDOW_WIDTH = MAP_NUM_COLS * SIZE,
	WINDOW_HEIGHT = MAP_NUM_ROWS * SIZE,
	WALL_STRIP_WIDTH = 1,
	NUM_RAYS = WINDOW_WIDTH / WALL_STRIP_WIDTH
}t_window_data;

typedef struct cub3d
{
	void	*mlx;
	void	*win;
	int		grid[MAP_NUM_ROWS][MAP_NUM_COLS];
	float	scale_factor;
}t_cub3d;

#endif
