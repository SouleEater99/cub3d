#include "../include/cub3d.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->Data + (y * img->Lenght + x * (img->N_Bytes / 8));
	*(unsigned int*)dst = color;
}


void ft_write_line(t_data *Data, int dx, int dy, int color)
{
	double x;
	double y;
	double x_increment;
	double y_increment;

	if (abs(dx) >= abs(dy))
		data->step = abs(dx);
	else
		data->step = abs(dy);
	x_increment = dx / data->step;
	y_increment = dy / data->step;
	x = (unsigned int)Data->X_Player * Data->Factor_Scale_Map; 
	y = (unsigned int)Data->Y_Player * Data->Factor_Scale_Map   ; 
	while (data->i <= data->step)
	{
		if (ft_board_protect(data, x, y))
			my_mlx_pixel_put(data->img, x, y, color);
			my_mlx_pixel_put(data, x, y, color);
		x += x_increment;
		y += y_increment;
		data->i++;
	}
}