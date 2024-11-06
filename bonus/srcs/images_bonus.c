/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:56:13 by aelkheta          #+#    #+#             */
/*   Updated: 2024/10/16 16:42:55 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

// void	put_pixel_in_img(t_image *image, int x, int y, int color)
// {
// 	int	pixel_index;

// 	pixel_index = (y * image->size_line) + (x * (image->bits_per_pixel / 8));
// 	*(int *)(image->img_data + pixel_index) = color;
// }

// t_image	*create_image(t_data *data)
// {
// 	t_image	*img;
// 	int		width;
// 	int		height;

// 	img = malloc(sizeof(t_image));
// 	width = SCREEN_WIDTH;
// 	height = SCREEN_HEIGHT;
// 	img->img_ptr = mlx_new_image(data->mlx_ptr, width, height);
// 	img->img_data = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel,
// 			&img->size_line, &img->endian);
// 	return (img);
// }

void    put_pixel_in_img(t_image *image, int x, int y, int color)
{
    int pixel_index;

    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
        return;

    pixel_index = (y * image->size_line) + (x * (image->bits_per_pixel / 8));
    *(int *)(image->img_data + pixel_index) = color;
}

t_image *create_image(t_data *data)
{
    t_image *img;

    img = malloc(sizeof(t_image));
    if (!img)
        return (NULL);
    img->img_ptr = mlx_new_image(data->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!img->img_ptr)
    {
        free(img);
        return (NULL);
    }
    img->img_data = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel,
            &img->size_line, &img->endian);
    if (!img->img_data)
    {
        mlx_destroy_image(data->mlx_ptr, img->img_ptr);
        free(img);
        return (NULL);
    }
    return (img);
}
