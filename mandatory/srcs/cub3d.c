/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:07:23 by aelkheta          #+#    #+#             */
/*   Updated: 2024/10/16 15:27:52 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	go_left_right(t_data *data, short rot_dir)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(ROT_SPEED * rot_dir) - data->dir_y
		* sin(ROT_SPEED * rot_dir);
	data->dir_y = old_dir_x * sin(ROT_SPEED * rot_dir) + data->dir_y
		* cos(ROT_SPEED * rot_dir);
	old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(ROT_SPEED * rot_dir) - data->plane_y
		* sin(ROT_SPEED * rot_dir);
	data->plane_y = old_plane_x * sin(ROT_SPEED * rot_dir) + data->plane_y
		* cos(ROT_SPEED * rot_dir);
}

void	go_up_down(t_data *data, short mov_dir)
{
	double	new_x;
	double	new_y;

	new_x = data->player_x + data->dir_x * MOVE_SPEED * mov_dir;
	new_y = data->player_y + data->dir_y * MOVE_SPEED * mov_dir;
	if (data->map[(int)new_y][(int)new_x] == '0')
	{
		data->player_x = new_x;
		data->player_y = new_y;
	}
}

void	update_player(t_data *data)
{
	if (data->move_forward)
		go_up_down(data, 1);
	if (data->move_backward)
		go_up_down(data, -1);
	if (data->rotate_right)
		go_left_right(data, 1);
	if (data->rotate_left)
		go_left_right(data, -1);
}

int	game_loop(t_data *data)
{
	update_player(data);
	raycasting(data);
	return (0);
}

int	main(void)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT,
			"cub3D");
	init_game(&data);
	mlx_hook(data.win_ptr, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win_ptr, 3, 1L << 1, key_release, &data);
	mlx_loop_hook(data.mlx_ptr, game_loop, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
