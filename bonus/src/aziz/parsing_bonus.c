/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:57:39 by aelkheta          #+#    #+#             */
/*   Updated: 2024/12/04 14:19:38 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	get_max_width(t_data *data)
{
	int	i;

	i = -1;
	data->map.map_width = 0;
	while (++i < data->map.map_height)
	{
		data->map.map_line_len[i] = ft_strlen(data->map.map[i]);
		while (data->map.map_line_len[i] > 0
			&& ft_isspace(data->map.map[i][data->map.map_line_len[i] - 1]))
		{
			data->map.map_line_len[i] -= 1;
			data->map.map_width = fmax(data->map.map_width,
					data->map.map_line_len[i]);
		}
	}
	return (data->map.map_width);
}

void	init_map(t_data *data, char **lines, int current_line, int height)
{
	int	i;

	while (current_line < height && is_empty_line(lines[current_line]))
		current_line++;
	i = height;
	while (--i - current_line > 0 && is_empty_line(lines[i]))
		;
	data->map.map_start = current_line;
	data->map.map_height = i - current_line + 1;
	data->map.map = copy_array(&lines[current_line], data->map.map_height);
	data->map.map_line_len = malloc(sizeof(int) * data->map.map_height);
	if (!data->map.map_line_len)
		ft_free_all(NULL, data, 1);
	data->map.map_width = get_max_width(data);
	if (data->map.map_height >= MAX_HEIGHT || data->map.map_width >= MAX_WIDTH)
	{
		free_array(lines);
		ft_free_all("Error: map too big\n", data, 1);
	}
	else if (data->map.map_height < 2 || data->map.map_width < 3)
	{
		free_array(lines);
		ft_free_all("Error: map too small\n", data, 1);
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

	if (ac != 2)
	{
		print_error("Error: bad arguments!\n", __FILE__, __LINE__);
		printf("Usage: ./cub3d <map_path>\n");
		return (1);
	}
	ft_memset(&data->map, 0, sizeof(t_map));
	if (!check_extension(av[1], ".cub"))
		return (0);
	data->lines = read_map_lines(av[1], &height);
	if (!data->lines)
		return (0);
	if (!validate_map_cont(data, data->lines, height))
		return (0);
	return (1);
}
