
#include "../include/cub3d.h"

void	ft_setup_texture(u_int32_t *texture)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < TEXTURE_SIZE)
	{
		while (y < TEXTURE_SIZE)
		{
			if (x % 8 && y % 8)
				texture[(y++ * TEXTURE_SIZE) + x] = (u_int32_t)BLUE;
			else
				texture[(y++ * TEXTURE_SIZE) + x] = 0;
		}
		x++;
	}
}

t_data *ft_init_data()
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->img = malloc(sizeof(t_image));
	if (!data->img)
		return (free(data), NULL);
	data->row = 24;
	data->col = 12;
	data->width = data->row * CUB_SIZE;
	data->high = data->col * CUB_SIZE;
	data->mlx = mlx_init();
	data->x_player = 5 * 40 + 20;
	data->y_player = 5 * 40 + 20;
    data->turn_direction = 0;
    data->walk_direction = 0;
	data->rotation_angle = PI / 2 ;
	data->minimap_scale_factor = 0.2;
	data->num_rays = data->width / WALL_STRIP;
	data->ray = malloc(sizeof(t_ray) * data->num_rays);
	if (!data->ray)
		return (free(data->img), free(data), NULL);
	data->texture = (u_int32_t * ) malloc(sizeof(u_int32_t) * (u_int32_t)TEXTURE_SIZE * (u_int32_t)TEXTURE_SIZE);
	if (!data->texture)
		return (free(data->img), free(data->ray), free(data), NULL);
	ft_setup_texture(data->texture);
	data->plan_distance = (320 / 2) / tan(FOV_ANGLE / 2);
    data->move_speed = 4;
    data->rotation_speed = 4 * (PI / 180); // whene it is 1 in right direction it is stop in 1.0032 riadines
	return (data);
}

void	ft_free_all(t_data *data, char *msg, int status)
{
	if (data)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		mlx_destroy_display(data->mlx);
		free(data->img);
		free(data->ray);
		free(data->texture);
		free(data);
	}
	if (msg)
		write(2, msg, strlen(msg));
	exit (status);
}