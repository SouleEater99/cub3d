/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:41:10 by aelkheta          #+#    #+#             */
/*   Updated: 2024/12/03 17:35:09 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	get_texture_pos(char *texture_dir)
{
	if (!ft_strcmp("NO", texture_dir))
		return (0);
	else if (!ft_strcmp("SO", texture_dir))
		return (1);
	else if (!ft_strcmp("WE", texture_dir))
		return (2);
	else if (!ft_strcmp("EA", texture_dir))
		return (3);
	else if (!ft_strcmp("DR", texture_dir))
		return (4);
	return (-1);
}

t_image	*load_texture(void *mlx, char *filename)
{
	t_image	*texture;

	if (!mlx || !filename)
		return (NULL);
	texture = malloc(sizeof(t_image));
	if (!texture)
		return (NULL);
	texture->img_ptr = mlx_xpm_file_to_image(mlx, filename, &texture->width,
			&texture->height);
	if (!texture->img_ptr)
	{
		free(texture);
		return (NULL);
	}
	texture->img_data = mlx_get_data_addr(texture->img_ptr,
			&texture->bits_per_pixel, &texture->size_line, &texture->endian);
	return (texture);
}

void	validate_texture(t_data *data, char **parts, int *textures_found)
{
	int	texture_pos;

	texture_pos = get_texture_pos(parts[0]);
	if (texture_pos != -1)
	{
		if (!check_extension(parts[1], ".xpm"))
			free_parse_allocated(data, parts, "Error: Bad textures\n");
		data->textures_path[texture_pos] = ft_strdup(parts[1]);
		(*textures_found)++;
	}
	else
		free_parse_allocated(data, parts, "Error: Bad textures\n");
}
