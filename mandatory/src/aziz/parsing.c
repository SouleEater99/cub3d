/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:57:39 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/28 13:36:28 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/// @brief check the map file extension (.cub).
/// @param file_path the file path.
/// @return 0 if the extension not valid otherwise 1.
int	check_extension(const char *file_path, const char *extension)
{
	int	fd;
	int	extension_len;

	if (!file_path || !extension)
		return (0);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		print_error("Error: File does not exist!\n", __FILE__, __LINE__);
		return (0);
	}
	else
		close(fd);
	extension_len = ft_strlen(extension);
	if (!ft_strnstr(&file_path[ft_strlen(file_path) - extension_len], extension,
			extension_len))
	{
		print_error("Error, bad file extension [example.cub]!\n", __FILE__,
			__LINE__);
		return (0);
	}
	return (1);
}

/// @brief chech is a line empty or not.
/// @param line the line.
/// @return true if the line empty otherwise false.
bool	is_empty_line(const char *line)
{
	int	i;

	i = -1;
	if (!line)
		return (true);
	while (line[++i] && ft_isspace(line[i]))
		;
	return (!line[i]);
}

int	is_empty_map(const char *map_path, int *height)
{
	int		fd;
	char	*line;
	bool	is_empty;

	is_empty = true;
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (print_error("Error: failed to open map file!\n", __FILE__,
				__LINE__), 0);
	*height = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!is_empty_line(line))
			is_empty = false;
		(*height)++;
		free(line);
		line = get_next_line(fd);
	}
	if (*height == 0 || is_empty)
		return (print_error("Error: map file is empty!\n", __FILE__, __LINE__),
			close(fd), 0);
	close(fd);
	return (1);
}

char	**read_lines(int fd, int *height)
{
	int		i;
	char	**lines;

	i = -1;
	lines = malloc(sizeof(char *) * (*height + 1));
	if (!lines)
		return (print_error("Error: failed to allocated memory for map!\n",
				__FILE__, __LINE__), NULL);
	while (++i < *height)
	{
		lines[i] = get_next_line(fd);
		if (!lines[i])
		{
			while (--i >= 0)
				free(lines[i]);
			free(lines);
			return (print_error("Error: failed to get next line!\n", __FILE__,
					__LINE__), close(fd), NULL);
		}
	}
	lines[*height] = NULL;
	return (lines);
}

/// @brief count, allocate and copy the map.
/// @param map_path map file path.
/// @param height a pointer to the lenght of the map.
/// @return the allocated map.
char	**read_map_lines(const char *map_path, int *height)
{
	int		fd;
	char	**lines;

	*height = 0;
	if (!is_empty_map(map_path, height))
		return (NULL);
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (print_error("Error: failed to open map file!\n", __FILE__,
				__LINE__), NULL);
	lines = read_lines(fd, height);
	close(fd);
	return (lines);
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
	int		textures_found;
	int		colors_found;
	char	**parts;

	textures_found = 0;
	colors_found = 0;
	while (*current_line < map_heigh && (textures_found < NUM_TEXTURES
			|| colors_found < NUM_COLORS))
	{
		if (is_empty_line(map_lines[*current_line]))
		{
			(*current_line)++;
			continue ;
		}
		data->trimmed = ft_strtrim(map_lines[*current_line], "\n");
		parts = ft_split(data->trimmed, ' ');
		if (!parts || arr_len(parts) != 2)
		{
			print_error("Error: bad texture or color arguments!\n", __FILE__,
				__LINE__);
			printf(BRED "%d: %s\n" COLOR_RESET, *current_line, data->trimmed);
			free_parse_allocated(data, parts);
		}
		if (textures_found < NUM_TEXTURES)
			validate_texture(data, parts, &textures_found);
		else if (colors_found < NUM_COLORS)
			validate_color(data, parts, current_line, &colors_found);
		free(data->trimmed);
		free_array(parts);
		(*current_line)++;
	}
	return (textures_found == NUM_TEXTURES && colors_found == NUM_COLORS);
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

/// @brief
/// @param data
/// @return
bool	validate_map(t_data *data)
{
	int		i;
	bool	is_player_found;
	int		door_found;
	int		j;

	i = -1;
	while (++i < data->map.map_height)
	{
		data->map.map_line_len[i] = ft_strlen(data->map.map[i]);
		if (i + 1 < data->map.map_height)
			data->map.map_line_len[i] -= 1;
	}
	i = -1;
	is_player_found = false;
	data->n_door = get_doors_num(&data->map);
	if (data->n_door != -1)
	{
		data->door = malloc(sizeof(t_door) * data->n_door);
		if (!data->door)
			ft_free_all("Error: can not allocate memory for doors!\n", data,
				EXIT_FAILURE);
		ft_memset(data->door, 0, sizeof(t_door) * data->n_door);
	}
	door_found = -1;
	while (++i < data->map.map_height)
	{
		data->map.map_line_len[i] = ft_strlen(data->map.map[i]);
		if (i + 1 < data->map.map_height)
			data->map.map_line_len[i] -= 1;
		j = -1;
		while (++j < data->map.map_line_len[i])
		{
			if (!ft_strchr(SUPPORTED_CHARS_BONUS, data->map.map[i][j]))
			{
				print_error("Error: unsupported metadata (characters)!\n",
					__FILE__, __LINE__);
				printf(BRED "%d: %s\n" COLOR_RESET, i, data->map.map[i]);
				ft_free_all(NULL, data, 1);
			}
			if (ft_strchr(PLAYER_DIR, data->map.map[i][j]))
			{
				if (is_player_found)
				{
					print_error("Error: multiple players!\n", __FILE__,
						__LINE__);
					printf(BRED "%d: %s\n" COLOR_RESET, i, data->map.map[i]);
					ft_free_all(NULL, data, 1);
				}
				data->player_x = j + 0.5;
				data->player_y = i + 0.5;
				data->player_dir = data->map.map[i][j];
				is_player_found = true;
				data->map.map[i][j] = '0';
			}
			if (data->map.map[i][j] == 'D')
				init_door(data->door, ++door_found, j, i);
		}
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
		printf(BRED "%d: %s\n" COLOR_RESET, i, data->map.map[i]);
		ft_panic(i + 1, i + 1, map[0], data);
	}
	i = -1;
	line = map_height - 1;
	while (map[line][++i] && ft_strchr("1 ", map[line][i]))
		;
	if (map[line][i] != '\n' && map[line][i] != '\0')
	{
		print_error("Error: invalid map border!\n", __FILE__, __LINE__);
		printf(BRED "%d: %s\n" COLOR_RESET, i, data->map.map[i]);
		ft_panic(line + 1, i + 1, map[line], data);
	}
	return (1);
}

int	check_left_right(t_data *data, char **map, int height)
{
	int	j;
	int	i;

	i = 0;
	while (++i < height - 1)
	{
		if (is_empty_line(map[i]))
			continue ;
		j = -1;
		while (++j < data->map.map_line_len[i] && ft_isspace(map[i][j]))
			;
		if (map[i][j] != '1' || map[i][data->map.map_line_len[i] - 1] != '1')
		{
			print_error("Error: invalid map border!\n", __FILE__, __LINE__);
			ft_panic(i + data->map.map_start + 1, j + 1, map[i], data);
		}
		while (j + 1 < data->map.map_line_len[i])
		{
			if ((map[i][j] == '0' && map[i][j + 1] == ' ') || (map[i][j] == ' '
					&& map[i][j + 1] == '0'))
			{
				print_error("Error: invalid map border!\n", __FILE__, __LINE__);
				ft_panic(i + data->map.map_start + 1, j + 1, map[i], data);
			}
			if ((i + 1 < height && map[i][j] == '0'
					&& j < data->map.map_line_len[i + 1] && map[i
					+ 1][j] == ' ') || (map[i][j] == ' ' && i + 1 < height
					&& map[i + 1][j] == '0'))
			{
				print_error("Error: invalid map border!\n", __FILE__, __LINE__);
				ft_panic(i + data->map.map_start + 1, j + 1, map[i], data);
			}
			j++;
		}
	}
	return (1);
}

int	**init_int_arr(int *lines_len, int arr_len)
{
	int	i;
	int	**arr;

	i = -1;
	arr = malloc(sizeof(int *) * arr_len);
	if (!arr)
		return (NULL);
	while (++i < arr_len)
	{
		arr[i] = ft_calloc(lines_len[i], sizeof(int));
		if (!arr[i])
		{
			while (--i >= 0)
				free(arr[i]);
			free(arr);
			return (NULL);
		}
	}
	return (arr);
}

/// @brief check if map is surounded by walls.
/// @param data
/// @param map
/// @param height
/// @return true if map is surounded by walls.
int	validate_map_borders(t_data *data, char **map, int height)
{
	int	**visited;

	if (!check_first_last(data, map, data->map.map_height))
		return (0);
	if (!check_left_right(data, map, height))
		return (0);
	visited = init_int_arr(data->map.map_line_len, data->map.map_height);
	if (!visited)
		ft_free_all(NULL, data, 1);
	if (!dfs(&data->map, visited, data->player_x, data->player_y))
	{
		print_error("Error: map is not surrounded by walls!\n", __FILE__,
			__LINE__);
		ft_free_all(NULL, data, 1);
	}
	free_int_array(visited, data->map.map_height);
	return (1);
}

char	**copy_array(char **array, int array_len)
{
	int		i;
	char	**cpy_array;

	i = -1;
	if (array_len <= 0)
		return (NULL);
	cpy_array = (char **)ft_calloc(sizeof(char *), array_len + 1);
	if (!cpy_array)
		return (NULL);
	while (++i < array_len)
		cpy_array[i] = ft_strdup(array[i]);
	return (cpy_array);
}

/// @brief
/// @param data
/// @param ac
/// @param av
/// @return
int	parse_map(t_data *data, int ac, char **av)
{
	int		height;
	char	**lines;
	int		current_line;

	if (ac != 2)
	{
		print_error("Error: bad arguments!\n", __FILE__, __LINE__);
		printf("Usage: ./cub3d <map_path>\n");
		return (0);
	}
	ft_memset(&data->map, 0, sizeof(t_map));
	if (!check_extension(av[1], ".cub"))
		return (0);
	lines = read_map_lines(av[1], &height);
	if (!lines)
		return (0);
	current_line = 0;
	if (!parse_metadata(data, lines, height, &current_line))
	{
		free_array(lines);
		return (0);
	}
	while (current_line < height && is_empty_line(lines[current_line]))
		current_line++;
	data->map.map_start = current_line;
	data->map.map_height = height - current_line;
	data->map.map = copy_array(&lines[current_line], data->map.map_height);
	data->map.map_width = ft_strlen(data->map.map[0]);
	data->map.map_line_len = malloc(sizeof(int) * data->map.map_height);
	free_array(lines);
	if (!data->map.map_line_len)
	{
		free_array(lines);
		return (0);
	}
	if (!validate_map(data))
	{
		free(data->map.map_line_len);
		free_array(lines);
		return (0);
	}
	if (!validate_map_borders(data, data->map.map, data->map.map_height))
	{
		free_array(lines);
		return (0);
	}
	return (1);
}
