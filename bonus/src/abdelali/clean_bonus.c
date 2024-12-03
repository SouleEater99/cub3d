/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:29:41 by aelkheta          #+#    #+#             */
/*   Updated: 2024/12/03 12:54:18 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	free_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < NUM_TEXTURES)
	{
		if (data->textures_path[i])
			free(data->textures_path[i]);
		if (data->textures[i] && data->textures[i]->img_ptr)
			mlx_destroy_image(data->mlx_ptr, data->textures[i]->img_ptr);
		free(data->textures[i]);
	}
	if (data->map.map_line_len)
		free(data->map.map_line_len);
	if (data->map.map)
		free_array(data->map.map);
	if (data->player.frames)
	{
		i = -1;
		while (++i < data->player.frames_num)
		{
			if (data->player.frames[i].img_ptr)
				mlx_destroy_image(data->mlx_ptr,
					data->player.frames[i].img_ptr);
		}
		free(data->player.frames);
	}
}

void	ft_free_all(char *msg, t_data *data, int exit_status)
{
	if (data)
	{
		free_all(data);
		if (data->door)
			free(data->door);
		if (data->win_ptr)
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		if (data->mlx_ptr)
		{
			mlx_destroy_display(data->mlx_ptr);
			free(data->mlx_ptr);
		}
	}
	if (msg)
		write(2, msg, strlen(msg));
	exit(exit_status);
}
