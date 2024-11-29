/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:30:04 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/29 09:47:43 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_is_player_inside_wall(t_data *data)
{
	int		x;
	int		y;
	double	new_x;
	double	new_y;

	new_x = (data->x_player + (cos(data->player_angle) * data->move_step));
	new_y = (data->y_player + (sin(data->player_angle) * data->move_step));
	x = (int)data->x_player / CUBE_TILE;
	y = (int)data->y_player / CUBE_TILE;
	if (data->map.map[y][(int)new_x / CUBE_TILE] == '0')
		data->x_player = new_x;
	if (data->map.map[(int)new_y / CUBE_TILE][x] == '0')
		data->y_player = new_y;
	return (1);
}

double	ft_normalize_angle(double angle)
{
	if (angle > 2 * PI)
		angle -= 2 * PI;
	else if (angle < 0)
		angle += 2 * PI;
	return (angle);
}

void	ft_write_line(t_data *data, int dx, int dy, int color)
{
	double	x;
	double	y;
	double	x_increment;
	double	y_increment;

	if (abs(dx) >= abs(dy))
		data->step = abs(dx);
	else
		data->step = abs(dy);
	x_increment = dx / data->step;
	y_increment = dy / data->step;
	x = (unsigned int)data->x_player * data->factor_scale_map;
	y = (unsigned int)data->y_player * data->factor_scale_map;
	data->i = 0;
	while (data->i <= data->step)
	{
		if (ft_board_protect(WIDTH, HIGH, x, y))
			my_mlx_pixel_put(&data->projection_img, x, y, color);
		x += x_increment;
		y += y_increment;
		data->i++;
	}
}
