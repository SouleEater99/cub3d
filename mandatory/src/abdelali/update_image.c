/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:30:22 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/29 10:02:20 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
	ft_cast_all_rays(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->projection_img.img_ptr, 0, 0);
	mlx_destroy_image(data->mlx_ptr, data->projection_img.img_ptr);
}
