/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:40:58 by aelkheta          #+#    #+#             */
/*   Updated: 2024/12/03 12:57:00 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	get_color(char **colors)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	free_array(colors);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

/// @brief check the color format (0,0,0).
/// @return true if the format is correct.
int	check_color_format(const char *str_color)
{
	int	i;
	int	sep_count;
	int	color_len;

	i = -1;
	sep_count = 0;
	if (!str_color)
		return (0);
	color_len = ft_strlen(str_color);
	while (++i < color_len)
	{
		if ((i == 0 || str_color[i - 1] == ',') && str_color[i] == '+')
			continue ;
		if (!ft_isdigit(str_color[i]) && str_color[i] != ',')
			return (0);
		if (str_color[i] == ',')
			sep_count++;
	}
	if (sep_count != 2)
		return (0);
	return (1);
}

/// @brief Takes a string color (255,255,0) and convert it to inteager.
/// @param str_color string color to be converted to inteager.
/// @return inteager color
// int str_to_color(const char *str_color)
int64_t	parse_color(const char *str_color)
{
	int64_t	color;
	char	**colors;

	color = -1;
	if (!check_color_format(str_color))
	{
		print_error("Error: color format should be like this: 255,255,255\n",
			__FILE__, __LINE__);
		return (color);
	}
	colors = ft_split(str_color, ',');
	if (!colors || arr_len(colors) != 3)
	{
		free_array(colors);
		return (-1);
	}
	color = get_color(colors);
	return (color);
}

void	validate_color(t_data *data, char **parts, int *current_line,
		int *colors_found)
{
	int	*color_ptr;

	color_ptr = NULL;
	if (!ft_strcmp("F", parts[0]))
		color_ptr = &data->map.floor_color;
	else if (!ft_strcmp("C", parts[0]))
		color_ptr = &data->map.ceiling_color;
	else
	{
		print_error("Error: bad texture or color arguments!\n", __FILE__,
			__LINE__);
		printf(BRED "%d: %s\n" COLOR_RESET, *current_line, data->trimmed);
		free_parse_allocated(data, parts, NULL);
	}
	if (color_ptr)
	{
		*color_ptr = parse_color(parts[1]);
		if (*color_ptr == -1)
		{
			print_error("Error: bad color!\n", __FILE__, __LINE__);
			printf(BRED "%d: %s\n" COLOR_RESET, *current_line, data->trimmed);
			free_parse_allocated(data, parts, NULL);
		}
		(*colors_found)++;
	}
}
