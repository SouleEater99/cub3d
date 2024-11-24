
#include "../include/cub3d.h"

void    ft_init_door(t_data *data)
{
    data->n_door = 3;
    data->door = (t_door *)malloc(sizeof(t_door) * data->n_door);
    data->door   = memset(data->door, 0, sizeof(t_door) * data->n_door);
    data->door[0].x = 8;
    data->door[0].y = 1;
    data->door[1].x = 16;
    data->door[1].y = 4;
    data->door[2].x = 8;
    data->door[2].y = 5;
}

int init_data(t_data *data, int ac, char **av)
{    
    init_mlx(data);

    if (!parse_map(data, ac, av))
        exit (10);
    
    data->row = data->map_.map_width;//22;
    data->col = data->map_.map_height;//10;
    data->map = data->map_.map;

    printf("%d %d\n", data->map_.map_height, data->map_.map_width);
    // data->factor_scale_map  = 0.2;
    data->img_width = data->row * (int)CUBE_TILE;
    data->img_height = data->col * (int)CUBE_TILE;
    data->x_player = 5 * CUBE_TILE; // + (CUBE_TILE / 2);
    data->y_player = 1 * CUBE_TILE; // + (CUBE_TILE / 2);
    data->player_angle = PI;
    data->turn_speed = 0.04;
    data->move_speed = 2;
    data->num_rays = WIDTH / WALL_STRIP;
    data->plan_distanced = (WIDTH / 2) / tan(FOV / 2);

// =================================== //

    data->player_x = data->x_player / (CUBE_TILE + (CUBE_TILE / 2));
    data->player_y = data->y_player / (CUBE_TILE + (CUBE_TILE / 2));
    data->scale = SCALE;
    // data->map_.map = data->map;
    // data->map_.map_height = data->col;
    // data->map_.map_width = data->row;
	data->player_radius = PLAYER_RADIUS;
	data->minimap_radius = MINIMAP_RADIUS;
	data->minimap_x_center = MINIMAP_MID_X;
	data->minimap_y_center = MINIMAP_MID_Y;
    
// =================================== //

    return (0);
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