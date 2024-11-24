/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:57:39 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/24 10:48:05 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/cub3d.h"

// DFS (Depth-First Search) function.
bool dfs(t_map *map, int **visited, int x, int y)
{
    if (x < 0 || y < 0 || x >= map->map_line_len[y] || y >= map->map_height)
        return (false);

    if (visited[y][x] || map->map[y][x] == '1')
        return true;

    if (x == 0 || y == 0 || x == map->map_line_len[y] - 1 || y == map->map_height - 1)
        return (false);

    visited[y][x] = 1; // mark it as visited

    bool up = dfs(map, visited, x, y - 1);
    bool down = dfs(map, visited, x, y + 1);
    bool left = dfs(map, visited, x - 1, y);
    bool right = dfs(map, visited, x + 1, y);

    return (up && down && left && right);
}

/// @brief claculate the lenght of an array of strings.
/// @param array the array to calculate its lenght.
/// @return the lenght of the array.
int arr_len(char **array)
{
    int i;

    i = -1;
    if (!array)
        return (0);
    while(array[++i])
        ;
    return (i);
}

/// @brief checks for white-space characters.  In the "C" and "POSIX" locales, these are: space, form-feed ('\f'), newline  ('\n'),  carriage  return  ('\r'), horizontal tab ('\t'), and vertical tab ('\v').
/// @param c the character that we want to check if it is a white-space.
/// @return return 1 if the character is an white-space.
int ft_isspace(int c)
{
    if (ft_strchr("\n\f\t\v\t ", c))
        return (1);
    return (0);
}

/// @brief print string in stderr.
/// @param error_str string to be printed.
/// @param file which file the error is.
/// @param line which line the error is.
void print_error (char *error_str, char *file, int line)
{
    ft_putstr_fd("\n", 2);
    ft_putstr_fd(error_str, 2);
    ft_putstr_fd("File: ------> ", 2);
    ft_putstr_fd(file, 2);
    ft_putstr_fd(":", 2);
    // ft_putstr_fd("\n", 2);
    // ft_putstr_fd("Line: ------> ", 2);
    ft_putnbr_fd(line, 2);
    ft_putstr_fd("\n\n", 2);
}

/// @brief check the map file extension (.cub).
/// @param file_path the file path.
/// @return 0 if the extension not valid otherwise 1.
int check_extension(const char *file_path, const char *extension)
{
    int fd;

    if (!file_path || !extension)
        return (0);

    printf("%s\n", file_path);
    if ((fd = open(file_path, O_RDONLY)) == -1)
    {
        print_error("Error: File does not exist!\n", __FILE__, __LINE__);
        return (0);
    }
    else
        close(fd);

    int extension_len = ft_strlen(extension);

    if (!ft_strnstr(&file_path[ft_strlen(file_path) - extension_len], extension, extension_len))
    {
        print_error("Error, bad file extension [example.cub]!\n", __FILE__, __LINE__);
		return (0);
    }
    return (1);
}

/// @brief chech is a line empty or not.
/// @param line the line.
/// @return true if the line empty otherwise false.
bool is_empty_line(const char *line)
{
    int i;

    i = -1;
    if(!line)
        return (true);

    while(line[++i] && ft_isspace(line[i]))
        ;
    // if (!line[i])
    //     return (true);
    return (!line[i]);
}

/// @brief check the color format (0,0,0).
/// @return true if the format is correct.
int check_color_format(const char *str_color)
{
    if (!str_color || !ft_isdigit(str_color[0]) || !ft_isdigit(str_color[ft_strlen(str_color) - 1]))
        return (0);
    return (1);
}

/// @brief 
/// @param arr 
void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr && arr[++i])
		free(arr[i]);
	free(arr);
}

/// @brief Takes a string color (255,255,0) and convert it to inteager.
/// @param str_color string color to be converted to inteager.
/// @return inteager color
// int str_to_color(const char *str_color)
int64_t parse_color(const char *str_color)
{
    int64_t color;
    char    **colors;

    color = -1;
    if (!check_color_format(str_color))
        return (color);

    colors = ft_split(str_color, ',');
    if (!colors || arr_len(colors) != 3)
    {
        free_array(colors);
        return (-1);
    }
        
    int r = ft_atoi(colors[0]);
    int g = ft_atoi(colors[1]);
    int b = ft_atoi(colors[2]);
    
    free_array(colors);

    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (-1);

    // color = (r << 16) + (g << 8) + b;
    // return ((r << 16) | (g << 8) | b);
    color = (r << 16) | (g << 8) | b;
    return (color);
}

/// @brief count, allocate and copy the map. 
/// @param map_path map file path.
/// @param height a pointer to the lenght of the map.
/// @return the allocated map.
char **read_map_lines(const char *map_path, int *height)
{
    int fd;
    char *line;

    fd = open(map_path, O_RDONLY);
    if (fd == -1)
        return (print_error("Error: failed to open map file!\n", __FILE__, __LINE__), NULL);

    *height = 0;
    line = get_next_line(fd);
    while(line)
    {
        (*height)++;
        free(line);
        line = get_next_line(fd);
    }
    if (*height == 0)
        return (print_error("Error: map file is empty!\n", __FILE__, __LINE__), close(fd), NULL);

    close(fd);
    fd = open(map_path, O_RDONLY);
    if (fd == -1)
        return (print_error("Error: failed to open map file!\n", __FILE__, __LINE__), NULL);

    char **lines = malloc(sizeof(char *) * (*height + 1));
    if (!lines)
        return (print_error("Error: failed to allocated memory for map!\n", __FILE__, __LINE__), close(fd), NULL);

    int i = -1;
    while(++i < *height)
    {
        lines[i] = get_next_line(fd);
        if (!lines[i])
        {
            while(--i >= 0)
                free(lines[i]);
            free(lines);
            return (print_error("Error: failed to get next line!\n", __FILE__, __LINE__), close(fd), NULL);
        }
    }

    lines[*height] = NULL;
    close(fd);
    return (lines);
}

t_image *load_texture(void *mlx, char *filename)
{
    if (!mlx || !filename)
        return (NULL);

    t_image *texture = malloc(sizeof(t_image));
    if (!texture)
        return (NULL);

    texture->img_ptr = mlx_xpm_file_to_image(mlx, filename, &texture->width, &texture->height);
    if (!texture->img_ptr)
    {
        free(texture);
        return (NULL);
    }
    texture->img_data = mlx_get_data_addr(texture->img_ptr, &texture->bits_per_pixel, &texture->size_line, &texture->endian);
    return texture;
}

/// @brief 
/// @param texture_path 
/// @return 
char *parse_texture(char *texture_path)
{
    if (!check_extension(texture_path, ".xpm"))
        return (NULL);
    return (texture_path);
}

/// @brief parse map metadata (01NSEW).
/// @param data a data structure that has all the nessecery variables.
/// @param map_lines 
/// @param map_heigh 
/// @param current_line 
/// @return 
bool parse_metadata(t_data *data, char **map_lines, int map_heigh, int *current_line)
{
    int textures_found = 0;
    int colors_found = 0;

    while(*current_line < map_heigh && (textures_found < 4 || colors_found < 2))
    {
        if (is_empty_line(map_lines[*current_line]))
        {
            (*current_line)++;
            continue;
        }
        
        char *trimmed = ft_strtrim(map_lines[*current_line], "\n");
        char **parts = ft_split(trimmed, ' ');
        if (!parts || arr_len(parts) != 2)
        {
            free(trimmed);
            free_array(parts);
            while(--textures_found >= 0)
            {
                mlx_destroy_image(data->mlx_ptr, data->textures[textures_found]->img_ptr);
                free(data->textures[textures_found]);
            }
            print_error("Error: bad texture or color arguments!\n", __FILE__, __LINE__);
            return (false);
        }

        if (textures_found < 4)
        {
            char **texture_ptr = NULL;
            
            if (!ft_strcmp("NO", parts[0]))
                texture_ptr = &data->no_texture_path;// = ft_strdup(parts[1]);
            else if (!ft_strcmp("SO", parts[0]))
                texture_ptr = &data->so_texture_path;// = ft_strdup(parts[1]);
            else if (!ft_strcmp("WE", parts[0]))
                texture_ptr = &data->we_texture_path;// = ft_strdup(parts[1]);
            else if (!ft_strcmp("EA", parts[0]))
                texture_ptr = &data->ea_texture_path;// = ft_strdup(parts[1]);

            if (texture_ptr)
            {
                *texture_ptr = parse_texture(parts[1]);//ft_strdup(parts[1]);
                if (!*texture_ptr)
                {
                    free(trimmed);
                    free_array(parts);
                    return (0);
                }
                data->textures[textures_found] = load_texture(data->mlx_ptr, *texture_ptr);
                if (!data->textures[textures_found])
                {
                    free(trimmed);
                    free_array(parts);
                    while(--textures_found >= 0)
                    {
                        mlx_destroy_image(data->mlx_ptr, data->textures[textures_found]->img_ptr);
                        free(data->textures[textures_found]);
                    }
                    return (false);
                }
                textures_found++;
            }
        }
        
        else if (colors_found < 2)
        {
            int *color_ptr = NULL;
            
            if (!ft_strcmp("F", parts[0]))
                color_ptr = &data->map_.floor_color;
            else if (!ft_strcmp("C", parts[0]))
                color_ptr = &data->map_.ceiling_color;
            
            else
            {
                print_error("Error: bad texture or color arguments!\n", __FILE__, __LINE__);
                printf(BRED"%d: %s\n"COLOR_RESET, *current_line, trimmed);
                while(--textures_found >= 0)
                {
                    mlx_destroy_image(data->mlx_ptr, data->textures[textures_found]->img_ptr);
                    free(data->textures[textures_found]);
                }
                free(trimmed);
                free_array(parts);
                return (0);
            }

            if (color_ptr)
            {
                *color_ptr = parse_color(parts[1]);
                if (*color_ptr == -1)
                {
                    print_error("Error: bad color!\n", __FILE__, __LINE__);
                    printf(BRED"%d: %s\n"COLOR_RESET, *current_line, trimmed);
                    while(--textures_found >= 0)
                    {
                        mlx_destroy_image(data->mlx_ptr, data->textures[textures_found]->img_ptr);
                        free(data->textures[textures_found]);
                    }
                    free(trimmed);
                    free_array(parts);
                    return (0);
                }
                colors_found++;
            }
        }
        
        free(trimmed);
        free_array(parts);
        (*current_line)++;
    }

    return (textures_found == 4 && colors_found == 2);
}

/// @brief 
/// @param data 
/// @return 
bool validate_map(t_data *data)
{
    int i = -1;
    bool is_player_found = false;

    while (++i < data->map_.map_height)
    {
        data->map_.map_line_len[i] = ft_strlen(data->map_.map[i]);
        if (i + 1 < data->map_.map_height)
            data->map_.map_line_len[i] -= 1;
        
        int j = -1;
        while (++j < data->map_.map_line_len[i])
        {
            if (!ft_strchr(SUPPORTED_CHARS, data->map_.map[i][j]))
            {
                print_error("Error: unsupported metadata (characters)!\n", __FILE__, __LINE__);
                return (false);
            }
            
            if (ft_strchr(PLAYER_DIR, data->map_.map[i][j]))
            {
                if (is_player_found)
                {
                    print_error("Error: multiple players!\n", __FILE__, __LINE__);
                    return (false);
                }
                data->player_x = j + 0.5; // in the center of the tile.
                data->player_y = i + 0.5; // in the center of the tile.
                data->player_dir = data->map_.map[i][j];
                is_player_found = true;
                data->map_.map[i][j] = '0';
            }
        }
    }
    if (!is_player_found)
        print_error("Error: no player found!\n", __FILE__, __LINE__);
    return (is_player_found);
}

void print_map(t_map *map)
{
    // char **map = map->map;
    int i = -1;
    while(++i < map->map_height)
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

void print_str(char *str, int index)
{
    int i = -1;
    while(++i < index)
        printf(" ");
    printf("%s", str);
}

void ft_panic(int line_num, int col_num, const char *line, void (*clean_func)(t_data *), void *data) {
    printf("%d:%d: %s", line_num, col_num, line);
    
    if (clean_func)
        clean_func(data);
    exit(EXIT_FAILURE);
    // print_str("▲", col_num);
}

void clean_up(t_data *data)
{
	if (data->map_.map_line_len)
		free(data->map_.map_line_len);
		
	// if (data->no_texture_path)
	// 	free(data->no_texture_path);
	// if (data->so_texture_path)
	// 	free(data->so_texture_path);
	// if (data->we_texture_path)
	// 	free(data->we_texture_path);
	// if (data->ea_texture_path)
	// 	free(data->ea_texture_path);
	
	// if (data->image)
	// 	mlx_destroy_image(data->mlx_ptr, data->image);

	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	
	#ifdef __linux__
	
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);

	# endif

	// if (data->map)
	// 	free_array(data->map);
	
	if (data->mlx_ptr)
		free(data->mlx_ptr);
}

/// @brief check the first line and the last one if all ones
/// @param data 
/// @param map 
/// @param map_start 
/// @param map_height 
/// @return 
int check_first_last(t_data *data, char **map, int map_start, int map_height)
{
    int j = -1;
    int line = 0;
    while (map[line][++j] && ft_strchr("1 ", map[line][j]));
    if (map[line][j] != '\n')
    {
        print_error("Error: invalid map border!\n", __FILE__, __LINE__);
        ft_panic(map_start + 1, j + 1, map[0], clean_up, data);
        return (0);
        // exit (100);
    }
    j = -1;
    line = map_height - 1;
    while (map[line][++j] && ft_strchr("1 ", map[line][j]));

    if (map[line][j] != '\n' && map[line][j] != '\0')
    {
        print_error("Error: invalid map border!\n", __FILE__, __LINE__);
        ft_panic(line + 1, j + 1, map[line], clean_up, data);       
        return (0); 
        // exit (100);
    }
    return (1);
}

/// @brief check if map is surounded by walls.
/// @param data 
/// @param map 
/// @param height 
/// @return true if map is surounded by walls.
int validate_map_borders(t_data *data, char **map, int height)
{
    int i = 0;
    int j = -1;

    if (!check_first_last(data, map, data->map_.map_start, data->map_.map_height))
        return (0);

    // start from the second line to the line befor the last.
    while (++i < height - 1)
    {
        if (is_empty_line(map[i]))
            continue;
        j = -1;
        while(++j < data->map_.map_line_len[i] && ft_isspace(map[i][j]))
            ;
        if (map[i][j] != '1' || map[i][data->map_.map_line_len[i] - 1] != '1')
        {
            print_error("Error: invalid map border!\n", __FILE__, __LINE__);
            ft_panic(i + data->map_.map_start + 1, j + 1, map[i], clean_up, data);            
            return (0);
        }
        
        while(j + 1 < data->map_.map_line_len[i])
        {
            if ((map[i][j] == '0' && map[i][j + 1] == ' ') || (map[i][j] == ' ' && map[i][j + 1] == '0'))
            {
                print_error("Error: invalid map border!\n", __FILE__, __LINE__);
                ft_panic(i + data->map_.map_start + 1, j + 1, map[i], clean_up, data);                
                return (0);
            }
            if ((i + 1 < height && map[i][j] == '0' && j < data->map_.map_line_len[i + 1] && map[i + 1][j] == ' ') || (map[i][j] == ' ' && i + 1 < height && map[i + 1][j] == '0'))
            {
                print_error("Error: invalid map border!\n", __FILE__, __LINE__);
                ft_panic(i + data->map_.map_start + 1, j + 1, map[i], clean_up, data);                
                return (0);
            }
            j++;
        }
    }

    
    int **visited = malloc(sizeof(int *) * data->map_.map_height);
    if (!visited)
        exit (1); // changes
    
    i = -1;
    while (++i < data->map_.map_height)
    {
        visited[i] = ft_calloc(data->map_.map_line_len[i], sizeof(int));
        if (!visited[i])
            exit (1);
    }

    if (!dfs(&data->map_, visited, data->player_x, data->player_y))
    {
        print_error("Error: map is not surrounded by walls!\n", __FILE__, __LINE__);
        exit (1);
    }

    i = -1;
    while(++i < data->map_.map_height)
        free(visited[i]);
    free(visited);

    return (1);
}

/// @brief 
/// @param data 
/// @param ac 
/// @param av 
/// @return 
int parse_map(t_data *data, int ac, char **av)
{
    if (ac != 2)
    {
        print_error("Error: bad arguments!\n", __FILE__, __LINE__);
        printf("Usage: ./cub3d <map_path>\n");
        return (0);
    }

    if (!check_extension(av[1], ".cub"))
        return (0);

    int height = 0;
    char **lines = read_map_lines(av[1], &height);
    if (!lines)
        return (0);
    
    int current_line = 0;
    if (!parse_metadata(data, lines, height, &current_line))
    {
        free_array(lines);
        return (0);
    }
    
    while(current_line < height && is_empty_line(lines[current_line]))
        current_line++;
    
    // data->map_start = current_line;
    // data->map_height = height - current_line;
    // data->map = &lines[current_line];
    
    data->map_.map_start = current_line;
    data->map_.map_height = height - current_line;
    data->map_.map = &lines[current_line];
    data->map_.map_width = ft_strlen(data->map_.map[0]);

    data->map_.map_line_len = malloc(sizeof(int) * data->map_.map_height);
    if (!data->map_.map_line_len)
    {
        free_array(lines);
        return (0);
    }

    if (!validate_map(data))
    {
        // free(data->map_line_len);
        free_array(lines);
        return (0);
    }

    if (!validate_map_borders(data, data->map_.map, data->map_.map_height))
    {
        free_array(lines);
        return (0);
    }

    // data->map_.map = data->map;
    // data->map_.map_height = data->map_height;
    // data->map_.ceiling_color = data->ceiling_color;
    // data->map_.floor_color = data->floor_color;
    // data->map_.no_texture_path = data->no_texture_path;
    // data->map_.so_texture_path = data->so_texture_path;
    // data->map_.ea_texture_path = data->ea_texture_path;
    // data->map_.we_texture_path = data->we_texture_path;

    // print_map(&data->map_);

    return (1);
}
