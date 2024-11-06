/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:17:16 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/01 10:27:18 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	key_press(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
	{
		clean_up(data);
		exit(0);
	}
	else if (keycode == 'w' || keycode == U_KEY)
		data->move_forward = 1;
	else if (keycode == 's' || keycode == D_KEY)
		data->move_backward = 1;
	else if (keycode == 'a' || keycode == L_KEY)
		data->rotate_left = 1;
	else if (keycode == 'd' || keycode == R_KEY)
		data->rotate_right = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == 'w' || keycode == U_KEY)
		data->move_forward = 0;
	else if (keycode == 's' || keycode == D_KEY)
		data->move_backward = 0;
	else if (keycode == 'a' || keycode == L_KEY)
		data->rotate_left = 0;
	else if (keycode == 'd' || keycode == R_KEY)
		data->rotate_right = 0;
	return (0);
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

#include <unistd.h> // For usleep function

void click_animation(t_data *data)
{
    int original_radius = data->minimap_radius;

    data->minimap_radius = original_radius - 4;
    draw_mini_map(data);

    data->minimap_radius = original_radius + 4;
    draw_mini_map(data);

    data->minimap_radius = original_radius;
    draw_mini_map(data);
}

int mouse_events(int button, int x, int y, t_data *data)
{
    printf("Button %d pressed at (%d, %d)\n", button, x, y);
    if (button == LEFT_CLICK)
    {
		if (check_click_space(data, x, y))
	        data->clicks++;
        if (data->clicks % 2 != 0 && check_click_space(data, x, y))
        {
            data->scale = SCALE * 2;
        	data->rot_speed = ROT_SPEED * 6;
            data->move_speed = MOVE_SPEED * 6;
            data->player_radius = PLAYER_RADIUS;
            data->minimap_radius = MINIMAP_RADIUS * 10;
            data->minimap_x_center = MAP_MID_X;
            data->minimap_y_center = MAP_MID_Y;
            // click_animation(data); // TODO
        }
        else
        {
            data->scale = SCALE;
        	data->rot_speed = ROT_SPEED;
            data->move_speed = MOVE_SPEED;
            data->player_radius = PLAYER_RADIUS;
            data->minimap_radius = MINIMAP_RADIUS;
            data->minimap_x_center = MINIMAP_MID_X;
            data->minimap_y_center = MINIMAP_MID_Y;
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


int	game_loop(t_data *data)
{
	// mouse_positions(data);
	update_player(data);
	start_game(data);
	return (0);
}

int destroy_notify(t_data *data)
{
	clean_up(data);
	return (exit (0), 0);
}
