/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:31:22 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/28 13:07:52 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_background(t_data *data, t_image *image)
{
	int	y;
	int	x;
	int	screen_x;
	int	screen_y;

	y = -data->minimap_radius - 1;
	while (++y <= data->minimap_radius)
	{
		x = -data->minimap_radius - 1;
		while (++x <= data->minimap_radius)
		{
			data->distance = sqrt(x * x + y * y);
			if (data->distance <= data->minimap_radius)
			{
				screen_x = data->minimap_x_center + x;
				screen_y = data->minimap_y_center + y;
				my_mlx_pixel_put(image, screen_x, screen_y, 0x222222);
			}
		}
	}
}

void	draw_player(t_data *data, t_image *image)
{
	int		x;
	int		y;
	double	dist;

	x = -data->player_radius;
	while (++x <= data->player_radius)
	{
		y = -data->player_radius;
		while (++y <= data->player_radius)
		{
			dist = sqrt(x * x + y * y);
			if (dist <= data->player_radius)
				my_mlx_pixel_put(image, data->minimap_x_center + x,
					data->minimap_y_center + y, 0xFFFF00);
		}
	}
}

void	draw_player_direction(t_data *data, t_image *image)
{
	double	end_x;
	double	end_y;
	double	ray_angle;
	double	ray_length;
	int		i;

	data->fov = 60 * PI / 180.0;
	i = -30 - 1;
	while (++i <= 30)
	{
		ray_angle = data->player_angle + (i * data->fov / 60);
		ray_length = MINIMAP_RADIUS * 0.3;
		end_x = data->minimap_x_center + cos(ray_angle) * ray_length;
		end_y = data->minimap_y_center + sin(ray_angle) * ray_length;
		draw_ray_line(data, image, end_x, end_y);
	}
}

void	draw_map(t_data *data, t_image *image)
{
	int	dy;
	int	dx;
	int	map_x;
	int	map_y;
	int	visible_range;

	visible_range = (int)(data->minimap_radius / (TILE_SIZE * data->scale)) + 1;
	data->player_x = data->x_player / CUBE_TILE;
	data->player_y = data->y_player / CUBE_TILE;
	dy = -visible_range - 1;
	while (++dy <= visible_range)
	{
		dx = -visible_range - 1;
		while (++dx <= visible_range)
		{
			map_x = (int)data->player_x + dx;
			map_y = (int)data->player_y + dy;
			data->image = image;
			draw_tile_within_bounds(data, map_x, map_y);
		}
	}
}

void	draw_minimap(t_data *data)
{
	draw_background(data, &data->projection_img);
	draw_map(data, &data->projection_img);
	draw_player_direction(data, &data->projection_img);
	draw_player(data, &data->projection_img);
}
