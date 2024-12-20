/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 19:03:55 by heisenberg        #+#    #+#             */
/*   Updated: 2024/12/04 14:18:57 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	mouse_hooks(t_data *data)
{
	int	x;
	int	y;
	int	delta_x;

	if (!data || !data->win_ptr)
		return ;
	mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr, &x, &y);
	delta_x = data->mouse_x - x;
	if (x < 0 || x > SCREEN_WIDTH || y < 0 || y > SCREEN_HEIGHT)
		return ;
	if (x != data->mouse_x)
	{
		data->sensitivity = MOUSE_SENSITIVITY;
		data->player_angle += (delta_x * data->sensitivity) * -1;
	}
	data->mouse_x = x;
	data->mouse_y = y;
}

int	check_click_space(t_data *data, int x, int y)
{
	int		dx;
	int		dy;
	double	distance;

	dx = x - data->minimap_x_center;
	dy = y - data->minimap_y_center;
	distance = sqrt(dx * dx + dy * dy);
	if (distance <= data->minimap_radius)
		return (1);
	return (0);
}

void	big_minimap(t_data *data)
{
	data->scale = SCALE * 2;
	data->turn_speed = ROT_SPEED * 1.5;
	data->move_speed = MOVE_SPEED * 1.5;
	data->player_radius = PLAYER_RADIUS;
	data->minimap_radius = MINIMAP_RADIUS * 3.8;
	data->minimap_x_center = SCREEN_WIDTH / 2;
	data->minimap_y_center = SCREEN_HEIGHT / 2;
}

void	small_minimap(t_data *data)
{
	data->scale = SCALE;
	data->turn_speed = ROT_SPEED;
	data->move_speed = MOVE_SPEED;
	data->player_radius = PLAYER_RADIUS;
	data->minimap_radius = MINIMAP_RADIUS;
	data->minimap_x_center = SCREEN_WIDTH - MINIMAP_RADIUS - 20;
	data->minimap_y_center = MINIMAP_RADIUS + 20;
}

int	mouse_events(int button, int x, int y, t_data *data)
{
	printf("Button %d pressed at (%d, %d)\n", button, x, y);
	if (button == RIGHT_CLICK)
	{
		if (check_click_space(data, x, y))
		{
			data->clicks++;
			if (data->clicks % 2 != 0)
				big_minimap(data);
			else
				small_minimap(data);
		}
	}
	else if (button == LEFT_CLICK)
		data->shoot = 1;
	return (0);
}
