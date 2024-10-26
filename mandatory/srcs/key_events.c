/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:17:16 by aelkheta          #+#    #+#             */
/*   Updated: 2024/10/26 15:56:42 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void clean_up(t_data *data)
{
	if (data->no_texture_path)
		free(data->no_texture_path);
	if (data->so_texture_path)
		free(data->so_texture_path);
	if (data->we_texture_path)
		free(data->we_texture_path);
	if (data->ea_texture_path)
		free(data->ea_texture_path);
	
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);
	if (data->image)
		mlx_destroy_image(data->mlx_ptr, data->image);
	if (data->map)
		free_array(data->map);
	if (data->mlx_ptr)
		free(data->mlx_ptr);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
	{
		clean_up(data);
		exit(0);
	}
	else if (keycode == 'w' || keycode == U_KEY)
		data->move_forward = 1;
	else if (keycode == 's' || keycode == D_KEY)
		data->move_backward = 1;
	else if (keycode == 'a' || keycode == L_KEY)
		data->rotate_left = 1;
	else if (keycode == 'd' || keycode == R_KEY)
		data->rotate_right = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == 'w' || keycode == U_KEY)
		data->move_forward = 0;
	else if (keycode == 's' || keycode == D_KEY)
		data->move_backward = 0;
	else if (keycode == 'a' || keycode == L_KEY)
		data->rotate_left = 0;
	else if (keycode == 'd' || keycode == R_KEY)
		data->rotate_right = 0;
	return (0);
}

int	game_loop(t_data *data)
{
	update_player(data);
	start_game(data);
	return (0);
}

int destroy_notify(t_data *data)
{
	clean_up(data);
	return (exit (0), 0);
}
