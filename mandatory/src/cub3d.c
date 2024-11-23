/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 04:00:00 by ael-maim          #+#    #+#             */
/*   Updated: 2024/11/23 11:56:40 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void    ft_write_texture_img(t_data *data)
{
    data->texture_img_1.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/1.xpm", &data->texture_img_1.width, &data->texture_img_1.height);
    if (!data->texture_img_1.img_ptr)
        ft_free_all("Texture Image Load Fail\n", data, 1);
    data->texture_img_1.img_data = mlx_get_data_addr(data->texture_img_1.img_ptr, &data->texture_img_1.bits_per_pixel, &data->texture_img_1.size_line, &data->texture_img_1.endian);
    if (!data->texture_img_1.img_data)
        ft_free_all("Texture data Load Fail\n", data, 1);

    data->texture_img_2.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/2.xpm", &data->texture_img_2.width, &data->texture_img_2.height);
    if (!data->texture_img_2.img_ptr)
        ft_free_all("Texture Image Load Fail\n", data, 1);
    data->texture_img_2.img_data = mlx_get_data_addr(data->texture_img_2.img_ptr, &data->texture_img_2.bits_per_pixel, &data->texture_img_2.size_line, &data->texture_img_2.endian);
    if (!data->texture_img_2.img_data)
        ft_free_all("Texture data Load Fail\n", data, 1);

    data->texture_img_3.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/3.xpm", &data->texture_img_3.width, &data->texture_img_3.height);
    if (!data->texture_img_3.img_ptr)
        ft_free_all("Texture Image Load Fail\n", data, 1);
    data->texture_img_3.img_data = mlx_get_data_addr(data->texture_img_3.img_ptr, &data->texture_img_3.bits_per_pixel, &data->texture_img_3.size_line, &data->texture_img_3.endian);
    if (!data->texture_img_3.img_data)
        ft_free_all("Texture data Load Fail\n", data, 1);

    data->texture_img_4.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/4.xpm", &data->texture_img_4.width, &data->texture_img_4.height);
    if (!data->texture_img_4.img_ptr)
        ft_free_all("Texture Image Load Fail\n", data, 1);
    data->texture_img_4.img_data = mlx_get_data_addr(data->texture_img_4.img_ptr, &data->texture_img_4.bits_per_pixel, &data->texture_img_4.size_line, &data->texture_img_4.endian);
    if (!data->texture_img_4.img_data)
        ft_free_all("Texture data Load Fail\n", data, 1);
}

int main()
{
    
    t_data  *data;
    // char *Map[] = {
    //     "111111111111111111111111111111111111111111111",
    //     "100000001000000000000000000000000000000000001",
    //     "100000000000110000000000000000000000000000001",
    //     "100000001000110000000000000000000000000000001",
    //     "100011011110110000000000000000000000000000001",
    //     "100000001000000000000000000000000000000000001",
    //     "100000001000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000001000000000000000000000000000000000001",
    //     "100000001000000000000000000000000000000000001",
    //     "100000001000000000000000000000000000000000001",
    //     "100000001000000000000000000000000000000000001",
    //     "100000001000000000000000000000000000000000001",
    //     "111111111111111111111111111111111111111111111",
    // };

    char *map[] = {
        "1111111111111111111111",
        "1000000010000000000001",
        "1000000000000000000001",
        "1000000010000000000001",
        "100011D111100000000001",
        "1000000010000000000001",
        "1000000010000000000001",
        "1000000000000000000001",
        "1000000000000000000001",
        "1111111111111111111111",
    };
    printf("=========== We Are In Debug Mode ============\n");
    data = init_data();
    data->map = map;
    data->door.x = 6;
    data->door.y = 4;
    data->door.is_open = 0;
    init_mlx(data);
    ft_write_texture_img(data);
    mlx_hook(data->win_ptr, 2, (1L<<0) ,ft_key_press, data);
    mlx_hook(data->win_ptr, 3, (1L<<1) ,ft_key_release, data);
    mlx_hook(data->win_ptr, 17, (0L) ,ft_key_destroy, data);
    mlx_loop_hook(data->mlx_ptr, ft_loop_hook, data);
    mlx_loop(data->mlx_ptr);
    ft_free_all(NULL, data, 0);
}