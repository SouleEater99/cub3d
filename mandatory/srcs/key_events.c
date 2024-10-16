/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:17:16 by aelkheta          #+#    #+#             */
/*   Updated: 2024/10/16 15:17:28 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	key_press(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(0);
	}
	else if (keycode == U_KEY)
		data->move_forward = 1;
	else if (keycode == D_KEY)
		data->move_backward = 1;
	else if (keycode == L_KEY)
		data->rotate_left = 1;
	else if (keycode == R_KEY)
		data->rotate_right = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == U_KEY)
		data->move_forward = 0;
	else if (keycode == D_KEY)
		data->move_backward = 0;
	else if (keycode == L_KEY)
		data->rotate_left = 0;
	else if (keycode == R_KEY)
		data->rotate_right = 0;
	return (0);
}
