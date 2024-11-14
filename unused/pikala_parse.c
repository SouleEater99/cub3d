/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pikala_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:57:39 by aelkheta          #+#    #+#             */
/*   Updated: 2024/10/26 18:48:13 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cub3d.h>
void print_file_cont(char *map_path)
{
    int fd = open(map_path, O_RDONLY);
    if (fd == -1) {
        printf("FILE: %s, LINE: %d\n", __FILE__, __LINE__);
        perror(map_path);
        return;
    }

    char *line = get_next_line(fd);
    while (line)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    printf("\n");
    close(fd);
}

int map_height(char *map_path)
{
    int i;
    int fd;
    char *line;
    
    i = 0;
    fd = open(map_path, O_RDONLY);
    if (fd == -1) {
        printf("FILE: %s, LINE: %d\n", __FILE__, __LINE__);
        perror(map_path);
        return -1;
    }

    line = get_next_line(fd);
    while(line)
    {
        ++i;    
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return i;
}

void print_map(char **map)
{
    if (!map)
        return;
    while(*map)
        printf("%s", *map++);
    printf("\n");
}

int read_map(t_data *data, char *map_path)
{
    if (!data || !map_path)
        return 1;
        
    int i;
    int fd;
    int map_h;
    
    fd = open(map_path, O_RDONLY);
    if (fd == -1) {
        printf("FILE: %s, LINE: %d\n", __FILE__, __LINE__);
        perror(map_path);
        return 1;
    }
    
    map_h = map_height(map_path);
    if (map_h <= 0)
        return 1;
        
    data->map = (char **)malloc(sizeof(char *) * (map_h + 1));
    if (!data->map) {
        close(fd);
        return 1;
    }
    
    for (i = 0; i < map_h; i++) {
        data->map[i] = get_next_line(fd);
        if (!data->map[i]) {
            while (--i >= 0)
                free(data->map[i]);
            free(data->map);
            close(fd);
            return 1;
        }
    }
    data->map[map_h] = NULL;
    
    data->map_height = map_h;
    if (data->map[0])
        data->map_width = ft_strlen(data->map[0]);
    else {
        free_array(data->map);
        close(fd);
        return 1;
    }
    
    close(fd);
    return 0;
}

int ft_isspace(int c)
{
    return (ft_strchr("\f\n\r\t\v ", c) != NULL);
}

bool is_empty_line(const char *line)
{
    if (!line)
        return true;
        
    while (*line && ft_isspace(*line))
        line++;
    return (*line == '\0');
}

int init_payer_pos(t_data *data, char **map)
{
    if (!data || !map)
        return 1;

    int x, y;
    bool found_player = false;

    y = data->map_start - 1;
    while(map[++y])
    {
        if (is_empty_line(map[y]))
            continue;
            
        x = -1;
        while(map[y][++x])
        {
            if (!ft_strchr("NSEW01 \t\n", map[y][x])) {
                fprintf(stderr, "Error: map not valid: unsupported character at [%d][%d]:[%c]\n", 
                    y, x, map[y][x]);
                return 1;
            }
            if (ft_strchr("NSEW", map[y][x])) {
                if (found_player) {
                    fprintf(stderr, "Error: multiple players found in map\n");
                    return 1;
                }
                data->player_dir = map[y][x];
                data->map[y][x] = '0';
                data->player_x = x;
                data->player_y = y;
                found_player = true;
            }
        }
    }
    
    if (!found_player) {
        fprintf(stderr, "Error: no player found in map\n");
        return 1;
    }
    
    return 0;
}

int check_map_borders(char **map, int height, int width, int map_start)
{
    if (!map || height <= map_start || width <= 0)
        return 1;

    // Check first line
    for (int i = 0; map[map_start][i] && map[map_start][i] != '\n'; i++)
        if (!ft_strchr("1 ", map[map_start][i])) {
            fprintf(stderr, "Error: invalid first line border at position %d\n", i);
            return 1;
        }

    // Check last line
    for (int i = 0; map[height - 1][i] && map[height - 1][i] != '\n'; i++)
        if (!ft_strchr("1 ", map[height - 1][i])) {
            fprintf(stderr, "Error: invalid last line border at position %d\n", i);
            return 1;
        }

    // Check side borders
    for (int i = map_start + 1; i < height - 1; i++) {
        int j = 0;
        // Skip leading spaces
        while (map[i][j] && map[i][j] == ' ')
            j++;
            
        // Check first non-space character
        if (!map[i][j] || map[i][j] != '1') {
            fprintf(stderr, "Error: invalid left border at line %d\n", i);
            return 1;
        }
        
        // Find last non-space character before newline
        int last = ft_strlen(map[i]) - 2;  // -2 to account for newline
        while (last >= 0 && map[i][last] == ' ')
            last--;
            
        if (last < 0 || map[i][last] != '1') {
            fprintf(stderr, "Error: invalid right border at line %d\n", i);
            return 1;
        }
    }

    return 0;
}

int arr_len(char **array)
{
    int i = -1;
    while(array && array[++i])
        ;
    return (i);
}

int str_to_color(const char *str_color)
{
    if (!str_color)
        return -1;
        
    char **colors = ft_split(str_color, ',');
    if (!colors)
        return -1;
        
    int count = arr_len(colors);
    if (count != 3) {
        free_array(colors);
        return -1;
    }
    
    int r = ft_atoi(colors[0]);
    int g = ft_atoi(colors[1]);
    int b = ft_atoi(colors[2]);
    
    free_array(colors);
    
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return -1;
        
    return (r << 16) | (g << 8) | b;
}

int load_floor_sky_colors(t_data *data, char **map)
{
    if (!data || !map)
        return 1;

    int colors_found = 0;
    int i = data->map_start - 1;
    
    while (map[++i] && colors_found < 2)
    {
        if (is_empty_line(map[i]))
            continue;

        char *map_line = ft_strtrim(map[i], "\n");
        if (!map_line)
            return 1;
            
        char **splited = ft_split(map_line, ' ');
        if (!splited || arr_len(splited) != 2) {
            free(map_line);
            free_array(splited);
            return 1;
        }

        int color = str_to_color(splited[1]);
        if (color == -1) {
            free(map_line);
            free_array(splited);
            return 1;
        }

        if (!ft_strcmp("F", splited[0])) {
            data->floor_color = color;
            colors_found++;
        }
        else if (!ft_strcmp("C", splited[0])) {
            data->ceiling_color = color;
            colors_found++;
        }
        
        free(map_line);
        free_array(splited);
    }
    
    data->map_start = i;
    return (colors_found != 2);
}

int load_textures(t_data *data, char **map)
{
    if (!data || !map)
        return 1;

    int textures_found = 0;
    int i = -1;

    while(map[++i] && textures_found < 4)
    {
        if (is_empty_line(map[i]))
            continue;

        char *map_line = ft_strtrim(map[i], "\n");
        if (!map_line)
            return 1;
            
        char **splited = ft_split(map_line, ' ');
        if (!splited || arr_len(splited) != 2) {
            free(map_line);
            free_array(splited);
            return 1;
        }

        char *texture_path = ft_strdup(splited[1]);
        if (!texture_path) {
            free(map_line);
            free_array(splited);
            return 1;
        }

        if (!ft_strcmp("NO", splited[0])) {
            free(data->no_texture_path);
            data->no_texture_path = texture_path;
            textures_found++;
        }
        else if (!ft_strcmp("SO", splited[0])) {
            free(data->so_texture_path);
            data->so_texture_path = texture_path;
            textures_found++;
        }
        else if (!ft_strcmp("WE", splited[0])) {
            free(data->we_texture_path);
            data->we_texture_path = texture_path;
            textures_found++;
        }
        else if (!ft_strcmp("EA", splited[0])) {
            free(data->ea_texture_path);
            data->ea_texture_path = texture_path;
            textures_found++;
        }
        else {
            free(texture_path);
        }
        
        free(map_line);
        free_array(splited);
    }
    
    data->map_start = i;
    return (textures_found != 4);
}

int parse_map(t_data *data, int ac, char **av)
{
    if (ac != 2) {
        write(2, "Error: missing map argument\n", 27);
        return 1;
    }
    
    if (!av[1] || !ft_strnstr(&av[1][ft_strlen(av[1]) - 4], ".cub", 4)) {
        write(2, "Error: invalid map file extension\n", 32);
        return 1;
    }
    
    if (read_map(data, av[1]))
        return 1;
    
    if (load_textures(data, data->map))
        return 1;

    if (load_floor_sky_colors(data, data->map))
        return 1;
        
    if (check_map_borders(data->map, data->map_height, data->map_width, data->map_start))
        return 1;
        
    if (init_payer_pos(data, data->map))
        return 1;

    return 0;
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
