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

// void print_file_cont(char *map_path)
// {
//     int fd = open(map_path, O_RDONLY);
//         return (printf("FILE: %s, LINE: %d\n", __FILE__, __LINE__), perror(map_path));

//     char *line = get_next_line(fd);
//     while (line)
//     {
//         printf("%s", line);
//         free(line);
//         line = get_next_line(fd);
//     }
//     printf("\n");
//     close(fd);
// }

// int map_height(char *map_path)
// {
//     int i;
//     int fd;
//     char *line;
    
//     i = 0;
//     fd = open(map_path, O_RDONLY);
//     if (fd == -1)
//         return (printf("FILE: %s, LINE: %d\n", __FILE__, __LINE__), perror(map_path), -1);

//     line = get_next_line(fd);
//     while(line)
//     {
//         ++i;    
//         free(line);
//         line = get_next_line(fd);
//     }
//     close(fd);
//     return (i);
// }

// void print_map(char **map)
// {
//     while(map && *map)
//         printf("%s", *map++);
//     printf("\n");
// }

// int init_payer_pos(t_data *data, char **map)
// {
//     (void)map;
//     // int x, y;

//     // // y = data->map_start;
//     // y = -1;
//     // while(map && map[++y])
//     // {
//     //     x = -1;
//     //     // printf("%s", map[y]);
//     //     if (is_empty_line(map[y]))
//     //         continue;
//     //     while(map[y] && map[y][++x])
//     //     {
//     //         if (!ft_strchr("NSEW01\t\n ", map[y][x]))
//     //         {
//     //             fprintf(stderr, "Error: map not valid: not supported characters: [%d][%d]:[%c]\n", y, x, map[y][x]);
//     //             exit(1);
//     //         }
//     //         if (strchr("NSEW", map[y][x]))
//     //         {
//     //             data->player_dir = map[y][x];
//     //             data->map[y][x] = '0';
//     //             data->player_x = x;
//     //             data->player_y = y;
//     //             printf("player at: [%lf][%lf] = [%c]\n", data->player_y, data->player_x, data->map[(int)data->player_y][(int)data->player_x]);
//     //         }
//     //     }
//     // }

//     data->player_x = 2.0;
//     data->player_y = 2.0;

//     return (0);
// }

// int check_map_borders(char **map, int height, int width, int map_start)
// {
//     (void)width;

//     int i = -1;
//     // int j = -1;
//     printf("\n======= %s =========\n", map[map_start]);
    
//     // check the first line in the map
//     while(map && map[map_start][++i])
//         if (!ft_strchr("1\n ", map[map_start][i]))
//             return(printf("\n💩Error File: %s Line: %d [%c]\n", __FILE__, __LINE__, map[map_start][i]), exit(1), 1);
    
//     // check the last line in the map
//     i = -1;
//     while(map && map[height - 1][++i])
//         if (!ft_strchr("1\n ", map[height - 1][i]))
//             return(printf("\n💩Error File: %s Line: %d [%c]\n", __FILE__, __LINE__, map[height - 1][i]), exit(1), 1);
    
//     // check the left and right borders
//     i = map_start;
//     while (map && map[++i + 1])
//     {
//         int j = 0;
//         while (map[i][j] && map[i][j] == ' ')
//             j++;
            
//         // printf("[%d]\n", map[i][ft_strlen(map[i]) - 2]);
//         if (map[i][j] && (map[i][j] != '1' || map[i][ft_strlen(map[i]) - 2] != '1'))// || map[i][ft_strlen(map[i] - 2)] != '1'))
//             return(printf("\n💩Error File: %s Line: %d [%c]\n", __FILE__, __LINE__, map[height - 1][i]), exit(1), 1);
//     }

//     printf("VALID MAP: ✅\n");
//     return (0);
// }

// int looad_floor_sky_colors(t_data *data, char **map)
// {
//     int flag = 0;
//     int i = data->map_start - 1;
    
//     while (map && map[++i] && flag != 2)
//     {
//         if (is_empty_line(map[i]))
//             continue;

//         char *map_line = ft_strtrim(map[i], "\n");
//         printf("\n ====== %s =======\n", map_line);
//         char **splited = ft_split(map_line, ' ');
//         if (!splited || arr_len(splited) < 2)
//             return (printf("Error: invalid colors\n"), free(map_line), free_array(splited), exit(1), 1);

//         if (!ft_strcmp("F", splited[0]))
//             data->floor_color = str_to_color(splited[1]);
//         else if (!ft_strcmp("C", splited[0]))
//             data->ceiling_color = str_to_color(splited[1]);
//         flag++;
//     }
//     data->map_start = i;
//     return (0);
// }

// int looad_textures(t_data *data, char **map)
// {
//     int i = -1;
//     int flag = 0;

//     while(map && map[++i] && flag != 4)
//     {
//         if (is_empty_line(map[i]))
//             continue;

//         char *map_line = ft_strtrim(map[i], "\n");
//         char **splited = ft_split(map_line, ' ');
        
//         printf("map line: %s\n", map_line);
//         if (!splited || arr_len(splited) < 2)
//             return (printf("Error, invalid texture path.\n"), free(map_line), free_array(splited), exit (1), 1);

//         if (!ft_strcmp("NO", splited[0]))
//             data->no_texture_path = ft_strdup(splited[1]);
//         else if (!ft_strcmp("SO", splited[0]))
//             data->so_texture_path = ft_strdup(splited[1]);
//         else if (!ft_strcmp("WE", splited[0]))
//             data->we_texture_path = ft_strdup(splited[1]);
//         else if (!ft_strcmp("EA", splited[0]))
//             data->ea_texture_path = ft_strdup(splited[1]);
//         free_array(splited);
//         free(map_line);
//         flag++;
//     }
//     data->map_start = i;
//     return (0);
// }

/// @brief claculate the lenght of an array of strings.
/// @param array 
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

// int parse_map(t_data *data, int ac, char **av)
// {
//     (void)data;

//     if (ac != 2)
//     {
//         print_error("Error: Bad arguments!\n", __FILE__, __LINE__);
//         printf("Usage: <./cub3d> <Path to the map>.\n");
//         return (0);
//     }
//     if (!check_map_extension(av[1]))
//         return (0);

//     if (!read_map(data, av[1]))
//         return (0);

//     return (1);
// }

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
        // printf("%d %d\n", i, *height);
        // printf("%s\n", lines[i]);
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

bool parse_metadata(t_data *data, char **map_lines, int map_heigh, int *current_line)
{
    // int current_line = -1;
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

bool validate_map(t_data *data)
{
    int i = -1;
    bool is_player_found = false;

    while (++i < data->map_height)
    {
        data->map_line_len[i] = ft_strlen(data->map[i]);
        if (i - 1 < data->map_height)
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
                data->player_x = j + 0.5;
                data->player_y = i + 0.5;
                data->player_dir = data->map[i][j];
                data->map[i][j] = '0';
                is_player_found = true;
            }
        }
    }
    return (is_player_found);
}

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

    if (!validate_map(data)) //current_line
    {
        free(data->map_line_len);
        free_array(lines);
        return (0);
    }

    return (1);
}

// int check_line_components(char *line, char *chars)
// {
//     int i;

//     i = -1;
//     if (!line || !chars)
//         return (0);
//     while (line[++i])
//     {
//         if (!ft_strchr(chars, line[i]))
//         {
//             printf("\n\n%s\n", line);
//             return (0);
//         }
//     }
//     return (1);
// }

// int read_map(t_data *data, char *map_path)
// {
//     int     i;
//     int     fd;
//     char    *line;
//     char    **lines;

//     // ====================================== //

//     fd = open(map_path, O_RDONLY);
//     if (fd == -1)
//         return (perror(map_path), print_error("\nError: opening file!", __FILE__, __LINE__), 0);
    
//     line = get_next_line(fd);
//     if (!line)
//         return (print_error("Error: map file is empty!\n", __FILE__, __LINE__), close(fd), 0);

//     i = 0;
//     data->map_width = ft_strlen(line) - 1; // should be removed.
//     while (line)
//     {
//         // printf("%s", line); // for debuging.
//         free(line);
//         line = get_next_line(fd);
//         ++i;
//     }
//     data->map_height = i;
//     close(fd);

//     // ====================================== //

//     fd = open(map_path, O_RDONLY);
//     if (fd == -1)
//         return (0);
    
//     lines = (char **)malloc(sizeof(char *) * (data->map_height + 1));
//     if (!lines)
//         return (perror("malloc"), close(fd), 0);
    
//     data->map_line_len = (int *)malloc(sizeof(int) * data->map_height);
//     if (!data->map_line_len)
//         return (perror("malloc"), close(fd), 0);

//     i = -1;
//     while(++i < data->map_height)
//     {
//         lines[i] = get_next_line(fd);
//         if (!lines[i])
//         {
//             while (--i >= 0)
//                 free(lines[i]);
//             free(lines);
//             close(fd);
//             return (print_error("Error: fail to get the next line!\n", __FILE__, __LINE__), 0);
//         }
//     }
//     lines[i] = NULL;
//     close(fd); // to be deleted.

//     // ====================================== //

//     printf("\n\n");

//     i = -1;
//     int flag = 0;
//     while(++i < data->map_height && flag != 4)
//     {
//         printf("%s\n", data->map[i]);
//         if (is_empty_line(lines[i]))
//             continue;

//         printf("%s", lines[i]);

//         char *map_line = ft_strtrim(lines[i], "\n");
//         char **splited = ft_split(map_line, ' ');
        
//         if (!splited || arr_len(splited) < 2)
//             return (print_error("Error, invalid texture path.\n", __FILE__, __LINE__), free(map_line), free_array(splited), 0);

//         if (!ft_strcmp("NO", splited[0]))
//             data->no_texture_path = ft_strdup(splited[1]);
//         else if (!ft_strcmp("SO", splited[0]))
//             data->so_texture_path = ft_strdup(splited[1]);
//         else if (!ft_strcmp("WE", splited[0]))
//             data->we_texture_path = ft_strdup(splited[1]);
//         else if (!ft_strcmp("EA", splited[0]))
//             data->ea_texture_path = ft_strdup(splited[1]);
//         free_array(splited);
//         free(map_line);
//         flag++;
//     }
//     data->map_start = i;

//     // ====================================== //

//     flag = 0;
//     i = data->map_start - 1;
    
//     while (++i < data->map_height && flag != 2)
//     {
//         if (is_empty_line(data->map[i]))
//             continue;

//         char *map_line = ft_strtrim(data->map[i], "\n");
//         printf("\n ====== %s =======\n", map_line);
//         char **splited = ft_split(map_line, ' ');
//         if (!splited || arr_len(splited) < 2)
//             return (printf("Error: invalid colors\n"), free(map_line), free_array(splited), exit(1), 1);

//         if (!ft_strcmp("F", splited[0]))
//             data->floor_color = str_to_color(splited[1]);
//         else if (!ft_strcmp("C", splited[0]))
//             data->ceiling_color = str_to_color(splited[1]);

//         free_array(splited);
//         free(map_line);
//         flag++;
//     }

//     while (i < data->map_height && is_empty_line(lines[i]))
//         i++;

//     data->map_start = i;
//     data->map_height -= i;

//     while (--i >= 0)
//         free(lines[i]);
    
//     data->map = &lines[i];

//     printf("map start: %d\n", data->map_start);

//     // ====================================== //
    

//     i = data->map_start - 1;
//     while (++i < data->map_height)
//     {
//         // data->map[i] = get_next_line(fd);

//         data->map_line_len[i] = ft_strlen(data->map[i]) - 1;
//         if (i == data->map_height - 1)
//             data->map_line_len[i] = ft_strlen(data->map[i]);

//         if (!check_line_components(data->map[i], SUPPORTED_CHARS)) // PLAYER_DIR
// 	    {
//             data->map[++i] = NULL;
//             free_map(data->map);
//             free(data->map_line_len);
//             return (print_error("Error: unsupported character!\n", __FILE__, __LINE__), close(fd), 0);
//         }

//         // if (!data->map[i])
//         // {
//             // free_map(data->map);
//             // free(data->map_line_len);
//             // return (print_error("Error: fail to get the next line!\n", __FILE__, __LINE__), close(fd), 0);
//         // }
//     }
    
//     // ====================================== //

//     i = -1;
//     while(++i < data->map_height)
//     {
//         int j = -1;
//         while(++j < data->map_line_len[i])
//         {
//             if (ft_strchr(PLAYER_DIR, data->map[i][j]))
//             {
//                 if (!data->player_dir)
//                 {
//                     data->player_x = (double)j + 1; // to be fixed.
//                     data->player_y = (double)i + 1; // to be fixed.
//                     data->player_dir = data->map[i][j];
//                     data->map[i][j] = '0';
//                 }
//                 else
//                     return (print_error("Error: multiple players found!\n", __FILE__, __LINE__), close(fd), 0);
//             }
//         }
//     }

//     if (!data->player_dir)
//     {
//         // free_map(lines);
//         // free(data->map_line_len);
//         return (print_error("Error: no player found!\n", __FILE__, __LINE__), close(fd), 0);
//     }

//     // close(fd);
//     return (1);
// }

// void print_error (char *error_str, char *file, int line)
// {
//     ft_putstr_fd("\n", 2);
//     ft_putstr_fd(error_str, 2);
//     ft_putstr_fd("File: ------> ", 2);
//     ft_putstr_fd(file, 2);
//     ft_putstr_fd("\n", 2);
//     ft_putstr_fd("Line: ------> ", 2);
//     ft_putnbr_fd(line, 2);
//     ft_putstr_fd("\n\n", 2);
// }

// int check_map_extension(const char *map_path)
// {
//     int fd;

//     if ((fd = open(map_path, O_RDONLY)) == -1)
//     {
//         print_error("Error: File does not exist!\n", __FILE__, __LINE__);
//         return (0);
//     }
//     else
//         close(fd);

//     if (!ft_strnstr(&map_path[ft_strlen(map_path) - 4], ".cub", 4))
//     {
//         print_error("Error, map file extension!\n", __FILE__, __LINE__);
// 		return (0);
//     }
//     return (1);
// }

// int parse_map(t_data *data, int ac, char **av)
// {
//     (void)data;

//     if (ac != 2)
//     {
//         print_error("Error: Bad arguments!\n", __FILE__, __LINE__);
//         printf("Usage: <./cub3d> <Path to the map>.\n");
//         return (0);
//     }
//     if (!check_map_extension(av[1]))
//         return (0);

//     if (!read_map(data, av[1]))
//         return (0);

//     return (1);
// }

// int parse_map(t_data *data, int ac, char **av)
// {
//     (void) ac;
//     (void) av;
//     (void) data;

//     if (ac != 2)
//     {
//         write(2, "Error, there is no map specified.\n", 24);
//         return (1);
//     }
    
//     printf("map file is: %s\n", av[1]);
//     if (!ft_strnstr(&av[1][ft_strlen(av[1]) - 4], ".cub", 4))
//     {
//         write(2, "Error, map file extention\n", 27);
//         printf("==== Line: %d ====\n", __LINE__);
//         printf("==== File: %s ====\n", __FILE__);
// 		return (1);
//     }
    
//     if (read_map(data, av[1]))
//         return (1);
    
//     // if (looad_textures(data, data->map))
//     //     return (1);

//     // if (looad_floor_sky_colors(data, data->map))
//     //     return (1);
        
//     // if (check_map_borders(data->map, data->map_height, data->map_width, data->map_start))
//     //     return (1);
        
//     // if (init_payer_pos(data, data->map))
//     //     return (1);

//     return 0;
// }
