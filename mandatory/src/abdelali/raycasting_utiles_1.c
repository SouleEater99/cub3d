/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utiles_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:45:38 by heisenberg        #+#    #+#             */
/*   Updated: 2024/11/29 10:23:44 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

double	rad_to_deg(double rad_angle)
{
	return (rad_angle * 180 / PI);
}

double	deg_to_rad(double deg_angle)
{
	return (deg_angle * PI / 180);
}

void	ft_write_floor(t_data *data, int i, int color)
{
	int		j;
	double	distance;
	int		shaded_color;

	j = data->end;
	while (j < HIGH)
	{
		distance = (j - HIGH / 2) / (double)(HIGH / 2);
		distance = 1 / distance;
		// shaded_color = color;
		shaded_color = shade_walls(color, distance);
		my_mlx_pixel_put(&data->projection_img, i * WALL_STRIP, j++,
			shaded_color);
	}
}

void	ft_write_ceiling(t_data *data, int i, int color)
{
	int		j;
	double	distance;
	int		shaded_color;

	j = 0;
	while (j < data->start)
	{
		distance = (HIGH / 2 - j) / (double)(HIGH / 2);
		distance = 1 / (distance);
		// shaded_color = color;
		shaded_color = shade_walls(color, distance);
		my_mlx_pixel_put(&data->projection_img, i * WALL_STRIP, j++,
			shaded_color);
	}
}

double	ft_calc_distance(t_data *data, double x, double y)
{
	double	dx;
	double	dy;

	dx = data->x_player - x;
	dy = data->y_player - y;
	return (sqrt(dx * dx + dy * dy));
}
