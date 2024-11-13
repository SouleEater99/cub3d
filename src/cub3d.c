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

void	ft_render_projection(t_data *data, t_ray *ray)
{
	int j = 0;
	int i = 0;
	int	start;
	int end;
	u_int32_t color;
	unsigned int		texture_offset_x;
	unsigned int		texture_offset_y;


	while (i < data->num_rays)
	{
		start = (data->high / 2) - (ray->WallSliceHigh / 2);
		end = (data->high / 2) + (ray->WallSliceHigh / 2);
		if (ray->IsHitVirt)
			texture_offset_x = (int)ray->WallHitY % TEXTURE_SIZE;
		else
			texture_offset_x = (int)ray->WallHitX % TEXTURE_SIZE;
		j = 0;
		while (j < start)
			my_mlx_pixel_put(data, i * WALL_STRIP, j++, 0x0000FFFF);
		j = 0;
		while (j < (ray->WallSliceHigh))
		{
			texture_offset_y = (j * TEXTURE_SIZE) / ray->WallSliceHigh;
			if (texture_offset_x < TEXTURE_SIZE && texture_offset_y < TEXTURE_SIZE)
				color = data->texture[(texture_offset_y * TEXTURE_SIZE) + texture_offset_x];
			// color = 0xFFFFFFFF;
			my_mlx_pixel_put(data,i * WALL_STRIP, start + j++,color);
		}
		j = end;
		while (j < data->high)
			my_mlx_pixel_put(data, i * WALL_STRIP, j++, 0xFF0F0F00);
		i++;
		ray++;
	}
}

void	ft_update_img(t_data *data)
{
	data->img->img = mlx_new_image(data->mlx, data->width, data->high);
	data->img->addr = mlx_get_data_addr(data->img->img, &data->img->bits_per_pixel, &data->img->line_length,
		&data->img->endian);
	ft_cast_all_rays(data);
	ft_render_projection(data, data->ray);
	ft_write_map_img(data);
	ft_write_player_to_img(data, data->ray);
	ft_write_line(data, cos(data->rotation_angle) * 60, sin(data->rotation_angle) * 60, BLUE);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
	mlx_destroy_image(data->mlx, data->img->img);
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

double	ft_normalize_angle(double angle)
{
	if (angle > 2 * PI)
 	   angle -= 2 * PI;
	else if (angle < 0)
 	   angle += 2 * PI;
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
		data->rotation_angle = ft_normalize_angle(data->rotation_angle);
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
		data->rotation_angle = ft_normalize_angle(data->rotation_angle);
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
	if (keycode == XK_m)
	{
		if (data->minimap_scale_factor == 0.2)
			data->minimap_scale_factor = 1;
		else
			data->minimap_scale_factor = 0.2;
		ft_update_img(data);
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

	data->mlx_win = mlx_new_window(data->mlx, data->width, data->high, "Hello world!");
	ft_update_img(data);
	mlx_hook(data->mlx_win, 2, 1L << 0, ft_key_hook, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, ft_key_hook, data);
	mlx_loop(data->mlx);
	ft_free_all(data, "destroy display\n", 0);
}

