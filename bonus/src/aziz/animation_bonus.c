/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:59:35 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/28 13:07:11 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

/// @brief Handle transparency (assuming 0xFF000000 is fully transparent)
/// @param data
/// @param sprite_image
/// @param x
/// @param y
void	render_sprites_to_image(t_data *data, t_image *sprite_image, int x,
		int y)
{
	int	sy;
	int	sx;
	int	dx;
	int	dy;

	if (!data->image || !sprite_image || !data->image->img_data
		|| !sprite_image->img_data)
		return ;
	sy = -1;
	while (++sy < sprite_image->height)
	{
		sx = -1;
		while (++sx < sprite_image->width)
		{
			if (sx < 0 || sx >= SCREEN_WIDTH || sy < 0 || sy >= SCREEN_HEIGHT)
				continue ;
			data->sprite_pixel = ((int *)sprite_image->img_data)[sy
				* sprite_image->width + sx];
			if ((data->sprite_pixel & 0xFF000000) == 0xFF000000)
				continue ;
			dx = x + sx;
			dy = y + sy;
			draw_pixel(data->image, dx, dy, data->sprite_pixel);
		}
	}
}

int	get_frame(t_data *data, int frame_delay)
{
	if (data->frame_counter >= frame_delay)
	{
		data->frame++;
		data->frame_counter = 0;
		if (data->frame >= data->frames_num)
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
	render_sprites_to_image(data, &sprite_image, x, y);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->projection_img.img_ptr, 0, 0);
}
