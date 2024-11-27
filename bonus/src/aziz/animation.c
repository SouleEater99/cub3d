/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:59:35 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/27 20:27:07 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_player_sprites(t_data *data, char *dir_path, int frames_num)
{
	int		i;
	char	*str;
	char	*sprite_index;
	char	*extension;
	char	*sprite_path;

	i = -1;
	data->player.frames = malloc(sizeof(t_image) * frames_num);
	while (++i < frames_num)
	{
		sprite_index = ft_itoa(i);
		extension = ft_strdup(".xpm");
		str = ft_strjoin(sprite_index, extension);
		sprite_path = ft_strjoin(ft_strdup(dir_path), str);
		data->player.frames[i].img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
				sprite_path, &data->player.frames[i].width,
				&data->player.frames[i].height);
		data->player.frames[i].img_data = mlx_get_data_addr(data->player.frames[i].img_ptr,
				&data->player.frames[i].bits_per_pixel,
				&data->player.frames[i].size_line,
				&data->player.frames[i].endian);
		free(str);
		free(extension);
		free(sprite_path);
	}
	data->frames_num = frames_num;
}

void	render_sprites_to_image(t_image *image, t_image *sprite_image, int x,
		int y)
{
	int	sy;
	int	sx;
	int	sprite_pixel;
	int	dx;
	int	dy;

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
			// Handle transparency (assuming 0xFF000000 is fully transparent)
			if ((sprite_pixel & 0xFF000000) == 0xFF000000)
				continue ;
			dx = x + sx;
			dy = y + sy;
			// Ensure we don't draw outside the main image bounds
			if (dx >= 0 && dx < SCREEN_WIDTH && dy >= 0 && dy < SCREEN_HEIGHT)
				((int *)image->img_data)[dy * SCREEN_WIDTH + dx] = sprite_pixel;
		}
	}
}

void	render_sprites(t_data *data)
{
	static int	frame = 0;
	static int	frame_counter = 0;
	int			frame_delay;
	t_image		*img;
	t_image		sprite_image;
	int			x;
	int			y;

	if (!data || !data->mlx_ptr || !data->win_ptr
		|| !data->projection_img.img_ptr || !data->player.frames)
	{
		print_error("Error: frames not initiates!\n", __FILE__, __LINE__);
		exit(1);
	}
	// static int shoot = 0;
	frame_delay = 4;
	img = &data->projection_img;
	sprite_image = data->player.frames[0];
	// if (data->shoot)
	// {
	// shoot = 1;
	// data->shoot = 0;
	// }
	if (data->shoot)
	{
		// take_a_shoot();
		frame_counter++;
		if (frame_counter >= frame_delay)
		{
			frame++;
			frame_counter = 0;             // this is for reset frame counter.
			if (frame >= data->frames_num) // to reset animation.
			{
				frame = 0;
				data->shoot = 0;
			}
		}
		sprite_image = data->player.frames[frame];
	}
	x = SCREEN_WIDTH / 2 - sprite_image.width / 2;
	y = SCREEN_HEIGHT - sprite_image.height;
	render_sprites_to_image(img, &sprite_image, x, y);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img->img_ptr, 0, 0);
}
