#include "../../include/cub3d.h"

void ft_get_virt_hit(t_data *data, double angle, double *x, double *y)
{
	double ystep;
	double xstep;

	if (data->is_face_right)
		*x = (long)(data->x_player / CUBE_TILE) * CUBE_TILE + CUBE_TILE;
	else
		*x = (long)(data->x_player / CUBE_TILE) * CUBE_TILE;
	*y = ((*x - data->x_player) * tan(angle)) + data->y_player;
	xstep = CUBE_TILE;
	if (!data->is_face_right)
		xstep *= -1;
	ystep = xstep * tan(angle);
	if (!data->is_face_down && ystep > 0)
		ystep *= -1;

	if (!data->is_face_right)
		*x -= 1;

	int x_pos = (int)(*x / CUBE_TILE);
	int y_pos = (int)(*y / CUBE_TILE);

	while (y_pos > 0 && y_pos < data->map.map_height && x_pos > 0 && x_pos < data->map.map_line_len[y_pos])
	{
		if (ft_is_a_wall(data, x_pos, y_pos))
			break;
		*y += ystep;
		*x += xstep;

		x_pos = (int)(*x / CUBE_TILE);
		y_pos = (int)(*y / CUBE_TILE);
	}
}

void ft_get_horz_hit(t_data *data, double angle, double *x, double *y)
{
	double ystep;
	double xstep;

	if (data->is_face_down)
		*y = (long)(data->y_player / CUBE_TILE) * CUBE_TILE + CUBE_TILE;
	else
		*y = (long)(data->y_player / CUBE_TILE) * CUBE_TILE;
	*x = ((*y - data->y_player) / tan(angle)) + data->x_player;
	ystep = CUBE_TILE;
	if (!data->is_face_down)
		ystep *= -1;
	xstep = ystep / tan(angle);
	if (!data->is_face_right && xstep > 0)
		xstep *= -1;
	if (!data->is_face_down)
		*y -= 1;


	int x_pos = (int)(*x / CUBE_TILE);
	int y_pos = (int)(*y / CUBE_TILE);

	while (y_pos > 0 && y_pos < data->map.map_height && x_pos > 0 && x_pos < data->map.map_line_len[y_pos])
	{
		if (ft_is_a_wall(data, x_pos, y_pos))
			break;
		*y += ystep;
		*x += xstep;
		
		x_pos = (int)(*x / CUBE_TILE);
		y_pos = (int)(*y / CUBE_TILE);
	}
}

void	ft_get_wall_hit(t_data *data, double angle)
{
	double	VirtHitX;
	double	VirtHitY;
	double	HorzHitX;
	double	HorzHitY;

	HorzHitX = 0;
	HorzHitY = 0;
	VirtHitX = 0;
	VirtHitY = 0;
	// if (data->dataangle != PI / 2 && data->dataangle !=  3 * (PI / 2))
	ft_get_virt_hit(data, angle, &VirtHitX, &VirtHitY);
	// if (data->dataangle != PI / 2 && data->dataangle != (3 * PI) / 2)
	ft_get_horz_hit(data, angle, &HorzHitX, &HorzHitY);
	if (ft_calc_distance(data, HorzHitX, HorzHitY) < ft_calc_distance(data, VirtHitX, VirtHitY))
	{
		data->distance = ft_calc_distance(data, HorzHitX, HorzHitY);
		data->correct_distance = data->distance * cos(angle - data->player_angle);
		data->wall_slice_high = ((double)CUBE_TILE / data->correct_distance) * (double)data->plan_distanced;
		data->wall_hit_x = HorzHitX;
		data->wall_hit_y = HorzHitY;
		data->is_hit_virt = 0;
	}
	else
	{
		data->distance = ft_calc_distance(data, VirtHitX, VirtHitY);
		data->correct_distance = data->distance * cos(angle - data->player_angle);
		data->wall_slice_high = ((double)CUBE_TILE / data->correct_distance) * (double)data->plan_distanced;
		data->wall_hit_x = VirtHitX;
		data->wall_hit_y = VirtHitY;
		data->is_hit_virt = 1;
	}

	// double shadow_factor = fmax(0.2, (1.0 / (data->distance / CUBE_TILE + 1.0))); // Calculate shadow factor

	// printf("Distance: %lf, Shadow Factor: %lf\n", data->distance, shadow_factor);
	
	// printf("======{distance_horz : %f | x = %f | y = %f}======\n", ft_calc_distance(data, HorzHitX, HorzHitY),HorzHitX, HorzHitY);
	// printf("======{distance_virt : %f | x : %f | y : %f}======\n", ft_calc_distance(data, VirtHitX, VirtHitY), VirtHitX, VirtHitY);
	// printf("x_player : %f | y_player : %f\n", data->x_player, data->y_player);
}


// void	ft_write_floor(t_data *data, int i, int color)
// {
// 	int	j;

// 	double distance = SCREEN_HEIGHT - data->end;

// 	color = shade_walls(color, distance);

// 	j = data->end;
// 	while (j < HIGH)
// 	{
//         double distance = (HIGH/2 - j) / (double)(HIGH/2);
//         distance = 1 / (distance);
//         int shaded_color = shade_walls(color, distance);

// 		my_mlx_pixel_put(&data->projection_img, i * WALL_STRIP, j++, shaded_color);
// 	}
// }

void ft_write_floor(t_data *data, int i, int color)
{
    int j;
    double distance;
    
    j = data->end;
    while (j < HIGH)
    {
        distance = (j - HIGH / 2) / (double)(HIGH / 2);
		distance = 1 / distance;
        
        int shaded_color = shade_walls(color, distance);
        my_mlx_pixel_put(&data->projection_img, i * WALL_STRIP, j++, shaded_color);
    }
}

void	ft_write_ceiling(t_data *data, int i, int color)
{
	int	j;

	j = 0;

	while (j < data->start)
	{
        double distance = (HIGH / 2 - j) / (double)(HIGH / 2);
        distance = 1 / (distance);
        int shaded_color = shade_walls(color, distance);

		my_mlx_pixel_put(&data->projection_img, i * WALL_STRIP, j++, shaded_color);
	}
}

void	ft_write_wall(t_data *data, int i)
{
	int		j;

	j = data->start;
	while (j < data->end)
	{
		ft_get_texture_color(data, j);

		data->color = shade_walls(data->color, (data->distance / CUBE_TILE));
		my_mlx_pixel_put(&data->projection_img,i * WALL_STRIP, j++, data->color);
	}
}

void	ft_get_texture_color(t_data *data, int j)
{
	int		texture_offset_x;
	int		texture_offset_y;

	if (data->is_hit_virt)
		texture_offset_x = (int)data->wall_hit_y % TEXTURE_TILE;
	else
		texture_offset_x = (int)data->wall_hit_x % TEXTURE_TILE;
	int	DistanceFromTop = j + (data->wall_slice_high / 2) - (HIGH / 2);
	texture_offset_y = DistanceFromTop * ((double)TEXTURE_TILE / data->wall_slice_high);
	if ((texture_offset_x >= 0 && texture_offset_x < TEXTURE_TILE - 1) && (texture_offset_y >= 0 && texture_offset_y < TEXTURE_TILE - 1))
	{
		if (data->map.map[(int)data->wall_hit_y / CUBE_TILE][(int)data->wall_hit_x / CUBE_TILE] == 'D')
			data->color = ft_get_color(data->textures[4] ,texture_offset_x , texture_offset_y);
		else if (data->is_hit_virt && data->is_face_right)
			data->color = ft_get_color(data->textures[0] ,texture_offset_x , texture_offset_y);
		else if (data->is_hit_virt && !data->is_face_right)
			data->color = ft_get_color(data->textures[1] ,texture_offset_x , texture_offset_y);
		else if (!data->is_hit_virt && data->is_face_down)
			data->color = ft_get_color(data->textures[2] ,texture_offset_x , texture_offset_y);
		else if (!data->is_hit_virt && !data->is_face_down)
			data->color = ft_get_color(data->textures[3] ,texture_offset_x , texture_offset_y);
	}
}

void	ft_write_projection(t_data *data, int i)
{
	// int mouse_factor = data->mouse_y - SCREEN_HEIGHT / 2;

	data->start = (HIGH / 2) - (data->wall_slice_high / 2); // + mouse_factor;
	if (data->start < 0)
		data->start = 0;
	data->end = (HIGH / 2) + (data->wall_slice_high / 2); // + mouse_factor;
	if (data->end > HIGH)
		data->end = HIGH;
	ft_write_ceiling(data, i, data->map.ceiling_color);
	ft_write_wall(data, i);	
	ft_write_floor(data, i, data->map.floor_color);
}

void ft_cast_all_rays(t_data *data)
{
	int		i;
	double	angle;

	i = 0;
	angle = data->player_angle - (FOV / 2);
	while (i < data->num_rays)
	{
		if (angle > 2 * PI)
   			angle -= 2 * PI;
		else if (angle < 0)
    		angle += 2 * PI;
	    data->is_face_down = ft_is_angle_facing_down(angle);
	    data->is_face_right = ft_is_angle_facing_right(angle);
		data->flag = 0;
		ft_get_wall_hit(data, angle);
		ft_write_projection(data, i);
        // ft_write_line(data, (data->wall_hit_x - data->x_player) * data->Factor_Scale_Map, (data->wall_hit_y - data->y_player) * data->Factor_Scale_Map, RED);
		angle = angle + ((double)FOV / (double)data->num_rays);
		i++;
	}

	render_sprites(data);
}
