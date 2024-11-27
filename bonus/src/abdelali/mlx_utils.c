#include "../../include/cub3d.h"

// void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = img->img_data + (y * img->size_line + x * (img->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

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
		else if (data->map.map[y][x] == 'D')
		{
			data->door_index = ft_get_door_index(data, x, y);
			if (data->door_index == -1)
				ft_free_all("Door_index Fail \n", data, 1);
			if (!data->door[data->door_index].is_open)
				return (1);
			else if (data->flag == 1 && data->door[data->door_index].is_open)
				return (1);
		}
	}
	return (0);
}

int	ft_is_player_inside_wall(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->x_player + (cos(data->player_angle) * data->move_step);
	new_y = data->y_player + (sin(data->player_angle) * data->move_step);
	// this is for glissing.
	if (data->map.map[(int)data->y_player / CUBE_TILE][(int)new_x
		/ CUBE_TILE] == '0')
		data->x_player = new_x;
	if (data->map.map[(int)new_y / CUBE_TILE][(int)data->x_player
		/ CUBE_TILE] == '0')
		data->y_player = new_y;
	if (data->map.map[(int)data->y_player / CUBE_TILE][(int)new_x
		/ CUBE_TILE] == 'D')
	{
		data->door_index = ft_get_door_index(data, new_x / CUBE_TILE,
				data->y_player / CUBE_TILE);
		if (data->door_index == -1)
			ft_free_all("Door_index Fail \n", data, 1);
		printf("========== { index:  %c | is_open : %d } ==========\n",
			data->map.map[(int)data->wall_hit_y
			/ CUBE_TILE][(int)data->wall_hit_x / CUBE_TILE],
			data->door[data->door_index].is_open);
		if (!data->door[data->door_index].is_open)
			return (0);
		else
			data->x_player = new_x;
	}
	if (data->map.map[(int)new_y / CUBE_TILE][(int)data->x_player
		/ CUBE_TILE] == 'D')
	{
		data->door_index = ft_get_door_index(data, data->x_player / CUBE_TILE,
				new_y / CUBE_TILE);
		if (data->door_index == -1)
			ft_free_all("Door_index Fail \n", data, 1);
		printf("========== { index:  %c | is_open : %d } ==========\n",
			data->map.map[(int)data->wall_hit_y
			/ CUBE_TILE][(int)data->wall_hit_x / CUBE_TILE],
			data->door[data->door_index].is_open);
		if (!data->door[data->door_index].is_open)
			return (0);
		else
			data->y_player = new_y;
	}
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

void	ft_write_line(t_data *data, int dx, int dy, int color)
{
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

double	ft_calc_distance(t_data *data, double x, double y)
{
	double dx = data->x_player - x;
	double dy = data->y_player - y;
	return (sqrt(dx * dx + dy * dy)); // Euclidean distance
}