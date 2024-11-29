/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:30:22 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/29 09:43:17 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/// @brief player sliding on door.
/// @param data
/// @param new_x
/// @param new_y
void	enter_open_door(t_data *data, double new_x, double new_y)
{
	data->door_index = ft_get_door_index(data, data->x_player / CUBE_TILE, new_y
			/ CUBE_TILE);
	if (data->door_index == -1)
		ft_free_all("Door_index Fail \n", data, 1);
	if (!data->door[data->door_index].is_open)
		return ;
	else
		data->y_player = new_y;
	data->door_index = ft_get_door_index(data, new_x / CUBE_TILE, new_y
			/ CUBE_TILE);
	if (data->door_index == -1)
		ft_free_all("Door_index Fail \n", data, 1);
	if (!data->door[data->door_index].is_open)
		return ;
	else
		data->x_player = new_x;
}

void	go_left_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->x_player + cos(data->player_angle + (PI / 2))
		* data->move_speed * data->strafe_direction;
	new_y = data->y_player + sin(data->player_angle + (PI / 2))
		* data->move_speed * data->strafe_direction;
	if (data->map.map[(int)(data->y_player / CUBE_TILE)][(int)(new_x
			/ CUBE_TILE)] == '0')
		data->x_player = new_x;
	if (data->map.map[(int)(new_y / CUBE_TILE)][(int)(data->x_player
			/ CUBE_TILE)] == '0')
		data->y_player = new_y;
	else if (data->map.map[(int)(new_y / CUBE_TILE)][(int)(new_x
			/ CUBE_TILE)] == 'D')
		enter_open_door(data, new_x, new_y);
}

void	ft_update_data(t_data *data)
{
	if (data->walk_direction != 0)
	{
		data->move_step = data->move_speed * data->walk_direction;
		ft_is_player_inside_wall(data);
	}
	if (data->strafe_direction != 0)
		go_left_right(data);
	if (data->turn_direction != 0)
	{
		data->player_angle += data->turn_direction * data->turn_speed;
		data->player_angle = ft_normalize_angle(data->player_angle);
	}
}

void	ft_update_image(t_data *data)
{
	ft_create_pojection_img(data);
	if (!(data->clicks % 2))
		ft_cast_all_rays(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->projection_img.img_ptr, 0, 0);
	mlx_destroy_image(data->mlx_ptr, data->projection_img.img_ptr);
}
