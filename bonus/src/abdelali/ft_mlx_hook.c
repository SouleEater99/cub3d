/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heisenberg <heisenberg@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:29:50 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/28 20:34:14 by heisenberg       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_key_press(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == XK_Up || key == XK_w)
		data->walk_direction = 1;
	else if (key == XK_Down || key == XK_s)
		data->walk_direction = -1;
	else if (key == XK_Right)
		data->turn_direction = 1;
	else if (key == XK_Left)
		data->turn_direction = -1;
	else if (key == XK_d)
		data->strafe_direction = 1;
	else if (key == XK_a)
		data->strafe_direction = -1;
	else if (key == XK_space)
	{
		data->flag = 1;
		ft_write_player_wall_hit(data);
	}
	else if (key == XK_Escape)
		ft_free_all(NULL, data, 0);
	else if (key == CTRL_KEY)
		data->shoot = 1;
	return (0);
}

int	ft_key_release(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == XK_Up || key == XK_w)
		data->walk_direction = 0;
	else if (key == XK_Down || key == XK_s)
		data->walk_direction = 0;
	else if (key == XK_Right)
		data->turn_direction = 0;
	else if (key == XK_Left)
		data->turn_direction = 0;
	else if (key == XK_a)
		data->strafe_direction = 0;
	else if (key == XK_d)
		data->strafe_direction = 0;
	return (0);
}

int	ft_key_destroy(void *param)
{
	ft_free_all(NULL, (t_data *)param, 0);
	return (0);
}

int	ft_loop_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	ft_update_data(data);
	ft_update_image(data);
	mouse_hooks(data);
	return (0);
}
