/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziz <aziz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:07:23 by aelkheta          #+#    #+#             */
/*   Updated: 2024/10/30 13:17:18 by aziz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	go_left_right(t_data *data, short rot_dir)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(data->rot_speed * rot_dir) - data->dir_y
		* sin(data->rot_speed * rot_dir);
	data->dir_y = old_dir_x * sin(data->rot_speed * rot_dir) + data->dir_y
		* cos(data->rot_speed * rot_dir);
	old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(data->rot_speed * rot_dir) - data->plane_y
		* sin(data->rot_speed * rot_dir);
	data->plane_y = old_plane_x * sin(data->rot_speed * rot_dir) + data->plane_y
		* cos(data->rot_speed * rot_dir);
}

void	go_up_down(t_data *data, short mov_dir)
{
	double	new_x;
	double	new_y;

	new_x = data->player_x + data->dir_x * data->move_speed * mov_dir;
	new_y = data->player_y + data->dir_y * data->move_speed * mov_dir;

	// check each one separately for sliding/gliding effect.
	printf("player at: [%lf][%lf] = [%c]\n", data->player_y, data->player_x, data->map[(int)data->player_y][(int)data->player_x]);
    
    if (data->map[(int)data->player_y][(int)new_x] == '0')
        data->player_x = new_x;
		
    if (data->map[(int)new_y][(int)data->player_x] == '0')
		data->player_y = new_y;
	
	printf("player will be at: [%lf][%lf] = [%c]\n", new_y, new_x, data->map[(int)new_y][(int)new_x]);
	
	// if (data->map[(int)new_y][(int)new_x] == '0')
	// {
	// 	data->player_x = new_x;
	// 	data->player_y = new_y;
	// }
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
	
// int mouse_events(int button, int x, int y, t_data *data)
// {
// 	(void)data;
// 	printf("Button %d pressed at (%d, %d)\n", button, y, x);
// 	if (button == 1)
// 		printf("Left click!\n");
// 	else if (button == 2)
// 		printf("Middle click!\n");
// 	else if (button == 3)
// 		printf("Right click!\n");
// 	else if (button == 4)
// 		printf("Scroll up!\n");
// 	else if (button == 5)
// 		printf("Scroll down!\n");
// 	return 0;
// }

int main(int ac, char **av)
{
    t_data data;

    memset(&data, 0, sizeof(t_data));
    if (parse_map(&data, ac, av))
        return (1);

    data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
    data.win_ptr = mlx_new_window(data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (!data.win_ptr)
		return (1);
		
    init_game(&data);
	
    mlx_hook(data.win_ptr, 2, 1L << 0, key_press, &data);
    mlx_hook(data.win_ptr, 3, 1L << 1, key_release, &data);
    mlx_hook(data.win_ptr, 17, 1L << 0, destroy_notify, &data);
	mlx_mouse_hook(data.win_ptr, mouse_events, &data);

    mlx_loop_hook(data.mlx_ptr, game_loop, &data);
    mlx_loop(data.mlx_ptr);
    return (0);
}
