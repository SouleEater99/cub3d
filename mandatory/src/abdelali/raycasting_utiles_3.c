/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utiles_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 22:00:27 by heisenberg        #+#    #+#             */
/*   Updated: 2024/11/29 10:03:04 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_write_wall(t_data *data, int i)
{
	int	j;

	j = data->start;
	while (j < data->end)
	{
		ft_get_texture_color(data, j);
		// data->color = shade_walls(data->color, (data->distance / CUBE_TILE));
		my_mlx_pixel_put(&data->projection_img, i * WALL_STRIP, j++,
			data->color);
	}
}

void	get_the_right_color(t_data *data, int texture_offset_x,
		int texture_offset_y)
{
	if (data->map.map[(int)data->wall_hit_y / CUBE_TILE][(int)data->wall_hit_x
		/ CUBE_TILE] == 'D')
		data->color = ft_get_color(data->textures[4], texture_offset_x,
				texture_offset_y);
	else if (data->is_hit_virt && data->is_face_right)
		data->color = ft_get_color(data->textures[0], texture_offset_x,
				texture_offset_y);
	else if (data->is_hit_virt && !data->is_face_right)
		data->color = ft_get_color(data->textures[1], texture_offset_x,
				texture_offset_y);
	else if (!data->is_hit_virt && data->is_face_down)
		data->color = ft_get_color(data->textures[2], texture_offset_x,
				texture_offset_y);
	else if (!data->is_hit_virt && !data->is_face_down)
		data->color = ft_get_color(data->textures[3], texture_offset_x,
				texture_offset_y);
}

void	ft_get_texture_color(t_data *data, int j)
{
	int	texture_offset_x;
	int	texture_offset_y;
	int	distance_from_top;

	if (data->is_hit_virt)
		texture_offset_x = (int)data->wall_hit_y % TEXTURE_TILE;
	else
		texture_offset_x = (int)data->wall_hit_x % TEXTURE_TILE;
	distance_from_top = j + (data->wall_slice_high / 2) - (HIGH / 2);
	texture_offset_y = distance_from_top * ((double)TEXTURE_TILE
			/ data->wall_slice_high);
	if ((texture_offset_x >= 0 && texture_offset_x < TEXTURE_TILE - 1)
		&& (texture_offset_y >= 0 && texture_offset_y < TEXTURE_TILE - 1))
		get_the_right_color(data, texture_offset_x, texture_offset_y);
}

void	ft_write_projection(t_data *data, int i)
{
	data->start = (HIGH / 2) - (data->wall_slice_high / 2);
	if (data->start < 0)
		data->start = 0;
	data->end = (HIGH / 2) + (data->wall_slice_high / 2);
	if (data->end > HIGH)
		data->end = HIGH;
	ft_write_ceiling(data, i, data->map.ceiling_color);
	ft_write_wall(data, i);
	ft_write_floor(data, i, data->map.floor_color);
}

void	ft_cast_all_rays(t_data *data)
{
	int		i;
	double	angle;

	i = 0;
	angle = data->player_angle - (FOV / 2);
	while (i < data->num_rays)
	{
		if (angle > 2 * PI)
			angle -= 2 * PI;
		else if (angle < 0)
			angle += 2 * PI;
		data->is_face_down = ft_is_angle_facing_down(angle);
		data->is_face_right = ft_is_angle_facing_right(angle);
		data->flag = 0;
		ft_get_wall_hit(data, angle);
		ft_write_projection(data, i);
		angle = angle + ((double)FOV / (double)data->num_rays);
		i++;
	}
}
