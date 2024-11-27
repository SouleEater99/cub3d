
#include "../../include/cub3d.h"

double rad_to_deg(double rad_angle)
{
    return (rad_angle * 180 / PI);
}

double deg_to_rad(double deg_angle)
{
    return (deg_angle * PI / 180);
}

double get_player_dir(int16_t player_dir)
{
    printf("player dir: %c\n", player_dir);
	if (player_dir == 'N')		// North
        return (-PI / 2);
	else if (player_dir == 'S')	// South
        return (PI / 2);
	else if (player_dir == 'W')	// West
        return (PI);
	else if (player_dir == 'E')	// East
        return (0);
    return (-1);
}

int init_data(t_data *data, int ac, char **av)
{    
    init_mlx(data);

    if (!parse_map(data, ac, av))
        exit (10);
    
    data->row = data->map.map_width;//22;
    data->col = data->map.map_height;//10;
    // data->map = data->map.map;

    printf("%d %d\n", data->map.map_height, data->map.map_width);
    // data->factor_scale_map  = 0.2;
    data->img_width = SCREEN_WIDTH;
    data->img_height = SCREEN_HEIGHT;
    data->x_player = data->player_x * CUBE_TILE; // + (CUBE_TILE / 2);
    data->y_player = data->player_y * CUBE_TILE; // + (CUBE_TILE / 2);

    data->player_angle = (double)get_player_dir(data->player_dir);

    printf("angle: %lf\n", data->player_angle);

    data->turn_speed = ROT_SPEED; // 0.2;
    data->move_speed = MOVE_SPEED; // 8;
    data->num_rays = WIDTH / WALL_STRIP;
    data->plan_distanced = (WIDTH / 2) / tan(FOV / 2);

// =================================== //

    data->player_x = data->x_player / (CUBE_TILE + (CUBE_TILE / 2));
    data->player_y = data->y_player / (CUBE_TILE + (CUBE_TILE / 2));
    data->scale = SCALE;
    // data->map.map = data->map;
    // data->map.map_height = data->col;
    // data->map.map_width = data->row;
	data->player_radius = PLAYER_RADIUS;
	data->minimap_radius = MINIMAP_RADIUS;
	data->minimap_x_center = MINIMAP_MID_X;
	data->minimap_y_center = MINIMAP_MID_Y;

	init_player_sprites(data, "./textures/sprites/gun_sprite_0/", 22);
    
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