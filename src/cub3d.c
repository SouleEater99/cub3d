/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maim <ael-maim@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 04:00:00 by ael-maim          #+#    #+#             */
/*   Updated: 2024/10/09 04:00:17 by ael-maim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_update_img(t_data *data)
{
	// ft_write_map_img(data);
	ft_write_player_to_img(data);
	t_ray *ray = data->ray;
	int j = 0;
	int i = 0;

	mlx_clear_window(data->mlx, data->mlx_win);
	while (i < NUM_RAYS / 4)
	{
		j = 0;
		while (j < (ray + i)->WallSliceHigh)
		{
			// if (ft_board_protect(data, i, j))
				my_mlx_pixel_put(data->img, i, j, WHITE);
			j++;

		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
}

int	ft_is_player_inside_wall(t_data *data)
{
	double	x;
	double	y;

	x = data->x_player + cos(data->rotation_angle) * data->move_step;
	y = data->y_player + sin(data->rotation_angle) * data->move_step;
	if (data->map[(int)y / CUB_SIZE][(int) x / CUB_SIZE] == '1')
		return (0);
	data->x_player = x;
	data->y_player = y;
	return (1);
}

int	ft_normalize_angle(int angle)
{
	angle = angle % 360;
	if (angle < 0)
		angle += 360;
	return (angle);
}

int	ft_key_hook(int keycode, t_data *data)
{
	if (keycode == XK_Up)
	{
		data->walk_direction = 1;
		data->move_step =	data->walk_direction * data->move_speed; 
		if (ft_is_player_inside_wall(data)) 
			ft_update_img(data);
	}
	if (keycode == XK_Down)
	{
		data->walk_direction = -1;
		data->move_step =	data->walk_direction * data->move_speed;
		if (ft_is_player_inside_wall(data)) 
			ft_update_img(data);
	}
	if (keycode == XK_Left)
	{
		data->turn_direction = -1;
		data->rotation_angle += (data->turn_direction * data->rotation_speed);
		data->rotation_angle = ft_normalize_angle(data->rotation_angle * (180 / PI)) * (PI / 180);
		if (ft_is_angle_facing_down(data->rotation_angle) == 1)
			printf("facing down \n");
		else
			printf("facing up \n");
		if (ft_is_angle_facing_right(data->rotation_angle) == 1)
			printf("facing right \n");
		else
			printf("facing left \n");
		ft_update_img(data);

	}
	if (keycode == XK_Right)
	{
		data->turn_direction = 1;
		data->rotation_angle += (data->turn_direction * data->rotation_speed);
		data->rotation_angle = ft_normalize_angle(data->rotation_angle * (180 / PI)) * (PI / 180);
		ft_update_img(data);
		if (ft_is_angle_facing_down(data->rotation_angle) == 1)
			printf("facing down \n");
		else
			printf("facing up \n");
		if (ft_is_angle_facing_right(data->rotation_angle) == 1)
			printf("facing right \n");
		else
			printf("facing left \n");
		ft_update_img(data);
		
	}
	if (keycode == XK_Escape)
	{
		ft_free_all(data, "destroy display\n", 1);
	}
	return (1);

}



int	main(void)
{
	t_data *data;

	char	*map[] = {	
						"111111111111111111111111",
						"100000000000010000000001",
						"111110000000000000000001",
						"100011111111110000000001",
						"100000000000010000000001",
						"100000000000010000000001",
						"100000000000011111000001",
						"100011111111111100000001",
						"100000000000010000000001",
						"100100000000010000000001",
						"100000000000000000000001",
						"111111111111111111111111",
						NULL};
	data = ft_init_data();
	data->map = map;

	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HIGH, "Hello world!");
	data->img->img = mlx_new_image(data->mlx, WIDTH, HIGH);
	data->img->addr = mlx_get_data_addr(data->img->img, &data->img->bits_per_pixel, &data->img->line_length,
		&data->img->endian);
	ft_update_img(data);
	mlx_hook(data->mlx_win, 2, 1L << 0, ft_key_hook, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, ft_key_hook, data);
	mlx_loop(data->mlx);
	ft_free_all(data, "destroy display\n", 0);
}

