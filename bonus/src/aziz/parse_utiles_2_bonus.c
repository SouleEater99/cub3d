/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utiles_2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:17:09 by aelkheta          #+#    #+#             */
/*   Updated: 2024/12/03 13:47:29 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

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
