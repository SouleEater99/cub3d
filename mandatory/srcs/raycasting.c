/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 08:56:36 by aelkheta          #+#    #+#             */
/*   Updated: 2024/10/22 09:20:09 by aelkheta         ###   ########.fr       */
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

// void draw_tile(t_image *image, int x, int y, int color)
// {
//     int i = x;
//     int j = y;
//     while(i < x + TILE_SIZE - 1)
//     {
//         j = y;
//         while (j < y + TILE_SIZE - 1)
//         {
//             put_pixel_in_img(image, i + CENTER, j, color);
//             j++;
//         }
//         i++;
//     }
// }

// void draw_map(t_data *data, t_image *image)
// {
//     int i = 0;
//     int j = 0;
    
//     while (i < MAP_HEIGHT)
//     {
//         j = 0;
//         while (j < MAP_WIDTH)
//         {
//             if (data->map[i][j] == '1')
//                 draw_tile(image, j * TILE_SIZE, i * TILE_SIZE, 0x000000);
//             else if (data->map[i][j] == '0' || data->map[i][j] == '0')
//                 draw_tile(image, j * TILE_SIZE, i * TILE_SIZE, 0xFFFFFF); //0xAAAAAA
//             j++;
//         }
//         i++;   
//     }
// }

// void draw_mini_map(t_data *data)
// {
// 	draw_map(data, data->image);
	    
// 	int x = -1;
//     while (++x < SCREEN_WIDTH)
//     {
//         data->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;

//         data->ray_dir_x = data->dir_x + data->plane_x * data->camera_x;
//         data->ray_dir_y = data->dir_y + data->plane_y * data->camera_x;

//         int end_x = data->player_x * TILE_SIZE + data->ray_dir_x * 500;
//         int end_y = data->player_y * TILE_SIZE + data->ray_dir_y * 500;

//         draw_line(data, data->image, end_x, end_y, 0xFF0000); //0xFFFFFF
//     }
// }

// void draw_line(t_data *data, t_image *image, int end_x, int end_y, int color)
// {
//     int dx = end_x - data->player_x * TILE_SIZE;
//     int dy = end_y - data->player_y * TILE_SIZE;

//     double steps = fmax(abs(dx), abs(dy));

//     double x_increment = (double)dx / steps;
//     double y_increment = (double)dy / steps;

//     double x = data->player_x * TILE_SIZE;
//     double y = data->player_y * TILE_SIZE;

//     for (int i = 0; i <= steps; i++)
//     {
//         int map_x = (int)(x / TILE_SIZE);
//         int map_y = (int)(y / TILE_SIZE);

//         if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT)
//             break;

//         if (data->map[map_y][map_x] == '1')
//             break;

//         // mlx_pixel_put(data->mlx_ptr, data->win_ptr, round(x), round(y), color);
//         put_pixel_in_img(image, round(x) + CENTER, round(y), color);
//         x += x_increment;
//         y += y_increment;
//     }
// }

// =========================================================================== //

# define MINIMAP_RADIUS 80
# define MINIMAP_POS_X (SCREEN_WIDTH - MINIMAP_RADIUS - 20)
# define MINIMAP_POS_Y (MINIMAP_RADIUS + 20)

void draw_black_bg(t_data *data)
{
	int y = - MINIMAP_RADIUS - 1;
	while(++y <= MINIMAP_RADIUS)
	{
		int x = - MINIMAP_RADIUS - 1;
		while(++x <= MINIMAP_RADIUS)
		{
			double dist = sqrt(x * x + y * y);
			if (dist <= MINIMAP_RADIUS)
			{
				int screen_x = MINIMAP_POS_X + x;
				int screen_y = MINIMAP_POS_Y + y;
 	        	put_pixel_in_img(data->image, screen_x, screen_y, 0x222222);	
			}
		}
	}
}

void draw_tile(t_image *image, double x, double y, int color, t_data *data, double scale)
{
    int size = (int)(TILE_SIZE * scale);
	
    // Calculate screen position relative to player's position
    double screen_x = MINIMAP_POS_X + (x - data->player_x * size);
    double screen_y = MINIMAP_POS_Y + (y - data->player_y * size);
    
	int i = -1;
    while (++i < size)
    {
		int j = -1;
        while (++j < size)
        {
            double pixel_x = screen_x + i;
            double pixel_y = screen_y + j;
            
            // Calculate distance from minimap center
            double dx = pixel_x - MINIMAP_POS_X;
            double dy = pixel_y - MINIMAP_POS_Y;
            double distance = sqrt(dx * dx + dy * dy);
            
            // Only draw if inside the circle
            if (distance <= MINIMAP_RADIUS)
                put_pixel_in_img(image, pixel_x, pixel_y, color);
        }
    }
}

void draw_map(t_data *data, t_image *image)
{
    // Calculate scale factor
    double scale = 0.5;
    
    // we calculate the visible range (in map tiles)
    int visible_range = (int)(MINIMAP_RADIUS / (TILE_SIZE * scale)) + 1;
    
    // here we calculate the player's position in map coordinates
    int player_map_x = (int)data->player_x;
    int player_map_y = (int)data->player_y;
    
    // Draw only the visible portion of the map
    int dy = -visible_range - 1;
	while (++dy <= visible_range)
    {
		int dx = -visible_range;
        while (++dx <= visible_range)
        {
            int map_x = player_map_x + dx;
            int map_y = player_map_y + dy;
            
            // Check if the tile is within map bounds
            if (map_x >= 0 && map_x < MAP_WIDTH && map_y >= 0 && map_y < MAP_HEIGHT)
            {
                double tile_x = map_x * TILE_SIZE * scale;
                double tile_y = map_y * TILE_SIZE * scale;
                
                if (data->map[map_y][map_x] == '1')
                    draw_tile(image, tile_x, tile_y, 0x000000, data, scale);
                else if (data->map[map_y][map_x] == '0')
                    draw_tile(image, tile_x, tile_y, 0xAAAAAA, data, scale);
            }
        }
    }
}

void draw_player_direction(t_data *data, t_image *image)
{
    // Draw direction indicator
    double angle = atan2(data->dir_y, data->dir_x);
    double fov = 60 * PI / 180.0; // 60 degrees FOV
    int i = -30 - 1;
    while (++i <= 30)
    {
        double ray_angle = angle + (i * fov / 60);
        double ray_length = MINIMAP_RADIUS * 0.3; // Length of direction indicator
        
        double end_x = MINIMAP_POS_X + cos(ray_angle) * ray_length;
        double end_y = MINIMAP_POS_Y + sin(ray_angle) * ray_length;
        
        // Draw ray line
        double dx = end_x - MINIMAP_POS_X;
        double dy = end_y - MINIMAP_POS_Y;
        double steps = fmax(fabs(dx), fabs(dy));
        
        if (steps == 0)
			continue;
        
        double x_increment = dx / steps;
        double y_increment = dy / steps;
        double x = MINIMAP_POS_X;
        double y = MINIMAP_POS_Y;
        
		int step = -1;
        while (++step <= steps)
        {
            double dist_x = x - MINIMAP_POS_X;
            double dist_y = y - MINIMAP_POS_Y;
			
            if (sqrt(dist_x * dist_x + dist_y * dist_y) <= MINIMAP_RADIUS)
                put_pixel_in_img(image, round(x), round(y), 0xFF0000);
            x += x_increment;
            y += y_increment;
        }
    }
}

void draw_mini_map(t_data *data)
{
    // draw black background for our minimap
	draw_black_bg(data);
    
    draw_map(data, data->image); // draw the map (floor and walls)
    
    // Draw the player's vield od view
    draw_player_direction(data, data->image);
    
    // Draw the player dot (or just the player)	// TODO
    // draw_player(data->image);
    
    // Draw the minimap border	// TODO
    // draw_minimap_border(data->image);
}

// ========================================================================= //

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

	draw_mini_map(data);		// draw the mini-map

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image->img_ptr,
		0, 0);
	mlx_destroy_image(data->mlx_ptr, data->image->img_ptr);
	free(data->image);
}
