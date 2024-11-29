/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utiles_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:30:45 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/29 09:30:59 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	get_x_pos(t_data *data, double angle, double *x)
{
	data->xstep = CUBE_TILE;
	if (!data->is_face_right)
		data->xstep *= -1;
	data->ystep = data->xstep * tan(angle);
	if (!data->is_face_down && data->ystep > 0)
		data->ystep *= -1;
	if (!data->is_face_right)
		*x -= 1;
	return ((int)(*x / CUBE_TILE));
}

void	ft_get_virt_hit(t_data *data, double angle, double *x, double *y)
{
	int	x_pos;
	int	y_pos;

	if (data->is_face_right)
		*x = (long)(data->x_player / CUBE_TILE) * CUBE_TILE + CUBE_TILE;
	else
		*x = (long)(data->x_player / CUBE_TILE) * CUBE_TILE;
	*y = ((*x - data->x_player) * tan(angle)) + data->y_player;
	x_pos = get_x_pos(data, angle, x);
	y_pos = (int)(*y / CUBE_TILE);
	while (y_pos > 0 && y_pos < data->map.map_height && x_pos > 0
		&& x_pos < data->map.map_line_len[y_pos])
	{
		if (ft_is_a_wall(data, x_pos, y_pos))
			break ;
		*y += data->ystep;
		*x += data->xstep;
		x_pos = (int)(*x / CUBE_TILE);
		y_pos = (int)(*y / CUBE_TILE);
	}
}

int	get_y_pos(t_data *data, double angle, double *y)
{
	data->ystep = CUBE_TILE;
	if (!data->is_face_down)
		data->ystep *= -1;
	data->xstep = data->ystep / tan(angle);
	if (!data->is_face_right && data->xstep > 0)
		data->xstep *= -1;
	if (!data->is_face_down)
		*y -= 1;
	return ((int)(*y / CUBE_TILE));
}

void	ft_get_horz_hit(t_data *data, double angle, double *x, double *y)
{
	int	x_pos;
	int	y_pos;

	if (data->is_face_down)
		*y = (long)(data->y_player / CUBE_TILE) * CUBE_TILE + CUBE_TILE;
	else
		*y = (long)(data->y_player / CUBE_TILE) * CUBE_TILE;
	*x = ((*y - data->y_player) / tan(angle)) + data->x_player;
	y_pos = get_y_pos(data, angle, y);
	x_pos = (int)(*x / CUBE_TILE);
	while (y_pos > 0 && y_pos < data->map.map_height && x_pos > 0
		&& x_pos < data->map.map_line_len[y_pos])
	{
		if (ft_is_a_wall(data, x_pos, y_pos))
			break ;
		*y += data->ystep;
		*x += data->xstep;
		x_pos = (int)(*x / CUBE_TILE);
		y_pos = (int)(*y / CUBE_TILE);
	}
}
