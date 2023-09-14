/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:56:19 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/14 16:57:06 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// DDA Function for line generation
// void DDA(int X0, int Y0, int X1, int Y1)
// {
// 	// calculate dx & dy
// 	int dx = X1 - X0;//horizontal
// 	int dy = Y1 - Y0;//vertical

// 	// calculate steps required for generating pixels
// 	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

// 	// calculate increment in x & y for each steps
// 	float Xinc = dx / (float)steps;
// 	float Yinc = dy / (float)steps;

// 	// Put pixel for each step
// 	float X = X0;
// 	float Y = Y0;
// 	for (int i = 0; i <= steps; i++) {
// 		// mlx_pixel_put(round(X), round(Y), RED); // put pixel at (X,Y)
// 		X += Xinc; // increment in x at each step
// 		Y += Yinc; // increment in y at each step
// 		// delay(100); // for visualization of line-
// 					// generation step by step
// 	}
// }
