/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennacir <rennacir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 19:16:24 by rennacir          #+#    #+#             */
/*   Updated: 2023/09/25 09:02:09 by rennacir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <mlx.h>

// Define the window size and player position
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define PLAYER_X 400
#define PLAYER_Y 300

// Define your map (you can use a 2D array or another data structure)
// For simplicity, we'll use a 2D array.
char map[WIN_WIDTH][WIN_HEIGHT];

// Function to render the environment around the player
int render_environment(void *mlx_ptr, void *win_ptr)
{
    int view_distance = 50;  // Adjust the view distance as needed

    for (int x = PLAYER_X - view_distance; x < PLAYER_X + view_distance; x++)
    {
        for (int y = PLAYER_Y - view_distance; y < PLAYER_Y + view_distance; y++)
        {
            if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
            {
                // Draw the map element at (x, y)
                mlx_pixel_put(mlx_ptr, win_ptr, x, y, map[x][y]);
            }
        }
    }
	return 0;
}

int main()
{
    void *mlx_ptr;
    void *win_ptr;

    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "MiniLibX Map");

    // Initialize your map data here (fill 'map' with appropriate values)

    mlx_loop_hook(mlx_ptr, render_environment, win_ptr);
    mlx_loop(mlx_ptr);

    return 0;
}
