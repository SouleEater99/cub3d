/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utiles_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:13:42 by aelkheta          #+#    #+#             */
/*   Updated: 2024/12/04 14:15:42 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	check_args_num(t_data *data, char **parts, int *current_line)
{
	if (!parts || arr_len(parts) != 2)
	{
		print_error("Error: bad texture or color arguments!\n", __FILE__,
			__LINE__);
		printf(BRED "%d: %s\n" COLOR_RESET, *current_line, data->trimmed);
		free_parse_allocated(data, parts, NULL);
	}
}

/// @brief parse map metadata (01NSEW).
/// @param data a data structure that has all the nessecery variables.
/// @param map_lines
/// @param map_heigh
/// @param current_line
/// @return
bool	parse_metadata(t_data *data, char **map_lines, int map_heigh,
		int *current_line)
{
	char	**parts;

	data->textures_found = 0;
	data->colors_found = 0;
	while (*current_line < map_heigh && (data->textures_found < NUM_TEXTURES
			|| data->colors_found < NUM_COLORS))
	{
		if (is_empty_line(map_lines[*current_line]))
		{
			(*current_line)++;
			continue ;
		}
		data->trimmed = ft_strtrim(map_lines[*current_line], "\n");
		parts = ft_split(data->trimmed, ' ');
		check_args_num(data, parts, current_line);
		if (data->textures_found < NUM_TEXTURES)
			validate_texture(data, parts, &data->textures_found);
		else if (data->colors_found < NUM_COLORS)
			validate_color(data, parts, current_line, &data->colors_found);
		free(data->trimmed);
		free_array(parts);
		(*current_line)++;
	}
	return (data->textures_found == NUM_TEXTURES
		&& data->colors_found == NUM_COLORS);
}
