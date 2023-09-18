#include "mlx.h"
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600

void update_image(void *param) {
    static int frame = 0;

    // Create a new image on each frame
    void *img_ptr = mlx_new_image(param, WIDTH, HEIGHT);
    int *img_data = (int *)mlx_get_data_addr(img_ptr, NULL, NULL, NULL);

    // Clear the window (set all pixels to black)
    mlx_clear_window(param, win_ptr);

    // Add pixels to the image (for example, draw a diagonal line)
    for (int x = 0; x < WIDTH; x++) {
        int y = (x + frame) % HEIGHT;
        img_data[y * WIDTH + x] = 0xFFFFFF; // White pixel
    }

    // Display the image in the window
    mlx_put_image_to_window(param, win_ptr, img_ptr, 0, 0);
    mlx_destroy_image(param, img_ptr);

    frame++; // Increment the frame for animation
}

int main() {
    void *mlx_ptr;
    void *win_ptr;

    // Initialize MiniLibX
    mlx_ptr = mlx_init();

    // Create a window
    win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "Image with MiniLibX");

    // Use mlx_loop_hook to continuously update the image
    mlx_loop_hook(mlx_ptr, update_image, mlx_ptr);

    // Start the event loop
    mlx_loop(mlx_ptr);

    return 0;
}
