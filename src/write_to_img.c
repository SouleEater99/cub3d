
#include "../include/cub3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;
	t_image	*img;

	img = data->img;
	if ((x > 0 && x < data->width) && (y > 0 && y < data->high))
	{
		dst = img->addr + ((y * img->line_length) + (x * (img->bits_per_pixel / 8)));
		*(unsigned int *)dst = color;
	}
}

void ft_write_cub_to_img(t_data *data, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < CUB_SIZE - 1)
	{
		j = 0;
		while (j < CUB_SIZE - 1)
		{
			my_mlx_pixel_put(data, x + j++, y + i, color);
			if (j == CUB_SIZE - 1)
				my_mlx_pixel_put(data, x + j, y + i, 0);
		}
		i++;
	}
	j = 0;
	if (i == CUB_SIZE - 1)
		while (j < CUB_SIZE - 1)
			my_mlx_pixel_put(data, x + j++, y + i, 0);
}

void ft_write_line(t_data *data, double dx, double dy, int color)
{
	double x;
	double y;
	double x_increment;
	double y_increment;

	if (abs((int)dx) >= abs((int)dy))
		data->step = abs((int)dx);
	else
		data->step = abs((int)dy);
	x_increment = dx / data->step;
	y_increment = dy / data->step;
	x = (unsigned int)data->x_player * data->minimap_scale_factor; // + PLAYER_SIZE / 2;
	y = (unsigned int)data->y_player * data->minimap_scale_factor   ; //	+ PLAYER_SIZE / 2;
	data->i = 0;
	while (data->i <= data->step)
	{
		if (ft_board_protect(data, x, y))
			my_mlx_pixel_put(data, x, y, color);
		x += x_increment;
		y += y_increment;
		data->i++;
	}
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

int ft_board_protect(t_data *data, double x, double  y)
{
	if ((x > 0 && x < data->width) && (y > 0 && y < data->high))
		return (1);
	return (0);
}

int ft_is_a_wall(t_data *data, int x, int y)
{
	if (ft_board_protect(data, x, y) == 1)
		if (data->map[y / CUB_SIZE][x / CUB_SIZE] == '1')
			return (1);
	return (0);
}

void ft_get_virt_hit(t_data *data,t_ray *ray, double *x, double *y)
{
	double ystep;
	double xstep;
	int		IsFaceDown;
	int		IsFaceRight;


	IsFaceDown = ft_is_angle_facing_down(ray->RayAngle);
	IsFaceRight = ft_is_angle_facing_right(ray->RayAngle);
	if (IsFaceRight)
		*x = (long)(data->x_player / CUB_SIZE) * CUB_SIZE + CUB_SIZE;
	else
		*x = (long)(data->x_player / CUB_SIZE) * CUB_SIZE;
	*y = ((*x - data->x_player) * tan(ray->RayAngle)) + data->y_player;
	xstep = CUB_SIZE;
	if (!IsFaceRight)
		xstep *= -1;
	ystep = xstep * tan(ray->RayAngle);
	if (!IsFaceDown && ystep > 0)
		ystep *= -1;

	if (!IsFaceRight)
		*x -= 1;
	while ((*x > 0 && *x < data->width) && (*y < data->high && *y > 0))
	{
		if (ft_is_a_wall(data, *x, *y))
			break;
		*y += ystep;
		*x += xstep;
	}
}

void ft_get_horz_hit(t_data *data, t_ray *ray, double *x, double *y)
{
	double ystep;
	double xstep;
	int		IsFaceDown;
	int		IsFaceRight;


	IsFaceDown = ft_is_angle_facing_down(ray->RayAngle);
	IsFaceRight = ft_is_angle_facing_right(ray->RayAngle);
	if (IsFaceDown)
		*y = (long)(data->y_player / CUB_SIZE) * CUB_SIZE + CUB_SIZE;
	else
		*y = (long)(data->y_player / CUB_SIZE) * CUB_SIZE;
	*x = ((*y - data->y_player) / tan(ray->RayAngle)) + data->x_player;
	ystep = CUB_SIZE;
	if (!IsFaceDown)
		ystep *= -1;
	xstep = ystep / tan(ray->RayAngle);
	if (!IsFaceRight && xstep > 0)
		xstep *= -1;
	if (!IsFaceDown)
		*y -= 1;
	while ((*x > 0 && *x < data->width) && (*y < data->high && *y > 0))
	{
		if (ft_is_a_wall(data, *x, *y))
			break;
		*y += ystep;
		*x += xstep;
	}
}

double ft_calc_distance(t_data *data, double x, double y)
{
    double dx = data->x_player - x;
    double dy = data->y_player - y;
    return sqrt(dx * dx + dy * dy); // Euclidean distance
}

void	ft_get_wall_hit(t_data *data, t_ray *ray)
{
	double	VirtHitX;
	double	VirtHitY;
	double	HorzHitX;
	double	HorzHitY;

	HorzHitX = 0;
	HorzHitY = 0;
	VirtHitX = 0;
	VirtHitY = 0;
	// if (ray->RayAngle != PI / 2 && ray->RayAngle !=  3 * (PI / 2))
		ft_get_virt_hit(data, ray, &VirtHitX, &VirtHitY);
	// if (ray->RayAngle != PI / 2 && ray->RayAngle != (3 * PI) / 2)
		ft_get_horz_hit(data, ray, &HorzHitX, &HorzHitY);
	if (ft_calc_distance(data, HorzHitX, HorzHitY) < ft_calc_distance(data, VirtHitX, VirtHitY))
	{
		ray->distance = ft_calc_distance(data, HorzHitX, HorzHitY);
		ray->CorrectDistance = ray->distance * cos(ray->RayAngle - data->rotation_angle);
		ray->WallSliceHigh = ((double)CUB_SIZE / ray->CorrectDistance) * (double)data->plan_distance;
		ray->WallHitX = HorzHitX;
		ray->WallHitY = HorzHitY;
		ray->IsHitVirt = 0;
	}
	else
	{
		ray->distance = ft_calc_distance(data, VirtHitX, VirtHitY);
		ray->CorrectDistance = ray->distance * cos(ray->RayAngle - data->rotation_angle);
		ray->WallSliceHigh = ((double)CUB_SIZE / ray->CorrectDistance) * (double)data->plan_distance;
		ray->WallHitX = VirtHitX;
		ray->WallHitY = VirtHitY;
		ray->IsHitVirt = 1;
	}
	// printf("======{distance_horz : %f | x = %f | y = %f}======\n", ft_calc_distance(data, HorzHitX, HorzHitY),HorzHitX, HorzHitY);
	// printf("======{distance_virt : %f | x : %f | y : %f}======\n", ft_calc_distance(data, VirtHitX, VirtHitY), VirtHitX, VirtHitY);
	// printf("x_player : %f | y_player : %f\n", data->x_player, data->y_player);
}

void ft_cast_all_rays(t_data *data)
{
		int		i;
		double	angle;
		t_ray	*ray;

	i = 0;
	ray = data->ray;
	angle = data->rotation_angle - (FOV_ANGLE / 2);
	while (i < data->num_rays)
	{
		if (angle > 2 * PI)
   			angle -= 2 * PI;
		else if (angle < 0)
    		angle += 2 * PI;
		(ray + i)->RayAngle = angle;
		ft_get_wall_hit(data, ray + i);
		angle = angle + ((double)FOV_ANGLE / (double)data->num_rays);
		i++;
	}

}

void ft_write_player_to_img(t_data *data, t_ray *ray)
{
	int i;
	int j;

	i = 0;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
			my_mlx_pixel_put(data, data->minimap_scale_factor * ( data->x_player + i), data->minimap_scale_factor * (data->y_player + j++), 0x00FF0000);
		i++;
	}
	i = 0;
	while (i < data->num_rays)
	{
		ft_write_line(data, data->minimap_scale_factor * (ray->WallHitX - data->x_player), data->minimap_scale_factor * (ray->WallHitY - data->y_player), 0x00000000);
		ray++;
		i++;
	}
}

void ft_write_map_img(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->row)
	{
		j = 0;
		while (j < data->col)
		{
			if (data->map[j][i] == '0')
				ft_write_cub_to_img(data, data->minimap_scale_factor * (i * CUB_SIZE), data->minimap_scale_factor * (j * CUB_SIZE), 0x00FFFFFF);
			else
				ft_write_cub_to_img(data, data->minimap_scale_factor * (i * CUB_SIZE), data->minimap_scale_factor * (j * CUB_SIZE), 0x00808080);
			j++;
		}
		i++;
	}
}