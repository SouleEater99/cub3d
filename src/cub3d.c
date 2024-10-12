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

void	ft_write_to_img(t_image *img, int x, int y, int color)
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
			printf("+++++++++++ { char : %c} ++++++++++\n", data->map[j][i]);
			if (data->map[j][i] == '0')
				ft_write_to_img(data->img, i * CUB_SIZE, j * CUB_SIZE, 0x00FFFFFF);
			else
				ft_write_to_img(data->img, i * CUB_SIZE, j * CUB_SIZE, 0x00808080);
			j++;
		}
		i++;
	}

}

int	main(void)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (-1);
	char	*map[] = {	
						"11111111111111111111111111111",
						"10000000000001000000000000001",
						"10000000000000000000000000001",
						"10001111111111000000000000001",
						"10000000000001000000000000001",
						"10000000000001000000000000001",
						"10000000000001111111111000001",
						"10001111111111110000000000001",
						"10000000000001000000100000001",
						"10010000000001000000100000001",
						"10000000000000000000000000001",
						"11111111111111111111111111111",
						NULL};
	data->img = malloc(sizeof(t_image));
	if (!data->img)
		return (free(data), -1);
	data->row = 12;
	data->col = 29;
	data->map = map;

	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HIGH, "Hello world!");
	data->img->img = mlx_new_image(data->mlx, WIDTH, HIGH);
	data->img->addr = mlx_get_data_addr(data->img->img, &data->img->bits_per_pixel, &data->img->line_length,
		&data->img->endian);
    printf("line_length : %d | bit_per_pixel : %d | pixel_data : %d\n", data->img->line_length, data->img->bits_per_pixel, WIDTH * (data->img->bits_per_pixel / 8));
	ft_write_map_img(data);

	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
	mlx_loop(data->mlx);
}