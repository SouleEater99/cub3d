
#include "../include/cub3d.h"

void    ft_write_cub(t_data *data, int x, int y, int color)
{
    int i;
    int j;

    i = 0;
    while (i < (int)(CUBE_TILE * data->factor_scale_map))
    {
        j = 0;
        while (j < (int)(CUBE_TILE * data->factor_scale_map))
        {

			// printf("========+{x : %d | y : %d }=======\n", x + i ,y + j);
            my_mlx_pixel_put(&data->projection_img, i + x, j + y, color);
            j++;
        }
        i++;
    }

}


void   ft_create_pojection_img(t_data *data)
{
    data->projection_img.img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HIGH);
    if (!data->projection_img.img_ptr)
        ft_free_all("Image Projection Image Fail\n", data, 1);
    data->projection_img.img_data = mlx_get_data_addr(data->projection_img.img_ptr, &data->projection_img.bits_per_pixel, &data->projection_img.size_line, &data->projection_img.endian);
    if (!data->projection_img.img_data)
        ft_free_all("Projection data Addres Fail\n", data, 1);

}

int     ft_get_color(t_image *img, int x, int y)
{
    int Color;

    // if (ft_board_protect(Img->Width, Img->High, x, y))
        Color = *(int *)(img->img_data + (y * img->size_line) + x  * (img->bits_per_pixel / 8));
    return (Color);
}

void	ft_write_player_view(t_data *data)
{
	int		x;
	double	angle;

	x = 0;
	angle = data->player_angle - (FOV / 2);
	while (x < data->num_rays)
	{
		if (angle > 2 * PI)
   			angle -= 2 * PI;
		else if (angle < 0)
    		angle += 2 * PI;
 		ft_write_line(data, cos(angle) * 60 * data->factor_scale_map, sin(angle) * 60 * data->factor_scale_map, BLUE);
		angle = angle + ((double)FOV / (double)data->num_rays);
		x++;
	}

}

void	ft_write_player(t_data *data)
{
	int		x;
	int		y;

	x= 0;
    while (x < PLAYER_TILE)
    {
        y = 0;
        while (y < PLAYER_TILE)
        {
            my_mlx_pixel_put(&data->projection_img, ((data->x_player - (PLAYER_TILE / 2) ) + x) * data->factor_scale_map, ((data->y_player - (PLAYER_TILE / 2)) + y) * data->factor_scale_map, RED);
            y++;
        }
        x++;
    }
	
}

void	ft_write_mini_map(t_data *data)
{

	int		x;
	int		y;
	double	ratio;

	ratio = (double)CUBE_TILE * data->factor_scale_map;
 	y = 0;
    while (y < data->col && y * ratio < HIGH)
    {
        x = 0;
        while (x < data->row && x  * ratio < WIDTH)
        {
			// printf("+=+++++++{x : %d | y : %d | ratio : %d}+++++++\n", x ,y, ratio);
            if (data->map[y][x] == '1')
                ft_write_cub(data, x * ratio, y * ratio, WHITE);
            else if (data->map[y][x] == 'D')
                ft_write_cub(data, x * ratio, y * ratio, YELLOW);
            else
                ft_write_cub(data, x * ratio, y * ratio, BLACK);
            x++;
        }
        y++;
    }
	ft_write_player(data);
    // ft_write_player_wall_hit(data);
	ft_write_player_view(data);

}

// void    ft_write_player_wall_hit(t_data  *data)
// {
// 	ft_write_player(data);
//     // ft_write_player_wall_hit(data);
// 	ft_write_player_view(data);

// }

int     ft_get_door_index(t_data *data, int x, int y)
{
    int i;

    i = 0;
    while (i < data->n_door)
    {
        if (data->door[i].x == x && data->door[i].y == y)
            return (i);
        i++;
    }
    return (0);
}

void    ft_write_player_wall_hit(t_data  *data)
{
	data->is_face_down = ft_is_angle_facing_down(data->player_angle);
	data->is_face_right = ft_is_angle_facing_right(data->player_angle);
	ft_get_wall_hit(data, data->player_angle);
	if (ft_board_protect(data->row, data->col, data->wall_hit_x / CUBE_TILE, data->wall_hit_y / CUBE_TILE) == 1)
    {
        if (data->map[(int)data->wall_hit_y / CUBE_TILE][(int)data->wall_hit_x / CUBE_TILE] == 'D' && data->distance < WALL_DISTANCE)
        {
            data->door_index = ft_get_door_index(data, data->wall_hit_x / CUBE_TILE, data->wall_hit_y / CUBE_TILE);
            if (data->door_index < 0)
                ft_free_all("Door_index Fail \n", data, 1);
            if (!data->door[data->door_index].is_open)
                data->door[data->door_index].is_open = 1;
            else if (data->door[data->door_index].is_open)
                data->door[data->door_index].is_open = 0;
            printf("========== { index:  %c | is_open : %d } ==========\n",data->map[(int)data->wall_hit_y / CUBE_TILE][(int)data->wall_hit_x / CUBE_TILE], data->door[data->door_index].is_open);
        }
            // printf("===========\n");
 		// Ft_Write_Line(data,(data->wall_hit_x -  data->X_Player) * data->Factor_Scale_Map , (data->wall_hit_y - data->Y_Player)* data->Factor_Scale_Map, BLUE);
    }
        
}
