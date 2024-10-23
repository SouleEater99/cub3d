/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 09:05:54 by aelkheta          #+#    #+#             */
/*   Updated: 2024/10/23 18:54:49 by aelkheta         ###   ########.fr       */
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
	data->dir_x = 1;      // the player look to the East or the Right
	data->dir_y = 0;      // the player look to the East or the Right
	data->plane_x = 0;    // for the field of view
	data->plane_y = 0.66; // for the field of view
	// data->player_x = 2;   // player positions
	// data->player_y = 2;   // player positions
	// init_map(data);
}
