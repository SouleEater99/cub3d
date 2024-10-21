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
	ft_write_map_img(data);
	ft_write_player_to_img(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
}

int	ft_key_hook(int keycode, t_data *data)
{
	if (keycode == XK_Up)
	{
		data->y_player-=4;
		ft_update_img(data);
		
	}
	if (keycode == XK_Down)
	{
		data->y_player+=4;
		ft_update_img(data);

	}
	if (keycode == XK_Left)
	{
		data->turn_direction = -1;
		data->rotation_angle = data->rotation_angle + (data->turn_direction * data->rotation_speed);
		ft_update_img(data);

	}
	if (keycode == XK_Right)
	{
		data->turn_direction = 1;
		data->rotation_angle = data->rotation_angle + (data->turn_direction * data->rotation_speed);
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
						"100000000000000000000001",
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
    printf("line_length : %d | bit_per_pixel : %d | pixel_data : %d\n", data->img->line_length, data->img->bits_per_pixel, WIDTH * (data->img->bits_per_pixel / 8));
	ft_update_img(data);
	mlx_hook(data->mlx_win, 2, 1L << 0, ft_key_hook, data);
	mlx_loop(data->mlx);

}

