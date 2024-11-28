/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:41:10 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/28 11:55:24 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/// @brief
/// @param texture_path
/// @return
char	*parse_texture(char *texture_path)
{
	if (!check_extension(texture_path, ".xpm"))
		return (NULL);
	return (texture_path);
}

char	**get_texture_ptr(t_data *data, char *texture_dir)
{
	char	**texture_ptr;

	texture_ptr = NULL;
	if (!ft_strcmp("NO", texture_dir))
		texture_ptr = &data->no_texture_path;
	else if (!ft_strcmp("SO", texture_dir))
		texture_ptr = &data->so_texture_path;
	else if (!ft_strcmp("WE", texture_dir))
		texture_ptr = &data->we_texture_path;
	else if (!ft_strcmp("EA", texture_dir))
		texture_ptr = &data->ea_texture_path;
	else if (!ft_strcmp("DR", texture_dir))
		texture_ptr = &data->dr_texture_path;
	return (texture_ptr);
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
	char	**texture_ptr;

	texture_ptr = NULL;
	texture_ptr = get_texture_ptr(data, parts[0]);
	if (texture_ptr)
	{
		*texture_ptr = parse_texture(parts[1]);
		if (!*texture_ptr)
			free_parse_allocated(data, parts);
		data->textures[*textures_found] = load_texture(data->mlx_ptr,
				*texture_ptr);
		if (!data->textures[*textures_found])
			free_parse_allocated(data, parts);
		(*textures_found)++;
	}
}
