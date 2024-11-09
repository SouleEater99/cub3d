
#include "../include/cub3d.h"

t_data *ft_init_data()
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->img = malloc(sizeof(t_image));
	if (!data->img)
		return (free(data), NULL);
	data->ray = malloc(sizeof(t_ray) * NUM_RAYS + 1);
	if (!data->ray)
		return (free(data->img), free(data), NULL);
	data->row = 12;
	data->col = 24;
	data->mlx = mlx_init();
	data->x_player = 5 * 40 + 20;
	data->y_player = 5 * 40 + 20;
    data->turn_direction = 0;
    data->walk_direction = 0;
	data->rotation_angle = (11 * PI) /6 ;
	data->plan_distance = (WIDTH / 2) / tan(FOV_ANGLE / 2);
    data->move_speed = 2;
    data->rotation_speed = 2 * (PI / 180); // whene it is 1 in right direction it is stop in 1.0032 riadines
	return (data);
}

void	ft_free_all(t_data *data, char *msg, int status)
{
	if (data)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		mlx_destroy_display(data->mlx);
		free(data->ray);
		free(data);
	}
	if (msg)
		write(2, msg, strlen(msg));
	exit (status);
}