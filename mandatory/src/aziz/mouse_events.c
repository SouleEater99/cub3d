/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 19:03:55 by heisenberg        #+#    #+#             */
/*   Updated: 2024/11/26 11:05:09 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/cub3d.h"

void mouse_hooks(t_data *data)
{
    if (!data || !data->win_ptr)
        return ;

    int x, y;
    mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr, &x, &y);

    int delta_x = data->mouse_x - x;

    if (x < 0 || x > SCREEN_WIDTH || y < 0 || y > SCREEN_HEIGHT)
        return ;

    if (x != data->mouse_x)
    {
        data->sensitivity = 0.01;
        data->player_angle += delta_x * data->sensitivity;
    }

    printf("%lf\n", data->player_angle);
    
    data->mouse_x = x;
    data->mouse_y = y;
}

int check_click_space(t_data *data, int x, int y)
{
    int dx = x - data->minimap_x_center;
    int dy = y - data->minimap_y_center;
    double distance = sqrt(dx * dx + dy * dy);
    if (distance <= data->minimap_radius)
        return (1);
    return (0);
}

int mouse_events(int button, int x, int y, t_data *data)
{
    printf("Button %d pressed at (%d, %d)\n", button, x, y);
    if (button == LEFT_CLICK)
    {
		if (check_click_space(data, x, y))
        {
            data->clicks++;
            printf("clicks: %d\n", data->clicks);
            if (data->clicks % 2 != 0)
            {
                data->scale = SCALE * 2;
                data->turn_speed = ROT_SPEED * 1.5;
                data->move_speed = MOVE_SPEED * 1.5;
                data->player_radius = PLAYER_RADIUS;
                data->minimap_radius = MINIMAP_RADIUS * 3.8;
                data->minimap_x_center = MAP_MID_X;
                data->minimap_y_center = MAP_MID_Y;
                // click_animation(data); // TODO
            }
            else
            {
                data->scale = SCALE;
                data->turn_speed = ROT_SPEED;
                data->move_speed = MOVE_SPEED;
                data->player_radius = PLAYER_RADIUS;
                data->minimap_radius = MINIMAP_RADIUS;
                data->minimap_x_center = MINIMAP_MID_X;
                data->minimap_y_center = MINIMAP_MID_Y;
            }
        }
        printf("Left click!\n");
    }
    else if (button == MIDDLE_CLICK)
        printf("Middle click!\n");
    else if (button == RIGHT_CLICK)
        printf("Right click!\n");
    else if (button == SCROLL_UP)
    {
        // data->scale += 0.2;
        // data->minimap_radius += 1;
        printf("Zooming in!\n");
    }
    else if (button == SCROLL_DOWN)
    {
        // data->scale -= 0.2;
        // data->minimap_radius -= 1;
        printf("Zooming out!\n");
    }
    return 0;
}
