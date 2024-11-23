
#include "../include/cub3d.h"

void    ft_free_all(char *msg, t_data *data, int exit_status)
{
    if (data)
    {
        if (data->texture_img_1.img_ptr)
            mlx_destroy_image(data->mlx_ptr, data->texture_img_1.img_ptr);
        if (data->texture_img_2.img_ptr)
            mlx_destroy_image(data->mlx_ptr, data->texture_img_2.img_ptr);
        if (data->texture_img_3.img_ptr)
            mlx_destroy_image(data->mlx_ptr, data->texture_img_3.img_ptr);
        if (data->texture_img_4.img_ptr)
            mlx_destroy_image(data->mlx_ptr, data->texture_img_4.img_ptr);
        if (data->win_ptr)
            mlx_destroy_window(data->mlx_ptr , data->win_ptr);
        if (data->mlx_ptr)
        {
            mlx_destroy_display(data->mlx_ptr);
            free(data->mlx_ptr);
        }
        free(data);
    }
    if (msg)
        write(2, msg, strlen(msg));
    exit(exit_status);
}
