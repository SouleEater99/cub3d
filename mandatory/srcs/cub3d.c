/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:07:23 by aelkheta          #+#    #+#             */
/*   Updated: 2024/10/13 11:58:45 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cub3d.h>

void update_player_positions(t_data *data, int keycode)
{
    int map_x;
    int map_y;
    
    if (keycode == U_KEY)
    {
        map_x = (int)(data->player_x + data->dir_x * MOVE_SPEED);
        map_y = (int)(data->player_y + data->dir_y * MOVE_SPEED);
        
        if (data->map[map_y][map_x] == '0' && map_x >= 0 && map_x < MAP_WIDTH && map_y >= 0 && map_y < SCREEN_HEIGHT)
        {
            data->player_x += data->dir_x * MOVE_SPEED;
            data->player_y += data->dir_y * MOVE_SPEED;
        }
    }
    
    if (keycode == D_KEY)
    {
        map_x = (int)(data->player_x - data->dir_x * MOVE_SPEED);
        map_y = (int)(data->player_y - data->dir_y * MOVE_SPEED);

        if (data->map[map_y][map_x] == '0' && map_x >= 0 && map_x < MAP_WIDTH && map_y >= 0 && map_y < SCREEN_HEIGHT)
        {
            data->player_x -= data->dir_x * MOVE_SPEED;
            data->player_y -= data->dir_y * MOVE_SPEED;
        }
    }

    if (keycode == L_KEY) 
    {
        double old_dir_x = data->dir_x;
        data->dir_x = data->dir_x * cos(-ROT_SPEED) - data->dir_y * sin(-ROT_SPEED);
        data->dir_y = old_dir_x * sin(-ROT_SPEED) + data->dir_y * cos(-ROT_SPEED);

        double old_plane_x = data->plane_x;
        data->plane_x = data->plane_x * cos(-ROT_SPEED) - data->plane_y * sin(-ROT_SPEED);
        data->plane_y = old_plane_x * sin(-ROT_SPEED) + data->plane_y * cos(-ROT_SPEED);
    }

    if (keycode == R_KEY) 
    {
        double old_dir_x = data->dir_x;
        data->dir_x = data->dir_x * cos(ROT_SPEED) - data->dir_y * sin(ROT_SPEED);
        data->dir_y = old_dir_x * sin(ROT_SPEED) + data->dir_y * cos(ROT_SPEED);

        double old_plane_x = data->plane_x;
        data->plane_x = data->plane_x * cos(ROT_SPEED) - data->plane_y * sin(ROT_SPEED);
        data->plane_y = old_plane_x * sin(ROT_SPEED) + data->plane_y * cos(ROT_SPEED);
    }

}

int keyhook(int keycode, t_data *data)
{
    if (keycode == ESC_KEY)
    {
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        // mlx_destroy_image(data->mlx_ptr, data->image->img_ptr);
        // free_array(data->map);
        free(data->mlx_ptr);
        exit(0);
    }

    int map_x;
    int map_y;

    if (keycode == U_KEY)
    {
        map_x = (int)(data->player_x + data->dir_x * MOVE_SPEED);
        map_y = (int)(data->player_y + data->dir_y * MOVE_SPEED);
        
        if (data->map[map_y][map_x] == '0' && map_x >= 0 && map_x < MAP_WIDTH && map_y >= 0 && map_y < SCREEN_HEIGHT)
        {
            data->player_x += data->dir_x * MOVE_SPEED;
            data->player_y += data->dir_y * MOVE_SPEED;
        }
    }
    
    if (keycode == D_KEY)
    {
        map_x = (int)(data->player_x - data->dir_x * MOVE_SPEED);
        map_y = (int)(data->player_y - data->dir_y * MOVE_SPEED);

        if (data->map[map_y][map_x] == '0' && map_x >= 0 && map_x < MAP_WIDTH && map_y >= 0 && map_y < SCREEN_HEIGHT)
        {
            data->player_x -= data->dir_x * MOVE_SPEED;
            data->player_y -= data->dir_y * MOVE_SPEED;
        }
    }

    if (keycode == L_KEY) 
    {
        double old_dir_x = data->dir_x;
        data->dir_x = data->dir_x * cos(-ROT_SPEED) - data->dir_y * sin(-ROT_SPEED);
        data->dir_y = old_dir_x * sin(-ROT_SPEED) + data->dir_y * cos(-ROT_SPEED);

        double old_plane_x = data->plane_x;
        data->plane_x = data->plane_x * cos(-ROT_SPEED) - data->plane_y * sin(-ROT_SPEED);
        data->plane_y = old_plane_x * sin(-ROT_SPEED) + data->plane_y * cos(-ROT_SPEED);
    }

    if (keycode == R_KEY) 
    {
        double old_dir_x = data->dir_x;
        data->dir_x = data->dir_x * cos(ROT_SPEED) - data->dir_y * sin(ROT_SPEED);
        data->dir_y = old_dir_x * sin(ROT_SPEED) + data->dir_y * cos(ROT_SPEED);

        double old_plane_x = data->plane_x;
        data->plane_x = data->plane_x * cos(ROT_SPEED) - data->plane_y * sin(ROT_SPEED);
        data->plane_y = old_plane_x * sin(ROT_SPEED) + data->plane_y * cos(ROT_SPEED);
    }

    // if (keycode == U_KEY)
    //     update_player_positions(data, keycode);
    // if (keycode == D_KEY)
    //     update_player_positions(data, keycode);

    //     // update_player_positions(data);
    // if (keycode == L_KEY)
    //     update_player_positions(data, keycode);

    //     // update_player_positions(data);
    // if (keycode == R_KEY)
    //     update_player_positions(data, keycode);

    //     // update_player_positions(data);
    
    raycasting(data);
    return (0);
}

int main()
{
    t_data data;
    
    data.mlx_ptr = mlx_init();
    data.win_ptr = mlx_new_window(data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");

    init_game(&data);
    raycasting(&data);
     
    mlx_hook(data.win_ptr, 2, 1L << 0, keyhook, &data);
    mlx_loop(data.mlx_ptr);
    return (0);
}