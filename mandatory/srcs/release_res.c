/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_res.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 09:02:40 by aelkheta          #+#    #+#             */
/*   Updated: 2024/10/13 10:20:26 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr && arr[++i])
		free(arr[i]);
	free(arr);
}

void free_map(char **map)
{
    int i;

	if (!map)
		return ;
    i = -1;
    while (map && map[++i])
        free(map[i]);
    free(map);
}

void clean_up(t_data *data)
{
	if (data->no_texture_path)
		free(data->no_texture_path);
	if (data->so_texture_path)
		free(data->so_texture_path);
	if (data->we_texture_path)
		free(data->we_texture_path);
	if (data->ea_texture_path)
		free(data->ea_texture_path);
	
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	
	#ifdef __linux__
	
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);

	# endif

	if (data->image)
		mlx_destroy_image(data->mlx_ptr, data->image);
	if (data->map)
		free_array(data->map);
	if (data->mlx_ptr)
		free(data->mlx_ptr);
}

// void clean_up(t_data *data)
// {
//     if (data->win_ptr)
//         mlx_destroy_window(data->mlx_ptr, data->win_ptr);
//     if (data->mlx_ptr)
//     {
//         // mlx_destroy_display(data->mlx_ptr);
//         free(data->mlx_ptr);
//     }
//     free_map(data->map);
// }
