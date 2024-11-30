/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:29:41 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/29 09:47:24 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_free_all(char *msg, t_data *data, int exit_status)
{
	int i;

	i = -1;
	while (++i < data->textures_found)
	{
		if (data->textures_path[i])
			free(data->textures_path[i]);
		if (data->textures[i] && data->textures[i]->img_ptr)
			mlx_destroy_image(data->mlx_ptr, data->textures[i]->img_ptr);
		free(data->textures[i]);
	}
	if (data)
	{
		if (data->map.map_line_len)
			free(data->map.map_line_len);
		if (data->map.map)
			free_array(data->map.map);
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
