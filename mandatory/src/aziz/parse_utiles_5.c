/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utiles_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:22:17 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/28 18:24:35 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	check_map_lr(t_data *data, int height, int i, int j)
{
	if ((data->map.map[i][j] == '0' && data->map.map[i][j + 1] == ' ')
		|| (data->map.map[i][j] == ' ' && data->map.map[i][j + 1] == '0'))
	{
		print_error("Error: invalid map border!\n", __FILE__, __LINE__);
		ft_panic(i + data->map.map_start + 1, j + 1, data->map.map[i], data);
	}
	if ((i + 1 < height && data->map.map[i][j] == '0'
		&& j < data->map.map_line_len[i + 1] && data->map.map[i
			+ 1][j] == ' ') || (data->map.map[i][j] == ' ' && i + 1 < height
			&& data->map.map[i + 1][j] == '0'))
	{
		print_error("Error: invalid map border!\n", __FILE__, __LINE__);
		ft_panic(i + data->map.map_start + 1, j + 1, data->map.map[i], data);
	}
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
			check_map_lr(data, height, i, j);
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
