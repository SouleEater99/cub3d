/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heisenberg <heisenberg@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:30:15 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/28 22:01:28 by heisenberg       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_get_virt_hit(t_data *data, double angle, double *x, double *y)
{
	double	ystep;
	double	xstep;
	int		x_pos;
	int		y_pos;

	if (data->is_face_right)
		*x = (long)(data->x_player / CUBE_TILE) * CUBE_TILE + CUBE_TILE;
	else
		*x = (long)(data->x_player / CUBE_TILE) * CUBE_TILE;
	*y = ((*x - data->x_player) * tan(angle)) + data->y_player;
	xstep = CUBE_TILE;
	if (!data->is_face_right)
		xstep *= -1;
	ystep = xstep * tan(angle);
	if (!data->is_face_down && ystep > 0)
		ystep *= -1;
	if (!data->is_face_right)
		*x -= 1;
	x_pos = (int)(*x / CUBE_TILE);
	y_pos = (int)(*y / CUBE_TILE);
	while (y_pos > 0 && y_pos < data->map.map_height && x_pos > 0
		&& x_pos < data->map.map_line_len[y_pos])
	{
		if (ft_is_a_wall(data, x_pos, y_pos))
			break ;
		*y += ystep;
		*x += xstep;
		x_pos = (int)(*x / CUBE_TILE);
		y_pos = (int)(*y / CUBE_TILE);
	}
}

void	ft_get_horz_hit(t_data *data, double angle, double *x, double *y)
{
	double	ystep;
	double	xstep;
	int		x_pos;
	int		y_pos;

	if (data->is_face_down)
		*y = (long)(data->y_player / CUBE_TILE) * CUBE_TILE + CUBE_TILE;
	else
		*y = (long)(data->y_player / CUBE_TILE) * CUBE_TILE;
	*x = ((*y - data->y_player) / tan(angle)) + data->x_player;
	ystep = CUBE_TILE;
	if (!data->is_face_down)
		ystep *= -1;
	xstep = ystep / tan(angle);
	if (!data->is_face_right && xstep > 0)
		xstep *= -1;
	if (!data->is_face_down)
		*y -= 1;
	x_pos = (int)(*x / CUBE_TILE);
	y_pos = (int)(*y / CUBE_TILE);
	while (y_pos > 0 && y_pos < data->map.map_height && x_pos > 0
		&& x_pos < data->map.map_line_len[y_pos])
	{
		if (ft_is_a_wall(data, x_pos, y_pos))
			break ;
		*y += ystep;
		*x += xstep;
		x_pos = (int)(*x / CUBE_TILE);
		y_pos = (int)(*y / CUBE_TILE);
	}
}

void	ft_get_wall_hit(t_data *data, double angle)
{
	double	VirtHitX;
	double	VirtHitY;
	double	HorzHitX;
	double	HorzHitY;

	HorzHitX = 0;
	HorzHitY = 0;
	VirtHitX = 0;
	VirtHitY = 0;
	ft_get_virt_hit(data, angle, &VirtHitX, &VirtHitY);
	ft_get_horz_hit(data, angle, &HorzHitX, &HorzHitY);
	if (ft_calc_distance(data, HorzHitX, HorzHitY) < ft_calc_distance(data,
			VirtHitX, VirtHitY))
	{
		data->distance = ft_calc_distance(data, HorzHitX, HorzHitY);
		data->correct_distance = data->distance * cos(angle
				- data->player_angle);
		data->wall_slice_high = ((double)CUBE_TILE / data->correct_distance)
			* (double)data->plan_distanced;
		data->wall_hit_x = HorzHitX;
		data->wall_hit_y = HorzHitY;
		data->is_hit_virt = 0;
	}
	else
	{
		data->distance = ft_calc_distance(data, VirtHitX, VirtHitY);
		data->correct_distance = data->distance * cos(angle
				- data->player_angle);
		data->wall_slice_high = ((double)CUBE_TILE / data->correct_distance)
			* (double)data->plan_distanced;
		data->wall_hit_x = VirtHitX;
		data->wall_hit_y = VirtHitY;
		data->is_hit_virt = 1;
	}
}
