/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utiles_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:15:35 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/29 09:52:21 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	check_map_characters(t_data *data, int i, int j, bool *is_player_found)
{
	if (!ft_strchr(SUPPORTED_CHARS, data->map.map[i][j]))
	{
		print_error("Error: unsupported metadata (characters)!\n", __FILE__,
			__LINE__);
		printf(BRED "%d: %s\n" COLOR_RESET, i, data->map.map[i]);
		ft_free_all(NULL, data, 1);
	}
	if (ft_strchr(PLAYER_DIR, data->map.map[i][j]))
	{
		if (*is_player_found)
		{
			print_error("Error: multiple players!\n", __FILE__, __LINE__);
			printf(BRED "%d: %s\n" COLOR_RESET, i, data->map.map[i]);
			ft_free_all(NULL, data, 1);
		}
		data->player_x = j + 0.5;
		data->player_y = i + 0.5;
		data->player_dir = data->map.map[i][j];
		*is_player_found = true;
		data->map.map[i][j] = '0';
	}
}

/// @brief
/// @param data
/// @return
bool	validate_map(t_data *data)
{
	int		i;
	int		j;
	bool	is_player_found;

	i = -1;
	is_player_found = false;
	while (++i < data->map.map_height)
	{
		j = -1;
		while (++j < data->map.map_line_len[i])
			check_map_characters(data, i, j, &is_player_found);
	}
	if (!is_player_found)
		print_error("Error: no player found!\n", __FILE__, __LINE__);
	return (is_player_found);
}

void	print_map(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->map_height)
		printf("%s", map->map[i]);
	printf("\n\n");
	printf("ceiling_color: 0x%X\n", map->ceiling_color);
	printf("floor_color: 0x%X\n", map->floor_color);
	printf("\n");
	printf("North texture: %s\n", map->no_texture_path);
	printf("South texture: %s\n", map->so_texture_path);
	printf("East texture: %s\n", map->ea_texture_path);
	printf("West texture: %s\n", map->we_texture_path);
	printf("\n");
}

void	print_str(char *str, int index)
{
	int	i;

	i = -1;
	while (++i < index)
		printf(" ");
	printf("%s", str);
}

/// @brief check the first line and the last one if all ones
/// @param data
/// @param map
/// @param map_start
/// @param map_height
/// @return
int	check_first_last(t_data *data, char **map, int map_height)
{
	int	i;
	int	line;

	i = -1;
	line = 0;
	while (map[line][++i] && ft_strchr("1 ", map[line][i]))
		;
	if (map[line][i] != '\n')
	{
		print_error("Error: invalid map border!\n", __FILE__, __LINE__);
		ft_panic(i + 1, i + 1, map[0], data);
	}
	i = -1;
	line = map_height - 1;
	while (map[line][++i] && ft_strchr("1 ", map[line][i]))
		;
	if (map[line][i] != '\n' && map[line][i] != '\0')
	{
		print_error("Error: invalid map border!\n", __FILE__, __LINE__);
		ft_panic(line + 1, i + 1, map[line], data);
	}
	return (1);
}
