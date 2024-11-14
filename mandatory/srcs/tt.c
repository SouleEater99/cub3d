#include <mlx.h>
#include <stdio.h>

int main(void)
{
    void    *mlx;
    void    *window;
    void    *image;
    int     img_width;
    int     img_height;

    // Initialize the mlx environment
    mlx = mlx_init();
    if (!mlx)
    {
        fprintf(stderr, "Error initializing MLX\n");
        return 1;
    }

    // Create a new window (width, height, title)
    window = mlx_new_window(mlx, 800, 600, "Display Image");

    // Load an image (replace "path_to_image.xpm" with your XPM image file)
    image = mlx_xpm_file_to_image(mlx, "../textures/sprites/w0_a.xpm", &img_width, &img_height);
    if (!image)
    {
        fprintf(stderr, "Error loading image\n");
        return 1;
    }

    // Put the image in the window at coordinates (0, 0)
    mlx_put_image_to_window(mlx, window, image, 0, 0);

    // Wait for the user to close the window
    mlx_loop(mlx);

    return 0;
}
