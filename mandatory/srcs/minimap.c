/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:31:22 by aelkheta          #+#    #+#             */
/*   Updated: 2024/10/23 19:07:37 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cub3d.h>

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
            if (map_x >= 0 && map_x < data->map_width && map_y >= 0 && map_y < data->map_height)
            {
                double tile_x = map_x * TILE_SIZE * scale;
                double tile_y = map_y * TILE_SIZE * scale;
                
                if (data->map[map_y][map_x] == '1')
                    draw_tile(image, tile_x, tile_y, 0x000000, data, scale);
                else if (data->map[map_y][map_x] == '0' || data->map[map_y][map_x] == 'N')
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

void draw_minimap_border(t_image *image)
{
    // Draw circular border
    int y = -MINIMAP_RADIUS;
	while (++y <= MINIMAP_RADIUS)
    {
	    int x = -MINIMAP_RADIUS;
		while (++x <= MINIMAP_RADIUS)
        {
            double distance = sqrt(x * x + y * y);
            if (distance <= MINIMAP_RADIUS + 2 && distance >= MINIMAP_RADIUS - 2)
            {
                int screen_x = MINIMAP_POS_X + x;
                int screen_y = MINIMAP_POS_Y + y;
                put_pixel_in_img(image, screen_x, screen_y, 0xaaaaaa);
            }
        }
	}   
}

void draw_player(t_image *image)
{
    int player_x = MINIMAP_POS_X;
    int player_y = MINIMAP_POS_Y;

    // Draw the player as a small circle
    int radius = 3; // Size of the player dot
    int y = -radius - 1;
    while (++y <= radius)
    {
        int x = -radius - 1;
        while (++x <= radius)
        {
            double distance = sqrt(x * x + y * y);
            if (distance <= radius)
            {
                int screen_x = player_x + x;
                int screen_y = player_y + y;
                put_pixel_in_img(image, screen_x, screen_y, 0xe6ff05); // 0x00FF00 Green color for the player
            }
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
    draw_player(data->image);
    
    // Draw the minimap border	// TODO
    // draw_minimap_border(data->image);
}
