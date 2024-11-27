#include "../../include/cub3d.h"

void	ft_update_data(t_data *data)
{
	double	new_x;
	double	new_y;

	if (data->walk_direction != 0)
	{
		data->move_step = data->move_speed * data->walk_direction;
		ft_is_player_inside_wall(data);
	}
	if (data->strafe_direction != 0)
	{
		new_x = data->x_player + cos(data->player_angle + (PI / 2))
			* data->move_speed * data->strafe_direction;
		new_y = data->y_player + sin(data->player_angle + (PI / 2))
			* data->move_speed * data->strafe_direction;
		if (data->map.map[(int)(new_y / CUBE_TILE)][(int)(new_x
				/ CUBE_TILE)] == '0')
		{
			data->x_player = new_x;
			data->y_player = new_y;
		}
		else if (data->map.map[(int)(new_y / CUBE_TILE)][(int)(new_x
				/ CUBE_TILE)] == 'D')
		{
			data->door_index = ft_get_door_index(data, new_x / CUBE_TILE, new_y
					/ CUBE_TILE);
			if (data->door_index == -1)
				ft_free_all("Door_index Fail \n", data, 1);
			if (!data->door[data->door_index].is_open)
				return ;
			else
			{
				data->x_player = new_x;
				data->y_player = new_y;
			}
		}
	}
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