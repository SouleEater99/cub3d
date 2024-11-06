/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziz <aziz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 09:05:54 by aelkheta          #+#    #+#             */
/*   Updated: 2024/10/30 14:04:00 by aziz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	init_map(t_data *data)
{
	data->map = (char **)malloc(sizeof(char *) * (data->map_height + 1));
	data->map[0] = strdup("11111111111111111111111111111");
	data->map[1] = strdup("10000000000000000000000000001");
	data->map[2] = strdup("10001111111111000000000000001");
	data->map[3] = strdup("10000000000000001111111111101");
	data->map[4] = strdup("11000000000000000000000000001");
	data->map[5] = strdup("10000111111011111100000000001");
	data->map[6] = strdup("10000000000000000001111111101");
	data->map[7] = strdup("10000000000000000001111111101");
	data->map[8] = strdup("10000000000000000001111111101");
	data->map[9] = strdup("10000000000000000001111111101");
	data->map[10] = strdup("10000000000000000001111111101");
	data->map[11] = strdup("10000000000000000001111111101");
	data->map[12] = strdup("10000000000000000001111111101");
	data->map[13] = strdup("10000000000000000001111111101");
	data->map[14] = strdup("10000000000000000001111111101");
	data->map[15] = strdup("10000000000000000001111111101");
	data->map[16] = strdup("10000000000000000000000000001");
	data->map[17] = strdup("10000000000000000000000000001");
	data->map[18] = strdup("10000000000000000000000000001");
	data->map[19] = strdup("10000000000000000000000000001");
	data->map[20] = strdup("10000000000000000000000000001");
	data->map[21] = strdup("10000000000000000000000000001");
	data->map[22] = strdup("10000000000000000000000000001");
	data->map[23] = strdup("10000000000000000000000000001");
	data->map[24] = strdup("10000000000000000000000000001");
	data->map[25] = strdup("10000000000000000000000000001");
	data->map[26] = strdup("10000000000000000000000000001");
	data->map[27] = strdup("10000000000000000000000000001");
	data->map[28] = strdup("10000000000000000000000000001");
	data->map[29] = strdup("11111111111111111111111111111");
	data->map[30] = NULL;
	return (0);
}

double rad_to_deg(double radians)
{
	double degrees;
	
	degrees = radians *  180 / PI;
	return degrees;
}

double deg_to_rad(double degrees)
{
	double radians;
	
	radians = degrees * PI / 180;
	return radians;
}

# define FOV 66

// # define FOV (66 * 180 / PI)

void	init_game(t_data *data)
{
	double fov_width = tan(deg_to_rad(FOV) / 2);

	// data->plane_x = -data->dir_y * fov_width;
	// data->plane_y = data->dir_x * fov_width;
	
	data->player_dir = 'E';

	if (data->player_dir == 'N')		// North
	{
		data->dir_x = 0;
		data->dir_y = -1;
		// data->plane_x = 0.66;
		// data->plane_y = 0;
	}
	else if (data->player_dir == 'S')	// South
	{
		data->dir_x = 0;
		data->dir_y = 1;
		// data->plane_x = -0.66;
		// data->plane_y = 0;
	}
	else if (data->player_dir == 'W')	// West
	{
		data->dir_x = -1;
		data->dir_y = 0;
		// data->plane_x = 0;
		// data->plane_y = 0.66;
	}
	else if (data->player_dir == 'E')	// East
	{
		data->dir_x = 1;
		data->dir_y = 0;
		// data->plane_x = 0;
		// data->plane_y = -0.66;
	}

	data->plane_x = -data->dir_y * fov_width;
	data->plane_y = data->dir_x * fov_width;

	data->scale = SCALE;
	data->rot_speed = ROT_SPEED;
	data->move_speed = MOVE_SPEED;
	data->player_radius = PLAYER_RADIUS;
	data->minimap_radius = MINIMAP_RADIUS;
	data->minimap_x_center = MINIMAP_MID_X;
	data->minimap_y_center = MINIMAP_MID_Y;

	data->map_width = MAP_WIDTH;
	data->map_height = MAP_HEIGHT;

	data->player_x = 2.0;   // player positions
	data->player_y = 2.0;   // player positions

	init_map(data);
}
