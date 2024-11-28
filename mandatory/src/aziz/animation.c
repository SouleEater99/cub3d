/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:59:35 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/28 11:13:51 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_player_sprites(t_data *data, char *dir_path, int frames_num)
{
	int		i;
	char	*path_slice[3];
	char	*sprite_path;

	i = -1;
	data->player.frames = malloc(sizeof(t_image) * frames_num);
	while (++i < frames_num)
	{
		path_slice[0] = ft_itoa(i);
		path_slice[1] = ft_strdup(".xpm");
		path_slice[2] = ft_strjoin(path_slice[0], path_slice[1]);
		sprite_path = ft_strjoin(ft_strdup(dir_path), path_slice[2]);
		data->player.frames[i].img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
				sprite_path, &data->player.frames[i].width,
				&data->player.frames[i].height);
		data->player.frames[i].img_data = mlx_get_data_addr(data->player.frames[i].img_ptr,
				&data->player.frames[i].bits_per_pixel,
				&data->player.frames[i].size_line,
				&data->player.frames[i].endian);
		free(path_slice[2]);
		free(path_slice[1]);
		free(sprite_path);
	}
	data->frames_num = frames_num;
}

void	draw_pixel(t_image *image, int dx, int dy, int sprite_pixel)
{
	if (dx >= 0 && dx < SCREEN_WIDTH && dy >= 0 && dy < SCREEN_HEIGHT)
		((int *)image->img_data)[dy * SCREEN_WIDTH + dx] = sprite_pixel;
}

void	render_sprites_to_image(t_image *image, t_image *sprite_image, int x,
		int y)
{
	int	sy;
	int	sx;
	int	dx;
	int	dy;
	int	sprite_pixel;

	if (!image || !sprite_image || !image->img_data || !sprite_image->img_data)
		return ;
	sy = -1;
	while (++sy < sprite_image->height)
	{
		sx = -1;
		while (++sx < sprite_image->width)
		{
			if (sx < 0 || sx >= SCREEN_WIDTH || sy < 0 || sy >= SCREEN_HEIGHT)
				continue ;
			sprite_pixel = ((int *)sprite_image->img_data)[sy
				* sprite_image->width + sx];
			if ((sprite_pixel & 0xFF000000) == 0xFF000000) // Handle transparency (assuming 0xFF000000 is fully transparent) 
				continue ;
			dx = x + sx;
			dy = y + sy;
			draw_pixel(image, dx, dy, sprite_pixel);
		}
	}
}

int	get_frame(t_data *data, int frame_delay)
{
	if (data->frame_counter >= frame_delay)
	{
		data->frame++;
		data->frame_counter = 0;             // this is for reset frame counter.
		if (data->frame >= data->frames_num) // to reset animation.
		{
			data->frame = 0;
			data->shoot = 0;
		}
	}
	return (data->frame);
}

void	render_sprites(t_data *data)
{
	int		x;
	int		y;
	int		frame_delay;
	t_image	sprite_image;

	if (!data || !data->mlx_ptr || !data->win_ptr
		|| !data->projection_img.img_ptr || !data->player.frames)
	{
		print_error("Error: frames not initiates!\n", __FILE__, __LINE__);
		exit(1);
	}
	frame_delay = FRAME_DELAY;
	sprite_image = data->player.frames[0];
	if (data->shoot)
	{
		data->frame_counter++;
		data->frame = get_frame(data, frame_delay);
		sprite_image = data->player.frames[data->frame];
	}
	x = SCREEN_WIDTH / 2 - sprite_image.width / 2;
	y = SCREEN_HEIGHT - sprite_image.height;
	render_sprites_to_image(&data->projection_img, &sprite_image, x, y);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->projection_img.img_ptr, 0, 0);
}
