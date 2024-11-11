/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:57:39 by aelkheta          #+#    #+#             */
/*   Updated: 2024/10/26 18:49:12 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cub3d.h>

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
    ft_putstr_fd("\n", 2);
    ft_putstr_fd("Line: ------> ", 2);
    ft_putnbr_fd(line, 2);
    ft_putstr_fd("\n\n", 2);
}

/// @brief check the map file extension (.cub).
/// @param map_path the file path.
/// @return 0 if the extension not valid otherwise 1.
int check_map_extension(const char *map_path)
{
    int fd;

    if ((fd = open(map_path, O_RDONLY)) == -1)
    {
        print_error("Error: File does not exist!\n", __FILE__, __LINE__);
        return (0);
    }
    else
        close(fd);

    if (!ft_strnstr(&map_path[ft_strlen(map_path) - 4], ".cub", 4))
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

/// @brief Takes a string color and convert it to inteager.
/// @param str_color string color to be converted to inteager.
/// @return inteager color
// int str_to_color(const char *str_color)
int parse_color(const char *str_color)
{
    int color;
    char **colors;

    color = -1;
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

// # define and &&

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
                *texture_ptr = ft_strdup(parts[1]);
                textures_found++;
            }
        }
        
        else if (colors_found < 2)
        {
            int *color_ptr = NULL;
            
            if (!ft_strcmp("F", parts[0]))
                color_ptr = &data->floor_color;
            else if (!ft_strcmp("C", parts[0]))
                color_ptr = &data->ceiling_color;
            
            else
            {
                free(trimmed);
                free_array(parts);
                return (print_error("Error:  bad texture or color arguments!\n", __FILE__, __LINE__), 0);
            }

            if (color_ptr)
            {
                *color_ptr = parse_color(parts[1]);
                if (*color_ptr == -1)
                {
                    free(trimmed);
                    free_array(parts);
                    return (false);
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

    while (++i < data->map_height)
    {
        data->map_line_len[i] = ft_strlen(data->map[i]);
        if (i + 1 < data->map_height)
            data->map_line_len[i] -= 1;
        
        int j = -1;
        while (++j < data->map_line_len[i])
        {
            if (!ft_strchr(SUPPORTED_CHARS, data->map[i][j]))
            {
                print_error("Error: unsupported metadata (characters)!\n", __FILE__, __LINE__);
                return (false);
            }
            
            if (ft_strchr(PLAYER_DIR, data->map[i][j]))
            {
                if (is_player_found)
                {
                    print_error("Error: multiple players!\n", __FILE__, __LINE__);
                    return (false);
                }
                data->player_x = j + 0.5; // in the center of the tile.
                data->player_y = i + 0.5; // in the center of the tile.
                data->player_dir = data->map[i][j];
                is_player_found = true;
                data->map[i][j] = '0';
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

    if (!check_map_extension(av[1]))
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
    
    data->map_start = current_line;
    data->map_height = height - current_line;
    data->map = &lines[current_line];

    data->map_line_len = malloc(sizeof(int) * data->map_height);
    if (!data->map_line_len)
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

    data->map_.map = data->map;
    data->map_.map_height = data->map_height;
    data->map_.ceiling_color = data->ceiling_color;
    data->map_.floor_color = data->floor_color;
    data->map_.no_texture_path = data->no_texture_path;
    data->map_.so_texture_path = data->so_texture_path;
    data->map_.ea_texture_path = data->ea_texture_path;
    data->map_.we_texture_path = data->we_texture_path;

    print_map(&data->map_);

    return (1);
}
