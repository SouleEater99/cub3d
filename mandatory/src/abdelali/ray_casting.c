/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:30:15 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/29 09:30:28 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	calc_virt_dist(t_data *data, double angle, double virt_hit_x,
		double VirtHitY)
{
	data->distance = ft_calc_distance(data, virt_hit_x, VirtHitY);
	data->correct_distance = data->distance * cos(angle - data->player_angle);
	data->wall_slice_high = ((double)CUBE_TILE / data->correct_distance)
		* (double)data->plan_distanced;
	data->wall_hit_x = virt_hit_x;
	data->wall_hit_y = VirtHitY;
	data->is_hit_virt = 1;
}

void	calc_horiz_dist(t_data *data, double angle, double HorzHitX,
		double HorzHitY)
{
	data->distance = ft_calc_distance(data, HorzHitX, HorzHitY);
	data->correct_distance = data->distance * cos(angle - data->player_angle);
	data->wall_slice_high = ((double)CUBE_TILE / data->correct_distance)
		* (double)data->plan_distanced;
	data->wall_hit_x = HorzHitX;
	data->wall_hit_y = HorzHitY;
	data->is_hit_virt = 0;
}

void	ft_get_wall_hit(t_data *data, double angle)
{
	double	virt_hit_x;
	double	virt_hit_y;
	double	horz_hit_x;
	double	horz_hit_y;

	virt_hit_x = 0;
	virt_hit_y = 0;
	horz_hit_x = 0;
	horz_hit_y = 0;
	ft_get_virt_hit(data, angle, &virt_hit_x, &virt_hit_y);
	ft_get_horz_hit(data, angle, &horz_hit_x, &horz_hit_y);
	if (ft_calc_distance(data, horz_hit_x, horz_hit_y) < ft_calc_distance(data,
			virt_hit_x, virt_hit_y))
		calc_horiz_dist(data, angle, horz_hit_x, horz_hit_y);
	else
		calc_virt_dist(data, angle, virt_hit_x, virt_hit_y);
}
