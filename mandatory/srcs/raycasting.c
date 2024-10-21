/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 08:56:36 by aelkheta          #+#    #+#             */
/*   Updated: 2024/10/16 16:31:41 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_vert_line(t_image *image, int x, int draw_start, int draw_end,
		int color)
{
	int	y;

	y = draw_start - 1;
	while (++y < draw_end)
	{
		if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
			put_pixel_in_img(image, x, y, color);
	}
}

void	dda_algorithm(t_data *data)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (data->side_dist_x < data->side_dist_y)
		{
			data->side_dist_x += data->delta_dist_x;
			data->map_x += data->step_x;
			data->side = 0;
		}
		else
		{
			data->side_dist_y += data->delta_dist_y;
			data->map_y += data->step_y;
			data->side = 1;
		}
		if (data->map_x < 0 || data->map_x >= MAP_WIDTH || data->map_y < 0
			|| data->map_y >= MAP_HEIGHT)
			break ; // we hit the border walls.
		if (data->map[data->map_y][data->map_x] == '1')
			hit = 1; // break ; we hit a wall;
	}
}

void	draw_vert_cols(t_data *data, int x)
{
	int	color;

	color = 0xFFFFFF;
	if (data->side == 0)
		data->perp_wall_dist = data->side_dist_x - data->delta_dist_x;
	else
		data->perp_wall_dist = data->side_dist_y - data->delta_dist_y;
	if (data->side == 0)
		color = CLR_EAW;
	else
		color = CLR_SAN;
	data->line_height = (int)(SCREEN_HEIGHT / data->perp_wall_dist);
	data->draw_start = -data->line_height / 2 + SCREEN_HEIGHT / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = data->line_height / 2 + SCREEN_HEIGHT / 2;
	if (data->draw_end >= SCREEN_HEIGHT)
		data->draw_end = SCREEN_HEIGHT - 1;
	draw_vert_line(data->image, x, 0, data->draw_start, CLR_SKY);
	draw_vert_line(data->image, x, data->draw_start, data->draw_end, color);
	draw_vert_line(data->image, x, data->draw_end, SCREEN_HEIGHT, CLR_FLR);
}

void	calculate_side_dist_x_y(t_data *data)
{
	if (data->ray_dir_x < 0)
	{
		data->step_x = -1;
		data->side_dist_x = (data->player_x - data->map_x) * data->delta_dist_x;
	}
	else
	{
		data->step_x = 1;
		data->side_dist_x = (data->map_x + 1.0 - data->player_x)
			* data->delta_dist_x;
	}
	if (data->ray_dir_y < 0)
	{
		data->step_y = -1;
		data->side_dist_y = (data->player_y - data->map_y) * data->delta_dist_y;
	}
	else
	{
		data->step_y = 1;
		data->side_dist_y = (data->map_y + 1.0 - data->player_y)
			* data->delta_dist_y;
	}
}

void draw_tile(t_image *image, int x, int y, int color)
{
    int i = x;
    int j = y;
    while(i < x + TILE_SIZE - 1)
    {
        j = y;
        while (j < y + TILE_SIZE - 1)
        {
            put_pixel_in_img(image, i + CENTER, j, color);
            j++;
        }
        i++;
    }
}

void draw_map(t_data *data, t_image *image)
{
    int i = 0;
    int j = 0;
    
    while (i < MAP_HEIGHT)
    {
        j = 0;
        while (j < MAP_WIDTH)
        {
            if (data->map[i][j] == '1')
                draw_tile(image, j * TILE_SIZE, i * TILE_SIZE, 0x000000);
            else if (data->map[i][j] == '0' || data->map[i][j] == '0')
                draw_tile(image, j * TILE_SIZE, i * TILE_SIZE, 0xFFFFFF); //0xAAAAAA
            j++;
        }
        i++;   
    }
}

void draw_line(t_data *data, t_image *image, int end_x, int end_y, int color)
{
    int dx = end_x - data->player_x * TILE_SIZE;
    int dy = end_y - data->player_y * TILE_SIZE;

    double steps = fmax(abs(dx), abs(dy));

    double x_increment = (double)dx / steps;
    double y_increment = (double)dy / steps;

    double x = data->player_x * TILE_SIZE;
    double y = data->player_y * TILE_SIZE;

    for (int i = 0; i <= steps; i++)
    {
        int map_x = (int)(x / TILE_SIZE);
        int map_y = (int)(y / TILE_SIZE);

        if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT)
            break;

        if (data->map[map_y][map_x] == '1')
            break;

        // mlx_pixel_put(data->mlx_ptr, data->win_ptr, round(x), round(y), color);
        put_pixel_in_img(image, round(x) + CENTER, round(y), color);
        x += x_increment;
        y += y_increment;
    }
}

void draw_mini_map(t_data *data)
{
	draw_map(data, data->image);
	    
	int x = -1;
    while (++x < SCREEN_WIDTH)
    {
        data->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;

        data->ray_dir_x = data->dir_x + data->plane_x * data->camera_x;
        data->ray_dir_y = data->dir_y + data->plane_y * data->camera_x;

        int end_x = data->player_x * TILE_SIZE + data->ray_dir_x * 500;
        int end_y = data->player_y * TILE_SIZE + data->ray_dir_y * 500;

        draw_line(data, data->image, end_x, end_y, 0xFF0000); //0xFFFFFF
    }
}

void	raycasting(t_data *data)
{
	int	x;

	data->image = create_image(data);
	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		data->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		// if x = 0 we'll get the leftmost ray direction and if x = SCREEN_WIDTH we'll get the rightmost ray direction.
		data->ray_dir_x = data->dir_x + data->plane_x * data->camera_x;
		// the direction of the ray.
		data->ray_dir_y = data->dir_y + data->plane_y * data->camera_x;
		// the direction of the ray. the player postions tell us which cell we are in and where in this cell exactly.
		data->map_x = (int)data->player_x;
		// the x player position in the map grid that tell us which grid cell we are in.
		data->map_y = (int)data->player_y;
		// the y player position in the map grid that tell us which grid cell we are in.
		data->delta_dist_x = fabs(1 / data->ray_dir_x);
		data->delta_dist_y = fabs(1 / data->ray_dir_y);
		calculate_side_dist_x_y(data);
		dda_algorithm(data); // DDA algorithm
		draw_vert_cols(data, x);
	}

	draw_mini_map(data);			// mini-map

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image->img_ptr,
		0, 0);
	mlx_destroy_image(data->mlx_ptr, data->image->img_ptr);
	free(data->image);
}
