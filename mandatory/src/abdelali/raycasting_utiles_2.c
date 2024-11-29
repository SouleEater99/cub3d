/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utiles_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:59:28 by heisenberg        #+#    #+#             */
/*   Updated: 2024/11/29 09:47:59 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	int	pixel_index;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	pixel_index = (y * image->size_line) + (x * (image->bits_per_pixel / 8));
	*(int *)(image->img_data + pixel_index) = color;
}

int	ft_is_angle_facing_down(double angle)
{
	if (angle > 0 && angle < PI)
		return (1);
	return (0);
}

int	ft_is_angle_facing_right(double angle)
{
	if ((angle < PI / 2 && angle >= 0) || (angle > (3 * PI) / 2))
		return (1);
	return (0);
}

int	ft_board_protect(int Width, int High, int x, int y)
{
	if ((x >= 0 && x < Width) && (y >= 0 && y < High))
		return (1);
	return (0);
}

int	ft_is_a_wall(t_data *data, int x, int y)
{
	if (ft_board_protect(data->map.map_line_len[y], data->map.map_height, x,
			y) == 1)
	{
		if (data->map.map[y][x] == '1')
			return (1);
	}
	return (0);
}
