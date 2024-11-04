
#include "../include/cub3d.h"

void my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void ft_write_cub_to_img(t_image *img, int x, int y, int color)
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

void ft_write_line(t_data *data, int dx, int dy, int color)
{
	// printf("rotationAngle :%f | dx : %d | dy : %d\n",data->rotation_angle  * (180 / PI), abs(dx), abs(dy));
	// printf("x_p : %f| y_P : %f\n",data->x_player, data->y_player);
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
	x = (unsigned int)data->x_player; // + PLAYER_SIZE / 2;
	y = (unsigned int)data->y_player; //	+ PLAYER_SIZE / 2;
	data->i = 0;
	while (data->i <= data->step)
	{
		if (ft_board_protect(data, x, y))
			my_mlx_pixel_put(data->img, x, y, color);
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

int	ft_board_protect(t_data *data, int x, int y)
{
	if ((x > 0 && x < data->col * CUB_SIZE) && (y > 0 && y < data->row * CUB_SIZE))
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

void ft_get_horz_hit(t_data *data, t_ray *ray)
{
	double RayAngle;

	RayAngle = data->rotation_angle;
	ray->ystep = CUB_SIZE;
	if (ft_is_angle_facing_down(RayAngle))
	{
		ray->WallHitY = (data->y_player / CUB_SIZE) * CUB_SIZE + CUB_SIZE;
		ray->WallHitX = ((ray->WallHitY - data->y_player) / tan(RayAngle)) + data->x_player;
		ray->xstep = ray->ystep / tan(RayAngle);
		while ((ray->WallHitX > 0 && ray->WallHitX < data->col * CUB_SIZE) && (ray->WallHitY < data->row * CUB_SIZE && ray->WallHitY > 0))
		{
		// printf("WallHitX : %ld | WallHitY : %ld \n", ray->WallHitX, ray->WallHitY);
		// printf("PlayerX : %f | PlayerY : %f \n", data->x_player, data->y_player);
		// printf("RayAngle : %f | Xstep : %ld\n", RayAngle * ( 180 / PI), ray->xstep);
			if (ft_is_a_wall(data, ray->WallHitX + 1, ray->WallHitY + 1))
				return;
			ray->WallHitY += ray->ystep;
			ray->WallHitX += ray->xstep;
		}
	}
	else
	{
		printf("###########################\n");
		ray->WallHitY = (data->y_player / CUB_SIZE) * CUB_SIZE;
		// ray->WallHitX = ((data->y_player - data->ray->WallHitY) / tan(RayAngle)) + data->x_player;
		ray->WallHitX = ((ray->WallHitY - data->y_player) / tan(RayAngle)) + data->x_player;
		ray->xstep = ray->ystep / tan(RayAngle);
		while ((ray->WallHitX > 0 && ray->WallHitX < data->col * CUB_SIZE) && (ray->WallHitY < data->row * CUB_SIZE && ray->WallHitY > 0))
		{
		printf("WallHitX : %ld | WallHitY : %ld \n", ray->WallHitX, ray->WallHitY);
		printf("PlayerX : %f | PlayerY : %f \n", data->x_player, data->y_player);
		printf("RayAngle : %f | Xstep : %ld\n", RayAngle * ( 180 / PI), ray->xstep);
			if (ft_is_a_wall(data, ray->WallHitX - 1, ray->WallHitY - 1))
				return;
			ray->WallHitY -= ray->ystep;
			ray->WallHitX += ray->xstep;
		}
	}
}

void ft_cast_all_rays(t_data *data)
{
	// 	double	ray_angle;
	// 	int		i;

	// i = 0;
	// ray_angle = data->rotation_angle - (FOV_ANGLE / 2) * (PI / 180);
	ft_get_horz_hit(data, data->ray);
	printf("================ WallHitX : %ld | WallHitY : %ld ==================\n", data->ray->WallHitX, data->ray->WallHitY);
	// if ((data->ray->WallHitX > 0 && data->ray->WallHitX < data->col * CUB_SIZE) && (data->ray->WallHitY > 0 && data->ray->WallHitY < data->row * CUB_SIZE))
	// {
		ft_write_line(data, data->ray->WallHitX - data->x_player, data->ray->WallHitY - data->y_player, 0x000000FF);

	// }
	// ft_write_line(data, cos(data->rotation_angle) *  30, sin(data->rotation_angle) * 30, 0x00FF0000);
	// while (i < WIDTH)
	// {
	// 	ft_write_line(data, cos(ray_angle) *  30, sin(ray_angle) * 30, 0x00FF0000);
	// 	ray_angle = ray_angle + ((double)FOV_ANGLE / (double)WIDTH) * (PI / 180);
	// 	i++;
	// 	printf ("#### { ray_angle : %f} ##### \n", ray_angle);
	// }

	// if (!ft_is_angle_facing_down(data->rotation_angle))
	// {

	// }
}

void ft_write_player_to_img(t_data *data)
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
	ft_cast_all_rays(data);
}

void ft_write_map_img(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->col)
	{
		j = 0;
		while (j < data->row)
		{
			if (data->map[j][i] == '0')
				ft_write_cub_to_img(data->img, i * CUB_SIZE, j * CUB_SIZE, 0x00FFFFFF);
			else
				ft_write_cub_to_img(data->img, i * CUB_SIZE, j * CUB_SIZE, 0x00808080);
			j++;
		}
		i++;
	}
}