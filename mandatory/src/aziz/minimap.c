/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:31:22 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/28 10:41:25 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_background(t_data *data, t_image *image)
{
	int		y;
	int		x;
	double	distance;
	int		screen_x;
	int		screen_y;

	y = -data->minimap_radius - 1;
	while (++y <= data->minimap_radius)
	{
		x = -data->minimap_radius - 1;
		while (++x <= data->minimap_radius)
		{
			distance = sqrt(x * x + y * y);
			if (distance <= data->minimap_radius)
			{
				screen_x = data->minimap_x_center + x;
				screen_y = data->minimap_y_center + y;
				my_mlx_pixel_put(image, screen_x, screen_y, 0x222222);
			}
		}
	}
}

void	draw_tile(t_data *data, t_image *image, double x, double y, int color)
{
	int		di;
	int		dj;
	int		size;
	double	screen_x;
	double	screen_y;
	double	distance;

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
			distance = sqrt(pow(screen_x + di - data->minimap_x_center, 2)
					+ pow(screen_y + dj - data->minimap_y_center, 2));
			if (distance <= data->minimap_radius)
				my_mlx_pixel_put(image, screen_x + di, screen_y + dj, color);
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

void	draw_ray_line(t_data *data, t_image *image, double end_x, double end_y)
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	steps;

	dx = end_x - data->minimap_x_center;
	dy = end_y - data->minimap_y_center;
	steps = fmax(fabs(dx), fabs(dy));
	if (steps == 0)
		return ;
	data->x_increment = dx / steps;
	data->y_increment = dy / steps;
	x = data->minimap_x_center;
	y = data->minimap_y_center;
	for (int step = 0; step <= steps; step++)
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

void	draw_player_direction(t_data *data, t_image *image)
{
	double	ray_angle;
	double	ray_length;
	double	end_x;
	double	end_y;

	double fov = 60 * PI / 180.0;
	for (int i = -30; i <= 30; i++)
	{
		ray_angle = data->player_angle + (i * fov / 60);
		ray_length = MINIMAP_RADIUS * 0.3;
		end_x = data->minimap_x_center + cos(ray_angle) * ray_length;
		end_y = data->minimap_y_center + sin(ray_angle) * ray_length;
		draw_ray_line(data, image, end_x, end_y);
	}
}

void	draw_map(t_data *data, t_image *image)
{
	int		dy;
	int		dx;
	int		map_x;
	int		map_y;
	double	tile_x;
	double	tile_y;
	int		visible_range;

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
			// Check if the tile is within map bounds
			if (map_x >= 0 && map_y >= 0 && map_y < data->map.map_height
				&& map_x < data->map.map_line_len[map_y]
				&& data->map.map[map_y] != NULL)
			{
				tile_x = map_x * TILE_SIZE * data->scale;
				tile_y = map_y * TILE_SIZE * data->scale;
				if (data->map.map[map_y][map_x] == '1')
					draw_tile(data, image, tile_x, tile_y, 0x000000);
				else if (data->map.map[map_y][map_x] == '0')
					draw_tile(data, image, tile_x, tile_y, 0xAAAAAA);
				else if (data->map.map[map_y][map_x] == 'D')
					draw_tile(data, image, tile_x, tile_y, 0x4278f5);
			}
		}
	}
}

void	draw_minimap(t_data *data)
{
	// draw black background for our minimap
	draw_background(data, &data->projection_img);
	// draw the map (floor and walls)
	draw_map(data, &data->projection_img);
	// Draw the player's vield od view
	draw_player_direction(data, &data->projection_img);
	// Draw the player dot (or just the player)	// TODO
	draw_player(data, &data->projection_img);
	// Draw the minimap border	// TODO
	// draw_minimap_border(data->image);
}
