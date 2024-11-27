/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:29:41 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/27 20:42:42 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_free_all(char *msg, t_data *data, int exit_status)
{
	if (data)
	{
		if (data->door)
			free(data->door);
		
		int i = -1;
		while(++i < NUM_TEXTURES)
		{
					if (data->textures[i]->img_ptr)
		    mlx_destroy_image(data->mlx_ptr, data->textures[i]->img_ptr);
		}
	
		if (data->win_ptr)
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		if (data->mlx_ptr)
		{
			mlx_destroy_display(data->mlx_ptr);
			free(data->mlx_ptr);
		}
		// free(data->door);
	}
	if (msg)
		write(2, msg, strlen(msg));
	exit(exit_status);
}
