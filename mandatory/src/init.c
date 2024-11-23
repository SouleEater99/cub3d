
#include "../include/cub3d.h"

t_data  *init_data()
{
    t_data *Data;

    Data = (t_data *)malloc(sizeof(t_data));
    if (!Data)
        return (NULL);
    Data = memset(Data, 0, sizeof(t_data));
    Data->row = 22;
    Data->col = 10;
    Data->factor_scale_map  = 0.2;
    Data->img_width = Data->row * (int)CUBE_TILE;
    Data->img_height = Data->col * (int)CUBE_TILE;
    Data->x_player = 5 * CUBE_TILE + (CUBE_TILE / 2);
    Data->y_player = 3 * CUBE_TILE + (CUBE_TILE / 2);
    Data->player_angle = PI;
    Data->turn_speed = 0.02;
    Data->move_speed = 1.5;
    Data->num_rays = WIDTH / WALL_STRIP;
    Data->plan_distanced = (WIDTH / 2) / tan(FOV / 2);
   
    return (Data);
}

void    init_mlx(t_data *data)
{
    data->mlx_ptr = mlx_init();
    if (!data->mlx_ptr)
        ft_free_all("mlx Fail\n", data, 1);
    data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HIGH, "First Game 3D");
    if (!data->win_ptr)
        ft_free_all("win_ptr Fail\n", data, 1);
    
}