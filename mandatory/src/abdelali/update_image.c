#include "../../include/cub3d.h"

void    ft_update_data(t_data *data)
{
    if (data->walk_direction != 0)// && data->Factor_Scale_Map != 1)
    {
        int x = (int)(data->x_player / CUBE_TILE);
        int y = (int)(data->y_player / CUBE_TILE);
        data->move_step = data->move_speed * data->walk_direction;
        printf("player at: %lf %lf\n", data->x_player / CUBE_TILE, data->y_player / CUBE_TILE);
        printf("(%d, %d) == [%c]\n", y, x, data->map.map[y][x]);
        printf("(%d, %d) == [%c]\n", y - 1, x, data->map.map[y - 1][x]);
        printf("(%d, %d) == [%c]\n", y + 1, x, data->map.map[y + 1][x]);
        printf("(%d, %d) == [%c]\n", y, x - 1, data->map.map[y][x - 1]);
        printf("(%d, %d) == [%c]\n", y, x + 1, data->map.map[y][x + 1]);
        ft_is_player_inside_wall(data);
    }
    if (data->turn_direction != 0) //&& data->Factor_Scale_Map != 1)
    {
        data->player_angle += data->turn_direction * data->turn_speed;
		data->player_angle = ft_normalize_angle(data->player_angle);
    }
}

void    ft_update_image(t_data *data)
{
    ft_create_pojection_img(data);
    if (!(data->clicks % 2))
        ft_cast_all_rays(data);
    draw_minimap(data);
    // ft_write_mini_map(data);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->projection_img.img_ptr, 0, 0);
    mlx_destroy_image(data->mlx_ptr, data->projection_img.img_ptr);
}