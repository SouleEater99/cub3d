/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:07:23 by aelkheta          #+#    #+#             */
/*   Updated: 2024/10/08 13:18:39 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cub3d.h>

int keyhook(int keycode, t_data *data)
{
    if (keycode == ESC_KEY)
    {
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        free(data->mlx_ptr);
        exit(0);
    }

    if (keycode == U_KEY)
    {
        // update_player_positions()
    }
    
    if (keycode == D_KEY)
    {
        // update_player_positions()
    }

    if (keycode == L_KEY) 
    {
        // update_player_direction()
    }

    if (keycode == R_KEY) 
    {
        // update_player_direction()
    }
    // raycasting(); 
    return (0);
}

int main()
{
    t_data data;
    
    data.mlx_ptr = mlx_init();

    data.win_ptr = mlx_new_window(data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
    mlx_hook(data.win_ptr, 2, 1L << 0, keyhook, &data);
    mlx_loop(data.mlx_ptr);
    return (0);
}