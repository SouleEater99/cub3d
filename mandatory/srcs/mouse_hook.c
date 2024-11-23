/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:59:05 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/23 15:43:25 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cub3d.h>

void mouse_hooks(t_data *data)
{
    if (!data || !data->win_ptr)
        return ;

    int x, y;
    mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr, &x, &y);

    // int delta_x = x - SCREEN_WIDTH / 2;
    int delta_x = data->mouse_x - x;

    printf("%d\n", data->mouse_x - x);

    // if (x < 0 || x > SCREEN_WIDTH)
    //     return ;

    if (x != data->mouse_x)
    {
        data->sensitivity = 0.0025;
        
        // if (data->mouse_x - x < 0)
            // delta_x = -delta_x;

        // if (data->mouse_x - x < 0)
            
        data->rot_angle = data->rot_speed * data->rot_dir - delta_x;  // Subtract delta_x to rotate right when moving left
        data->rot_angle *= data->sensitivity;

        double old_dir_x = data->dir_x;
        double old_plane_x = data->plane_x;
        
        data->dir_x = data->dir_x * cos(data->rot_angle) - data->dir_y * sin(data->rot_angle);
        data->dir_y = old_dir_x * sin(data->rot_angle) + data->dir_y * cos(data->rot_angle);
    
        data->plane_x = data->plane_x * cos(data->rot_angle) - data->plane_y * sin(data->rot_angle);
        data->plane_y = old_plane_x * sin(data->rot_angle) + data->plane_y * cos(data->rot_angle);
    }

    data->mouse_x = x;
    data->mouse_y = y;
}
