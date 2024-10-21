
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
		{
			my_mlx_pixel_put(img, x + j++, y + i, color);
			if (j == CUB_SIZE - 1)
				my_mlx_pixel_put(img, x + j, y + i, 0);
		}
		i++;
	}
	j = 0;
	if (i == CUB_SIZE - 1)
		while (j < CUB_SIZE - 1)
			my_mlx_pixel_put(img, x + j++, y + i, 0);
}

void ft_write_line(t_data *data,int dx, int dy)
{
	printf("rotationAngle :%f | dx : %d | dy : %d\n",data->rotation_angle , abs(dx), abs(dy));
	double	x;
	double	y;
	double	x_increment;
	double	y_increment;
	
	if (abs(dx) >= abs(dy))
		data->step = abs(dx);
	else
		data->step = abs(dy);
	x_increment = dx / data->step;
	y_increment = dy / data->step;
	x = data->x_player + PLAYER_SIZE / 2;
	y = data->y_player + PLAYER_SIZE / 2;
	data->i = 0;
	while (data->i <= data->step)
	{
		my_mlx_pixel_put(data->img, x, y, 0x00FF0000);
		x += x_increment;
		y += y_increment;
		data->i++;
	}
}

void	ft_write_player_to_img(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
			my_mlx_pixel_put(data->img, data->x_player + i, data->y_player + j++, 0x00FF0000);
		i++;
	}
	ft_write_line(data, cos(data->rotation_angle) *  30, sin(data->rotation_angle) * 15);
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