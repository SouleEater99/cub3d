/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:56:13 by aelkheta          #+#    #+#             */
/*   Updated: 2024/10/10 14:59:07 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cub3d.h>

/// @brief this function setting a pixel in an image with the cordinates given.
/// @param image t_image *image: A pointer to a struct that holds the image information. This struct typically includes:
/// @param img_data: A pointer to the raw image data (the actual pixel array).
/// @param size_line: The number of bytes that represent a single row (or "line") of pixels in the image.
/// @param bits_per_pixel: The number of bits used to represent a single pixel (often 32 bits, or 4 bytes).
/// @param endian: Information about the byte order (not used directly in this function).
/// @param x is the horizontal position of the coordinates of the pixel you want to modify.
/// @param y is the vertical position of the coordinates of the pixel you want to modify.
/// @param color The color value (in ARGB format) that will be applied to the specified pixel. This is typically a 32-bit integer where each byte represents a different color component (Alpha, Red, Green, Blue).
void put_pixel_in_img(t_image *image, int x, int y, int color)
{
    int pixel_index = (y * image->size_line) + (x * (image->bits_per_pixel / 8));
    *(int *)(image->img_data + pixel_index) = color;
}

/// @brief Create a new image.
/// @param data the struct that hold all what we need.
/// @return return an allocated pointer to the image created.
t_image *create_image(t_data *data)
{
    t_image *img = malloc(sizeof(t_image));
    int width = SCREEN_WIDTH;
    int height = SCREEN_HEIGHT;
    img->img_ptr = mlx_new_image(data->mlx_ptr, width, height);
    img->img_data = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, &img->size_line, &img->endian);

    return img;
}