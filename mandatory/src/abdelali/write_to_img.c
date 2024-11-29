/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_img.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:30:27 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/29 10:01:17 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*get_img_address(t_image *image)
{
	char	*addrr;

	addrr = mlx_get_data_addr(image->img_ptr, &image->bits_per_pixel,
			&image->size_line, &image->endian);
	return (addrr);
}

void	ft_write_cub(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < (int)(CUBE_TILE * data->factor_scale_map))
	{
		j = 0;
		while (j < (int)(CUBE_TILE * data->factor_scale_map))
		{
			my_mlx_pixel_put(&data->projection_img, i + x, j + y, color);
			j++;
		}
		i++;
	}
}

// mlx_get_data_addr(data->projection_img.img_ptr,
// 			&data->projection_img.bits_per_pixel,
// 			&data->projection_img.size_line, &data->projection_img.endian);
void	ft_create_pojection_img(t_data *data)
{
	data->projection_img.img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HIGH);
	if (!data->projection_img.img_ptr)
		ft_free_all("Image Projection Image Fail\n", data, 1);
	data->projection_img.img_data = get_img_address(&data->projection_img);
	if (!data->projection_img.img_data)
		ft_free_all("Projection data Addres Fail\n", data, 1);
}

int	ft_get_color(t_image *img, int x, int y)
{
	int	color;

	color = *(int *)(img->img_data + (y * img->size_line) + x
			* (img->bits_per_pixel / 8));
	return (color);
}

void	ft_write_player_wall_hit(t_data *data)
{
	data->is_face_down = ft_is_angle_facing_down(data->player_angle);
	data->is_face_right = ft_is_angle_facing_right(data->player_angle);
	ft_get_wall_hit(data, data->player_angle);
}
