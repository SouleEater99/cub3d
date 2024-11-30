/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:54:14 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/28 13:00:43 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	draw_tile(t_data *data, double x, double y, int color)
{
	int		di;
	int		dj;
	int		size;
	double	screen_x;
	double	screen_y;

	size = (int)(TILE_SIZE * data->scale);
	screen_x = data->minimap_x_center + (x - data->player_x * TILE_SIZE
			* data->scale);
	screen_y = data->minimap_y_center + (y - data->player_y * TILE_SIZE
			* data->scale);
	di = -1;
	while (++di < size)
	{
		dj = -1;
		while (++dj < size)
		{
			data->distance = sqrt(pow(screen_x + di - data->minimap_x_center, 2)
					+ pow(screen_y + dj - data->minimap_y_center, 2));
			if (data->distance <= data->minimap_radius)
				my_mlx_pixel_put(data->image, screen_x + di, screen_y + dj,
					color);
		}
	}
}

void	draw_ray_line(t_data *data, t_image *image, double end_x, double end_y)
{
	double	x;
	double	y;
	double	dx;
	double	dy;

	dx = end_x - data->minimap_x_center;
	dy = end_y - data->minimap_y_center;
	data->steps = fmax(fabs(dx), fabs(dy));
	if (data->steps == 0)
		return ;
	data->x_increment = dx / data->steps;
	data->y_increment = dy / data->steps;
	x = data->minimap_x_center;
	y = data->minimap_y_center;
	data->step = -1;
	while (++data->step <= data->steps)
	{
		data->dist_x = x - data->minimap_x_center;
		data->dist_y = y - data->minimap_y_center;
		if (sqrt(data->dist_x * data->dist_x + data->dist_y
				* data->dist_y) <= MINIMAP_RADIUS)
			my_mlx_pixel_put(image, round(x), round(y), 0xFF0000);
		x += data->x_increment;
		y += data->y_increment;
	}
}

void	draw_tile_within_bounds(t_data *data, int map_x, int map_y)
{
	double	tile_x;
	double	tile_y;

	if (map_x >= 0 && map_y >= 0 && map_y < data->map.map_height
		&& map_x < data->map.map_line_len[map_y])
	{
		tile_x = map_x * TILE_SIZE * data->scale;
		tile_y = map_y * TILE_SIZE * data->scale;
		if (data->map.map[map_y][map_x] == '1')
			draw_tile(data, tile_x, tile_y, 0x000000);
		else if (data->map.map[map_y][map_x] == '0')
			draw_tile(data, tile_x, tile_y, 0xAAAAAA);
		else if (data->map.map[map_y][map_x] == 'D')
			draw_tile(data, tile_x, tile_y, 0x4278f5);
	}
}
