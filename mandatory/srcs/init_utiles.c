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

#include <cub3d.h>

int	init_map(t_data *data)
{
	data->map = (char **)malloc(sizeof(char *) * (data->map_height + 1));
	data->map[0] = strdup("11111111111111111111111111111");
	data->map[1] = strdup("10000000000000000000000000001");
	data->map[2] = strdup("10001111111111000000000000001");
	data->map[3] = strdup("10000000000000001111111111101");
	data->map[4] = strdup("11000000000000000000000000001");
	data->map[5] = strdup("10000111111011111100000000001");
	data->map[6] = strdup("10101000000000000001111111101");
	data->map[7] = strdup("10000010000000000000000000001");
	data->map[8] = strdup("11111111111111111111111111111");
	data->map[9] = NULL;
	return (0);
}

void	init_game(t_data *data)
{
	if (data->player_dir == 'N')		// North
	{
		data->dir_x = 0;
		data->dir_y = -1;
		data->plane_x = 0.66;
		data->plane_y = 0;
	}
	else if (data->player_dir == 'S')	// South
	{
		data->dir_x = 0;
		data->dir_y = 1;
		data->plane_x = -0.66;
		data->plane_y = 0;
	}
	else if (data->player_dir == 'W')	// West
	{
		data->dir_x = -1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = 0.66;
	}
	else if (data->player_dir == 'E')	// East
	{
		data->dir_x = 1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = -0.66;
	}

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
