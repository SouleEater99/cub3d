/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:59:05 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/21 10:43:30 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cub3d.h>

# define print printf

void mouse_hooks(t_data *data)
{
    if (!data || !data->win_ptr)
        return ;

    int x, y;

    mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr, &x, &y);

    if (x >= 0 && y >= 0 && x < SCREEN_WIDTH && y < SCREEN_HEIGHT)
    {
        data->sensitivity = 0.00005;
        data->rot_angle = data->rot_speed * data->rot_dir + (x - SCREEN_WIDTH / 2);

        data->rot_angle *= data->sensitivity;

        data->mouse_x = x;
        data->mouse_y = y;

	    double	old_dir_x;
	    double	old_plane_x;
        
	    old_dir_x = data->dir_x;
	    data->dir_x = data->dir_x * cos(data->rot_angle) - data->dir_y * sin(data->rot_angle);
	    data->dir_y = old_dir_x * sin(data->rot_angle) + data->dir_y * cos(data->rot_angle);
    
	    old_plane_x = data->plane_x;
	    data->plane_x = data->plane_x * cos(data->rot_angle) - data->plane_y * sin(data->rot_angle);
	    data->plane_y = old_plane_x * sin(data->rot_angle) + data->plane_y * cos(data->rot_angle);

    }
    print("%d %d\n", x, y);

}
