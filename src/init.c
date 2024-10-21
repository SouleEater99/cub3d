
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
	data->row = 12;
	data->col = 24;
	data->mlx = mlx_init();
	data->x_player = (17 * CUB_SIZE ) + (CUB_SIZE / 3);
	data->y_player = (3 * CUB_SIZE) + (CUB_SIZE / 3);
    data->turn_direction = 0;
    data->walk_direction = 0;
	data->rotation_angle = PI / 2;
    data->move_speed = 2;
    data->rotation_speed = 2 * (PI / 180);
	return (data);
}