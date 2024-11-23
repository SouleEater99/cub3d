/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 08:56:36 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/21 11:28:14 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_vert_line(t_image *image, int x, int draw_start, int draw_end, int color)
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
		if (data->map_x < 0 || data->map_x >= data->map_.map_line_len[data->map_y] || data->map_y < 0 // data->map_x >= data->map_width
			|| data->map_y >= data->map_.map_height)
			break ; // we hit the border walls.
		if (data->map_.map[data->map_y][data->map_x] == '1')
			hit = 1; // break ; we hit a wall;
	}
}

int apply_shadow(int color, double shadow_factor)
{
	int r = color >> 16 & 0xFF;
	int g = color >> 8 & 0xFF;
	int b = color & 0xFF;


	r = (int)(r * shadow_factor);
	g = (int)(g * shadow_factor);
	b = (int)(b * shadow_factor);

	r = r > 255 ? 255 : r;
    g = g > 255 ? 255 : g;
    b = b > 255 ? 255 : b;

	return (r << 16 | (g << 8) | b);
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

	double ambient_light = 0.1;
	double shadow_factor = fmax(ambient_light, 1.0 / (data->perp_wall_dist + 1.0)); // Calculate shadow factor
	// double shadow_factor = fmin(1.0, fmax(0.3, 1.0 / (data->perp_wall_dist + 0.5)));

	color = apply_shadow(color, shadow_factor);
	
	printf("Distance: %lf, Shadow Factor: %lf\n", data->perp_wall_dist, shadow_factor);
	
	data->line_height = (int)(SCREEN_HEIGHT / data->perp_wall_dist);
	data->draw_start = -data->line_height / 2 + SCREEN_HEIGHT / 2 + data->mouse_y - SCREEN_HEIGHT / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = data->line_height / 2 + SCREEN_HEIGHT / 2 + data->mouse_y - SCREEN_HEIGHT / 2;
	if (data->draw_end >= SCREEN_HEIGHT)
		data->draw_end = SCREEN_HEIGHT - 1;
	draw_vert_line(data->image, x, 0, data->draw_start, data->map_.ceiling_color); //CLR_SKY
	draw_vert_line(data->image, x, data->draw_start, data->draw_end, color);
	draw_vert_line(data->image, x, data->draw_end, SCREEN_HEIGHT, data->map_.floor_color); //CLR_FLR
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

void raycasting(t_data *data)
{
	int	x;
	
	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		data->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;

		// printf("camera_x: %lf\n", data->camera_x);
		// printf("ray_dir_x: %lf\n", data->ray_dir_x);
		// printf("ray_dir_y: %lf\n", data->ray_dir_y);

		// if x = 0 we'll get the leftmost ray direction and if x = SCREEN_WIDTH we'll get the rightmost ray direction.
		data->ray_dir_x = data->dir_x + data->plane_x * data->camera_x;
		// the direction of the ray.
		data->ray_dir_y = data->dir_y + data->plane_y * data->camera_x;
		// the direction of the ray. the player postions tell us which cell we are in and where in this cell exactly.
		data->map_x = (int)data->player_x;
		// the x player position in the map grid that tell us which grid cell we are in.
		data->map_y = (int)data->player_y;
		// the y player position in the map grid that tell us which grid cell we are in.
		
		data->delta_dist_x = (data->ray_dir_x == 0) ? 1e30 : fabs(1 / data->ray_dir_x);
		data->delta_dist_y = (data->ray_dir_y == 0) ? 1e30 : fabs(1 / data->ray_dir_y);
		
		// printf("delta dist x: %lf | delta dist y: %lf\n", data->delta_dist_x, data->delta_dist_y);

		calculate_side_dist_x_y(data);
		dda_algorithm(data); // DDA algorithm
		draw_vert_cols(data, x);
	}
}

void	start_game(t_data *data)
{
	data->image = create_image(data);
	if (data->clicks % 2 == 0)
		raycasting(data);
	draw_minimap(data);		// draw the mini-map

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image->img_ptr,
		0, 0);
	mlx_destroy_image(data->mlx_ptr, data->image->img_ptr);
	free(data->image);
	data->image = NULL;
}

// #include <math.h>
// #include <stdlib.h>

// /* Constants for improved readability */
// #define TEXTURE_SIZE 64
// #define MAX_TEXTURE_DISTANCE 8.0
// #define MIN_TEXTURE_DISTANCE 1.0

// /* Texture mapping helper functions */
// static void calculate_wall_height(t_data *data)
// {
//     // Calculate perpendicular wall distance to avoid fisheye effect
//     if (data->side == 0)
//         data->perp_wall_dist = (data->side_dist_x - data->delta_dist_x);
//     else
//         data->perp_wall_dist = (data->side_dist_y - data->delta_dist_y);
    
//     // Calculate wall height and drawing boundaries
//     data->line_height = (int)(SCREEN_HEIGHT / data->perp_wall_dist);
//     data->draw_start = -data->line_height / 2 + SCREEN_HEIGHT / 2;
//     data->draw_start = (data->draw_start < 0) ? 0 : data->draw_start;
//     data->draw_end = data->line_height / 2 + SCREEN_HEIGHT / 2;
//     data->draw_end = (data->draw_end >= SCREEN_HEIGHT) ? SCREEN_HEIGHT - 1 : data->draw_end;
// }

// static void calculate_texture_coordinates(t_data *data, t_texture *texture, 
//                                        double *wall_x, int *tex_x)
// {
//     // Calculate where exactly the wall was hit
//     *wall_x = (data->side == 0) 
//         ? data->player_y + data->perp_wall_dist * data->ray_dir_y
//         : data->player_x + data->perp_wall_dist * data->ray_dir_x;
//     *wall_x -= floor(*wall_x);  // Get fractional part

//     // Calculate x coordinate on the texture
//     *tex_x = (int)(*wall_x * (double)texture->width);
//     if ((data->side == 0 && data->ray_dir_x > 0) || 
//         (data->side == 1 && data->ray_dir_y < 0))
//         *tex_x = texture->width - *tex_x - 1;
// }

// static void draw_textured_wall(t_data *data, int x, int tex_x, t_texture *texture)
// {
//     // Input validation
//     if (data->draw_end <= data->draw_start || !texture || !texture->data ||
//         tex_x < 0 || tex_x >= texture->width)
//         return;

//     // Calculate texture step and starting position
//     double step = (double)texture->height / (data->draw_end - data->draw_start);
//     double tex_pos = 0.0;

//     // Draw the textured wall slice
//     for (int y = data->draw_start; y < data->draw_end; y++)
//     {
//         int tex_y = (int)tex_pos & (texture->height - 1);
//         tex_pos += step;

//         // Get texture color
//         int tex_offset = tex_y * texture->width + tex_x;
//         if (tex_offset >= 0 && tex_offset < texture->width * texture->height)
//         {
//             int color = texture->data[tex_offset];
            
//             // Apply distance-based shading for depth perception
//             if (data->perp_wall_dist > MIN_TEXTURE_DISTANCE)
//             {
//                 double shade = MIN_TEXTURE_DISTANCE / 
//                     fmin(data->perp_wall_dist, MAX_TEXTURE_DISTANCE);
//                 int r = (int)(((color >> 16) & 0xFF) * shade);
//                 int g = (int)(((color >> 8) & 0xFF) * shade);
//                 int b = (int)((color & 0xFF) * shade);
//                 color = (r << 16) | (g << 8) | b;
//             }
            
//             put_pixel_in_img(data->image, x, y, color);
//         }
//     }
// }

// /* DDA (Digital Differential Analysis) implementation */
// static void dda_algorithm(t_data *data)
// {
//     int hit = 0;
//     while (hit == 0)
//     {
//         // Jump to next map square in x or y direction
//         if (data->side_dist_x < data->side_dist_y)
//         {
//             data->side_dist_x += data->delta_dist_x;
//             data->map_x += data->step_x;
//             data->side = 0;
//         }
//         else
//         {
//             data->side_dist_y += data->delta_dist_y;
//             data->map_y += data->step_y;
//             data->side = 1;
//         }

//         // Check if ray has hit a wall or map boundary
//         if (data->map_x < 0 || data->map_x >= data->map_line_len[data->map_y] || 
//             data->map_y < 0 || data->map_y >= data->map_height)
//             break;  // Hit map boundary
        
//         if (data->map[data->map_y][data->map_x] == '1')
//             hit = 1;  // Hit wall
//     }
// }

// /* Main raycasting function */
// void raycasting(t_data *data)
// {
//     t_texture *wall_texture = load_texture(data->mlx_ptr, 
//         "textures/north_wall.xpm");
//     if (!wall_texture)
//         return;  // Handle texture loading failure

//     // Cast rays for each vertical screen line
//     for (int x = 0; x < SCREEN_WIDTH; x++)
//     {
//         // Calculate ray position and direction
//         data->camera_x = 2.0 * x / (double)SCREEN_WIDTH - 1.0;
//         data->ray_dir_x = data->dir_x + data->plane_x * data->camera_x;
//         data->ray_dir_y = data->dir_y + data->plane_y * data->camera_x;

//         // Set initial ray position
//         data->map_x = (int)data->player_x;
//         data->map_y = (int)data->player_y;

//         // Calculate ray step sizes
//         data->delta_dist_x = fabs(data->ray_dir_x) < 1e-20 ? 1e30 : 
//             fabs(1.0 / data->ray_dir_x);
//         data->delta_dist_y = fabs(data->ray_dir_y) < 1e-20 ? 1e30 : 
//             fabs(1.0 / data->ray_dir_y);

//         // Calculate ray steps and initial side distances
//         calculate_side_dist_x_y(data);
        
//         // Perform DDA
//         dda_algorithm(data);

//         // Calculate wall height and drawing bounds
//         calculate_wall_height(data);

//         // Calculate texture coordinates
//         double wall_x;
//         int tex_x;
//         calculate_texture_coordinates(data, wall_texture, &wall_x, &tex_x);

//         // Draw the textured wall slice
// 		draw_vert_line(data->image, x, 0, data->draw_start, CLR_SKY);
//         draw_textured_wall(data, x, tex_x, wall_texture);
// 		draw_vert_line(data->image, x, data->draw_end, SCREEN_HEIGHT, CLR_FLR);
//     }

//     free(wall_texture);
// }

// /* Game rendering function */
// void start_game(t_data *data)
// {
//     data->image = create_image(data);
//     if (!data->image)
//         return;  // Handle image creation failure

//     if (data->clicks % 2 == 0)
//         raycasting(data);
        
//     draw_mini_map(data);

//     // Display the rendered image
//     mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, 
//         data->image->img_ptr, 0, 0);
        
//     // Cleanup
//     mlx_destroy_image(data->mlx_ptr, data->image->img_ptr);
//     free(data->image);
//     data->image = NULL;
// }