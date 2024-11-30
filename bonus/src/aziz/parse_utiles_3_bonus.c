/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utiles_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heisenberg <heisenberg@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:13:42 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/28 19:37:40 by heisenberg       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	check_args_num(t_data *data, char **parts, int *current_line)
{
	if (!parts || arr_len(parts) != 2)
	{
		print_error("Error: bad texture or color arguments!\n", __FILE__,
			__LINE__);
		printf(BRED "%d: %s\n" COLOR_RESET, *current_line, data->trimmed);
		free_parse_allocated(data, parts);
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

int	get_doors_num(t_map *map)
{
	int	x;
	int	y;
	int	doors_num;

	x = -1;
	y = -1;
	doors_num = 0;
	if (!map || !map->map || !map->map_line_len)
		return (-1);
	while (++y < map->map_height)
	{
		x = -1;
		while (++x < map->map_line_len[y])
		{
			if (map->map[y][x] == DOOR_SYMBOL)
				doors_num++;
		}
	}
	return (doors_num);
}

void	init_door(t_door *door, int index, int x_pos, int y_pos)
{
	door[index].is_open = 0;
	door[index].x = x_pos;
	door[index].y = y_pos;
}

t_door	*allocate_doors(t_data *data)
{
	data->n_door = get_doors_num(&data->map);
	if (data->n_door != -1)
	{
		data->door = malloc(sizeof(t_door) * data->n_door);
		if (!data->door)
			ft_free_all("Error: can not allocate memory for doors!\n", data,
				EXIT_FAILURE);
		ft_memset(data->door, 0, sizeof(t_door) * data->n_door);
	}
	return (data->door);
}
