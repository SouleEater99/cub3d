
#include "../include/cub3d.h"

int ft_key_press(int key, void *param)
{
    t_data *data;

    data = (t_data *)param;
    (void) data;
    if (key == XK_Up || key == XK_w)
        data->walk_direction = 1;
    else if (key == XK_Down || key == XK_s)
       data->walk_direction = -1;
    else if (key == XK_Right)
        data->turn_direction = 1;
    else if (key == XK_Left)
        data->turn_direction = -1;
    else if (key == XK_m)
    {
        if (data->factor_scale_map == 1)
            data->factor_scale_map = 0.2;
        else
            data->factor_scale_map = 1;
        mlx_clear_window(data->mlx_ptr, data->win_ptr);
    }
    else  if (key == XK_e)
    {
        data->flag = 1;
        ft_write_player_wall_hit(data);
    }
    else if (key == XK_Escape)
        ft_free_all(NULL, data, 0);
    
    else if(key == CTRL_KEY)
        data->shoot = 1;
    return (0);
}

int ft_key_release(int key, void *param)
{
    t_data *data;

    data = (t_data *)param;
    (void) data;
    if (key == XK_Up || key == XK_w)
        data->walk_direction = 0;
    else if (key == XK_Down || key == XK_s)
       data->walk_direction = 0;
    else if (key == XK_Right)
        data->turn_direction = 0;
    else if (key == XK_Left)
        data->turn_direction = 0;
    else if(key == CTRL_KEY)
        data->shoot = 0;
    return (0);
}

int ft_key_destroy(void *param)
{
    ft_free_all(NULL, (t_data *)param, 0);
    return (0);
}


int ft_loop_hook(void *param)
{
    t_data *data;

    data = (t_data *)param;
    (void ) data;
    ft_update_data(data);
    ft_update_image(data);
    mouse_hooks(data);

    return (0);
}