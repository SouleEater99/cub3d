/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 08:56:36 by aelkheta          #+#    #+#             */
/*   Updated: 2024/10/13 18:40:25 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cub3d.h>

void draw_vert_line(t_image *image, int x, int draw_start, int draw_end, int color)
{
    int y = draw_start -1;
    while(++y < draw_end)
    {
        if(x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
            put_pixel_in_img(image, x, y, color);
    }    
}

void raycasting(t_data *data)
{
    data->image = create_image(data);
    
    int x = -1;
    while (++x < SCREEN_WIDTH)
    {
        data->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
        // if x = 0 we'll get the leftmost ray direction and if x = SCREEN_WIDTH we'll get the rightmost ray direction.
        data->ray_dir_x = data->dir_x + data->plane_x * data->camera_x; // the direction of the ray.
        data->ray_dir_y = data->dir_y + data->plane_y * data->camera_x; // the direction of the ray.

        // the player postions tell us which cell we are in and where in this cell exactly.
        data->map_x = (int)data->player_x;  // the x player position in the map grid that tell us which grid cell we are in.
        data->map_y = (int)data->player_y;  // the y player position in the map grid that tell us which grid cell we are in.
    
        double side_dist_x;
        double side_dist_y;

        double delta_dist_x = fabs(1 / data->ray_dir_x);
        double delta_dist_y = fabs(1 / data->ray_dir_y);

        double perp_wall_dist;

        int step_x;
        int step_y;
        
        int hit = 0;
        int side;

        if (data->ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (data->player_x - data->map_x) * delta_dist_x; 
        }
        else
        {
            step_x = 1;
            side_dist_x = (data->map_x + 1.0 - data->player_x) * delta_dist_x;
        }

        if (data->ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (data->player_y - data->map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (data->map_y + 1.0 - data->player_y) * delta_dist_y;
        }

        while (hit == 0)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                data->map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                data->map_y += step_y;
                side = 1;
            }
            if (data->map_x < 0 || data->map_x >= MAP_WIDTH || data->map_y < 0 || data->map_y >= MAP_HEIGHT)
                break; // we hit the border walls.
                
            if (data->map[data->map_y][data->map_x] == '1')
                hit = 1; // break; we hit a wall;
        }
        
        if (side == 0)
            perp_wall_dist = side_dist_x - delta_dist_x;
        else
            perp_wall_dist = side_dist_y - delta_dist_y;
        
        int color = 0xFFFFFF;
        if (side == 0)
        {
            if (step_x > 0)         // this is mean the player look to the right or the East
                color = 0xFF0000;   // red color
            else                    // this is mean the player look to the left or the West
                color = 0x00FF00;   // green color
        }
        else
        {
            if (step_y > 0)         // this is mean the player look to the bottom or the South
                color = 0x0000FF;   // blue color
            else                    // this is mean the player look to the top or the South
                color = 0xFFFF00;   // yellow color

        }
        
        int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);

        int draw_start = - line_height / 2 + SCREEN_HEIGHT / 2;
        if (draw_start < 0)
            draw_start = 0;
            
        int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
        if(draw_end >= SCREEN_HEIGHT)
            draw_end = SCREEN_HEIGHT - 1;

        draw_vert_line(data->image, x, 0, draw_start, 0xFFFFFF);
        draw_vert_line(data->image, x, draw_start, draw_end, color);
        draw_vert_line(data->image, x, draw_end, SCREEN_HEIGHT, 0xFFFFFF);
    }
    
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image->img_ptr, 0, 0);
    mlx_destroy_image(data->mlx_ptr, data->image->img_ptr);
    
    free(data->image);
}
