/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unused.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:21:58 by aelkheta          #+#    #+#             */
/*   Updated: 2024/10/16 16:10:00 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	raycasting(t_data *data)
{
	int		x;
	double	perp_wall_dist;
	int		hit;
	int		side;
	int		color;
	int		line_height;
	int		draw_start;
	int		draw_end;

	data->image = create_image(data);
	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		data->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		// if x = 0 we'll get the leftmost ray direction and if x = SCREEN_WIDTH we'll get the rightmost ray direction.
		data->ray_dir_x = data->dir_x + data->plane_x * data->camera_x;
		// the direction of the ray.
		data->ray_dir_y = data->dir_y + data->plane_y * data->camera_x;
		// the direction of the ray.
		// the player postions tell us which cell we are in and where in this cell exactly.
		data->map_x = (int)data->player_x;
		// the x player position in the map grid that tell us which grid cell we are in.
		data->map_y = (int)data->player_y;
		// the y player position in the map grid that tell us which grid cell we are in.
		data->delta_dist_x = fabs(1 / data->ray_dir_x);
		data->delta_dist_y = fabs(1 / data->ray_dir_y);
		hit = 0;
		if (data->ray_dir_x < 0)
		{
			data->step_x = -1;
			data->side_dist_x = (data->player_x - data->map_x)
				* data->delta_dist_x;
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
			data->side_dist_y = (data->player_y - data->map_y)
				* data->delta_dist_y;
		}
		else
		{
			data->step_y = 1;
			data->side_dist_y = (data->map_y + 1.0 - data->player_y)
				* data->delta_dist_y;
		}
		while (hit == 0)
		{
			if (data->side_dist_x < data->side_dist_y)
			{
				data->side_dist_x += data->delta_dist_x;
				data->map_x += data->step_x;
				side = 0;
			}
			else
			{
				data->side_dist_y += data->delta_dist_y;
				data->map_y += data->step_y;
				side = 1;
			}
			if (data->map_x < 0 || data->map_x >= MAP_WIDTH || data->map_y < 0
				|| data->map_y >= MAP_HEIGHT)
				break ; // we hit the border walls.
			if (data->map[data->map_y][data->map_x] == '1')
				hit = 1; // break ; we hit a wall;
		}
		if (side == 0)
			perp_wall_dist = data->side_dist_x - data->delta_dist_x;
		else
			perp_wall_dist = data->side_dist_y - data->delta_dist_y;
		color = 0xFFFFFF;
		if (side == 0)
		{
			color = CLR_EAW;
			// if (data->step_x > 0)
			// this is mean the player look to the right or the East
			//     color = 0xFF0000;   // red color
			// else
			// this is mean the player look to the left or the West
			//     color = 0x00FF00;   // green color
		}
		else
		{
			color = CLR_SAN;
			// if (data->step_y > 0)
			// this is mean the player look to the bottom or the South
			//     color = 0x0000FF;   // blue color
			// else
			// this is mean the player look to the top or the South
			//     color = 0xFFFF00;   // yellow color
		}
		line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
		draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_end >= SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;
		draw_vert_line(data->image, x, 0, draw_start, CLR_SKY);
		draw_vert_line(data->image, x, draw_start, draw_end, color);
		draw_vert_line(data->image, x, draw_end, SCREEN_HEIGHT, CLR_FLR);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image->img_ptr,
		0, 0);
	mlx_destroy_image(data->mlx_ptr, data->image->img_ptr);
	free(data->image);
}

// void update_player_positions(t_data *data, int keycode)
// {
//     int map_x;
//     int map_y;

//     if (keycode == U_KEY)
//     {
//         map_x = (int)(data->player_x + data->dir_x * MOVE_SPEED);
//         map_y = (int)(data->player_y + data->dir_y * MOVE_SPEED);

//         if (data->map[map_y][map_x] == '0' && map_x >= 0 && map_x < MAP_WIDTH
	&& map_y >= 0 && map_y < SCREEN_HEIGHT)
//         {
//             data->player_x += data->dir_x * MOVE_SPEED;
//             data->player_y += data->dir_y * MOVE_SPEED;
//         }
//     }

//     if (keycode == D_KEY)
//     {
//         map_x = (int)(data->player_x - data->dir_x * MOVE_SPEED);
//         map_y = (int)(data->player_y - data->dir_y * MOVE_SPEED);

//         if (data->map[map_y][map_x] == '0' && map_x >= 0 && map_x < MAP_WIDTH
	&& map_y >= 0 && map_y < SCREEN_HEIGHT)
//         {
//             data->player_x -= data->dir_x * MOVE_SPEED;
//             data->player_y -= data->dir_y * MOVE_SPEED;
//         }
//     }

//     if (keycode == L_KEY)
//     {
//         double old_dir_x = data->dir_x;
//         data->dir_x = data->dir_x * cos(-ROT_SPEED) - data->dir_y
	* sin(-ROT_SPEED);
	//         data->dir_y = old_dir_x * sin(-ROT_SPEED) + data->dir_y
	*cos(-ROT_SPEED);

	//         double old_plane_x = data->plane_x;
	//         data->plane_x = data->plane_x * cos(-ROT_SPEED) - data->plane_y
	*sin(-ROT_SPEED);
	//         data->plane_y = old_plane_x * sin(-ROT_SPEED) + data->plane_y
	*cos(-ROT_SPEED);
	//     }

	//     if (keycode == R_KEY)
	//     {
	//         double old_dir_x = data->dir_x;
	//         data->dir_x = data->dir_x * cos(ROT_SPEED) - data->dir_y
	*sin(ROT_SPEED);
	//         data->dir_y = old_dir_x * sin(ROT_SPEED) + data->dir_y
	*cos(ROT_SPEED);

	//         double old_plane_x = data->plane_x;
	//         data->plane_x = data->plane_x * cos(ROT_SPEED) - data->plane_y
	*sin(ROT_SPEED);
	//         data->plane_y = old_plane_x * sin(ROT_SPEED) + data->plane_y
	*cos(ROT_SPEED);
	//     }

	// }

	// int keyhook(int keycode, t_data *data)
	// {
	//     if (keycode == ESC_KEY)
	//     {
	//         mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	//         // mlx_destroy_image(data->mlx_ptr, data->image->img_ptr);
	//         // free_array(data->map);
	//         free(data->mlx_ptr);
	//         exit(0);
	//     }

	//     int map_x;
	//     int map_y;

	//     if (keycode == U_KEY)
	//     {
	//         map_x = (int)(data->player_x + data->dir_x * MOVE_SPEED);
	//         map_y = (int)(data->player_y + data->dir_y * MOVE_SPEED);

	//         if (data->map[map_y][map_x] == '0' && map_x >= 0
		&& map_x < MAP_WIDTH
	&& map_y >= 0 && map_y < SCREEN_HEIGHT)
//         {
//             data->player_x += data->dir_x * MOVE_SPEED;
//             data->player_y += data->dir_y * MOVE_SPEED;
//         }
//     }

//     if (keycode == D_KEY)
//     {
//         map_x = (int)(data->player_x - data->dir_x * MOVE_SPEED);
//         map_y = (int)(data->player_y - data->dir_y * MOVE_SPEED);

//         if (data->map[map_y][map_x] == '0' && map_x >= 0 && map_x < MAP_WIDTH
	&& map_y >= 0 && map_y < SCREEN_HEIGHT)
//         {
//             data->player_x -= data->dir_x * MOVE_SPEED;
//             data->player_y -= data->dir_y * MOVE_SPEED;
//         }
//     }

//     if (keycode == L_KEY)
//     {
//         double old_dir_x = data->dir_x;
//         data->dir_x = data->dir_x * cos(-ROT_SPEED) - data->dir_y
	* sin(-ROT_SPEED);
		//         data->dir_y = old_dir_x * sin(-ROT_SPEED) + data->dir_y
		*cos(-ROT_SPEED);

		//         double old_plane_x = data->plane_x;
		//         data->plane_x = data->plane_x * cos(-ROT_SPEED)
			- data->plane_y
		*sin(-ROT_SPEED);
		//         data->plane_y = old_plane_x * sin(-ROT_SPEED) + data->plane_y
		*cos(-ROT_SPEED);
		//     }

		//     if (keycode == R_KEY)
		//     {
		//         double old_dir_x = data->dir_x;
		//         data->dir_x = data->dir_x * cos(ROT_SPEED) - data->dir_y
		*sin(ROT_SPEED);
		//         data->dir_y = old_dir_x * sin(ROT_SPEED) + data->dir_y
		*cos(ROT_SPEED);

		//         double old_plane_x = data->plane_x;
		//         data->plane_x = data->plane_x * cos(ROT_SPEED)
			- data->plane_y
		*sin(ROT_SPEED);
		//         data->plane_y = old_plane_x * sin(ROT_SPEED) + data->plane_y
		*cos(ROT_SPEED);
		//     }

		//     // if (keycode == U_KEY)
		//     //     update_player_positions(data, keycode);
		//     // if (keycode == D_KEY)
		//     //     update_player_positions(data, keycode);

		//     //     // update_player_positions(data);
		//     // if (keycode == L_KEY)
		//     //     update_player_positions(data, keycode);

		//     //     // update_player_positions(data);
		//     // if (keycode == R_KEY)
		//     //     update_player_positions(data, keycode);

		//     //     // update_player_positions(data);

		//     // raycasting(data);
		//     return (0);
		// }