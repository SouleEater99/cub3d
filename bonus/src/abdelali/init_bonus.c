/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:29:58 by aelkheta          #+#    #+#             */
/*   Updated: 2024/12/03 16:32:20 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

double	get_player_dir(int16_t player_dir)
{
	if (player_dir == 'N')
		return (-PI / 2);
	else if (player_dir == 'S')
		return (PI / 2);
	else if (player_dir == 'W')
		return (PI);
	else if (player_dir == 'E')
		return (0);
	return (-1);
}

void	init_minimap(t_data *data)
{
	data->fov = 66 * (PI / 180);
	data->plan_distanced = (WIDTH / 2) / tan(data->fov / 2);
	data->player_x = data->x_player / (CUBE_TILE + (CUBE_TILE / 2));
	data->player_y = data->y_player / (CUBE_TILE + (CUBE_TILE / 2));
	data->scale = SCALE;
	data->player_radius = PLAYER_RADIUS;
	data->minimap_radius = MINIMAP_RADIUS;
	data->minimap_x_center = SCREEN_WIDTH - MINIMAP_RADIUS - 20;
	data->minimap_y_center = MINIMAP_RADIUS + 20;
	data->player.frames_num = 22;
	data->player.frames_path = "./textures/sprites/gun_sprite_0/";
	init_player_sprites(data, data->player.frames_path,
		data->player.frames_num);
}

int	init_data(t_data *data, int ac, char **av)
{
	int	i;

	if (!parse_map(data, ac, av))
		ft_free_all(NULL, data, 1);
	init_mlx(data);
	i = -1;
	while (++i < data->textures_found)
	{
		data->textures[i] = load_texture(data->mlx_ptr, data->textures_path[i]);
		if (!data->textures[i])
			ft_free_all(NULL, data, 1);
	}
	data->row = data->map.map_width;
	data->col = data->map.map_height;
	data->img_width = SCREEN_WIDTH;
	data->img_height = SCREEN_HEIGHT;
	data->x_player = data->player_x * CUBE_TILE;
	data->y_player = data->player_y * CUBE_TILE;
	data->player_angle = (double)get_player_dir(data->player_dir);
	data->turn_speed = ROT_SPEED;
	data->move_speed = MOVE_SPEED;
	data->num_rays = WIDTH / WALL_STRIP;
	init_minimap(data);
	return (0);
}

void	init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		ft_free_all("mlx Fail\n", data, 1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HIGH, "First Game 3D");
	if (!data->win_ptr)
		ft_free_all("win_ptr Fail\n", data, 1);
}
