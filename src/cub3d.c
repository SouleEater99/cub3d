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

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}



void	ft_write_cub_to_img(t_image *img, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < CUB_SIZE - 1)
	{
		j = 0;
		while (j < CUB_SIZE - 1)
			my_mlx_pixel_put(img, x + i, y + j++, color);
		i++;
	}
}

void	ft_write_player_to_img(t_image *img, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	ft_write_cub_to_img(img, x, y, 0x00FFFFFF);
	while (i < 10)
	{
		j = 0;
		while (j < 10)
			my_mlx_pixel_put(img, x + i, y + j++, color);
		i++;
	}
}

void	ft_write_map_img(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->col)
	{
		j = 0;
		while (j < data->row)
		{
			if (data->map[j][i] == 'P')
				ft_write_cub_to_img(data->img, i * CUB_SIZE, j * CUB_SIZE, 0x00FFFFFF);
			else if (data->map[j][i] == '0')
				ft_write_cub_to_img(data->img, i * CUB_SIZE, j * CUB_SIZE, 0x00FFFFFF);
			else
				ft_write_cub_to_img(data->img, i * CUB_SIZE, j * CUB_SIZE, 0x00808080);
			j++;
		}
		i++;
	}

}

// int	ft_loop_hook(void *param)
// {
// 	t_data *data;
// 	unsigned int static i;

// 	data = (t_data *)param;

// }

// int	ft_key_hook(int keycode, t_data *data)
// {
// 	if (keycode == XK_Up)
// 	{

// 	}
// 	if (keycode == XK_Down)
// 	{

// 	}
// 	if (keycode == XK_Left)
// 	{

// 	}
// 	if (keycode == XK_Right)
// 	{
		
// 	}

// }

t_data *ft_init()
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->img = malloc(sizeof(t_image));
	if (!data->img)
		return (free(data), NULL);
	data->row = 12;
	data->col = 29;
	data->mlx = mlx_init();
	data->x_player = (17 * CUB_SIZE ) + (CUB_SIZE / 3);
	data->y_player = (3 * CUB_SIZE) + (CUB_SIZE / 3);
	return (data);
}

int	main(void)
{
	t_data *data;

	char	*map[] = {	
						"11111111111111111111111111111",
						"10000000000001000000000000001",
						"10000000000000000000000000001",
						"10001111111111000P00000000001",
						"10000000000001000000000000001",
						"10000000000001000000000000001",
						"10000000000001111111111000001",
						"10001111111111110000000000001",
						"10000000000001000000100000001",
						"10010000000001000000100000001",
						"10000000000000000000000000001",
						"11111111111111111111111111111",
						NULL};
	data = ft_init();
	data->map = map;

	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HIGH, "Hello world!");
	data->img->img = mlx_new_image(data->mlx, WIDTH, HIGH);
	data->img->addr = mlx_get_data_addr(data->img->img, &data->img->bits_per_pixel, &data->img->line_length,
		&data->img->endian);
    printf("line_length : %d | bit_per_pixel : %d | pixel_data : %d\n", data->img->line_length, data->img->bits_per_pixel, WIDTH * (data->img->bits_per_pixel / 8));
	ft_write_map_img(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
	usleep(1000);
	ft_write_player_to_img(data->img, data->x_player, data->y_player, 0x00FF0000);
	sleep(2);
	// mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
	// mlx_hook(data->mlx_win, 2, 1L << 0, ft_key_hook, data);	
	mlx_loop(data->mlx);

}