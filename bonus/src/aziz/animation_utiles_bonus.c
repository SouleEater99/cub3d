/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utiles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heisenberg <heisenberg@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:07:21 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/28 17:47:37 by heisenberg       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

char	*get_img_address(t_image *image)
{
	char	*addrr;

	addrr = mlx_get_data_addr(image->img_ptr, &image->bits_per_pixel,
			&image->size_line, &image->endian);
	return (addrr);
}

void	init_player_sprites(t_data *data, char *dir_path, int frames_num)
{
	int		i;
	char	*path_slice[3];
	char	*sprite_path;
	t_image	*frames;

	i = -1;
	data->player.frames = malloc(sizeof(t_image) * frames_num);
	frames = data->player.frames;
	while (++i < frames_num)
	{
		path_slice[0] = ft_itoa(i);
		path_slice[1] = ft_strdup(".xpm");
		path_slice[2] = ft_strjoin(path_slice[0], path_slice[1]);
		sprite_path = ft_strjoin(ft_strdup(dir_path), path_slice[2]);
		frames[i].img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, sprite_path,
				&frames[i].width, &frames[i].height);
		frames[i].img_data = get_img_address(&frames[i]);
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
