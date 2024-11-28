/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heisenberg <heisenberg@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:48:00 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/28 14:24:52 by heisenberg       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	free_int_array(int **int_array, int arr_len)
{
	int	i;

	i = -1;
	if (!int_array)
		return ;
	while (++i < arr_len)
		free(int_array[i]);
	free(int_array);
}

/// @brief
/// @param arr
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

void	free_parse_allocated(t_data *data, char **parts)
{
	free(data->trimmed);
	free_array(parts);
	free_array(data->map_lines);
	ft_free_all(NULL, data, 1);
}

void	destroy_images(void *mlx_ptr, t_image **images, int images_num)
{
	int	i;

	i = -1;
	while (++i < images_num)
	{
		if (images[i]->img_ptr)
			mlx_destroy_image(mlx_ptr, images[i]->img_ptr);
	}
	free(images);
}

void	clean_up(t_data *data)
{
	if (data)
	{
		if (data->textures[0])
			destroy_images(data->mlx_ptr, data->textures, NUM_TEXTURES);
		if (data->map.map_line_len)
			free(data->map.map_line_len);
		if (data->map.map)
			free_array(data->map.map);
		if (data->player.frames)
			destroy_images(data->mlx_ptr, &data->player.frames,
				data->player.frames_num);
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
}
