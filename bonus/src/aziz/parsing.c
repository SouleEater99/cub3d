/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:57:39 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/28 18:22:03 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_map(t_data *data, char **lines, int current_line, int height)
{
	int	i;

	data->map.map_start = current_line;
	data->map.map_height = height - current_line;
	data->map.map = copy_array(&lines[current_line], data->map.map_height);
	data->map.map_width = ft_strlen(data->map.map[0]);
	data->map.map_line_len = malloc(sizeof(int) * data->map.map_height);
	if (!data->map.map_line_len)
		ft_free_all(NULL, data, 1);
	i = -1;
	while (++i < data->map.map_height)
	{
		data->map.map_line_len[i] = ft_strlen(data->map.map[i]);
		if (i + 1 < data->map.map_height)
			data->map.map_line_len[i] -= 1;
	}
}

int	validate_map_cont(t_data *data, char **lines, int height)
{
	int	current_line;

	current_line = 0;
	if (!parse_metadata(data, lines, height, &current_line))
	{
		free_array(lines);
		return (0);
	}
	init_map(data, lines, current_line, height);
	free_array(lines);
	if (!validate_map(data))
		return (0);
	if (!validate_map_borders(data, data->map.map, data->map.map_height))
		return (0);
	return (1);
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
	if (!validate_map_cont(data, lines, height))
		return (0);
	return (1);
}
