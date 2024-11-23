#include "../include/cub3d.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->img_data + (y * img->size_line + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


int ft_is_angle_facing_down(double angle)
{
	if (angle > 0 && angle < PI)
		return (1);
	return (0);
}

int ft_is_angle_facing_right(double angle)
{
	if ((angle < PI / 2 && angle >= 0) || (angle > (3 * PI) / 2))
		return (1);
	return (0);
}

int ft_board_protect(int Width, int High, int x, int  y)
{
	if ((x >= 0 && x < Width) && (y >= 0 && y < High))
		return (1);
	return (0);
}


int ft_is_a_wall(t_data *data, int x, int y)
{
	// printf("x : %d | y : %d\n", x, y);
	if (ft_board_protect(data->row, data->col, x / CUBE_TILE, y / CUBE_TILE) == 1)
	{
		if (data->map[y / CUBE_TILE][x / CUBE_TILE] == '1')
			return (1);
		else if (data->map[y / CUBE_TILE][x / CUBE_TILE] == 'D' && !data->door.is_open)
			return (1);
		else if (data->flag == 1 && data->map[y / CUBE_TILE][x / CUBE_TILE] == 'D' && data->door.is_open)
			return (1);
	} 
	return (0);
}

int	ft_is_player_inside_wall(t_data *data)
{
	double	x;
	double	y;

	x = data->x_player + (cos(data->player_angle) * data->move_step);
	y = data->y_player + (sin(data->player_angle) * data->move_step);
	if (data->map[(int)y / CUBE_TILE][(int) x / CUBE_TILE] == '1' || (data->map[(int)y / CUBE_TILE][(int) x / CUBE_TILE] == 'D' && !data->door.is_open))
		return (0);
	data->x_player = x;
	data->y_player = y;
	return (1);
}

double	ft_normalize_angle(double angle)
{
	if (angle > 2 * PI)
 	   angle -= 2 * PI;
	else if (angle < 0)
 	   angle += 2 * PI;
	return (angle);
}

void ft_write_line(t_data *data, int dx, int dy, int color)
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
	x = (unsigned int)data->x_player * data->factor_scale_map; 
	y = (unsigned int)data->y_player * data->factor_scale_map;
	data->i = 0;
	while (data->i <= data->step)
	{
		if (ft_board_protect(WIDTH, HIGH, x, y))
			my_mlx_pixel_put(&data->projection_img, x, y, color);
		x += x_increment;
		y += y_increment;
		data->i++;
	}
}


double ft_calc_distance(t_data *data, double x, double y)
{
    double dx = data->x_player - x;
    double dy = data->y_player - y;
    return sqrt(dx * dx + dy * dy); // Euclidean distance
}