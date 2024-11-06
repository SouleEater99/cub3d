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

# include <cub3d_bonus.h>

void print_file_cont(char *map_path)
{
    int fd = open(map_path, O_RDONLY);
        return (printf("FILE: %s, LINE: %d\n", __FILE__, __LINE__), perror(map_path));

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
    if (fd == -1)
        return (printf("FILE: %s, LINE: %d\n", __FILE__, __LINE__), perror(map_path), -1);

    line = get_next_line(fd);
    while(line)
    {
        ++i;    
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (i);
}

void print_map(char **map)
{
    while(map && *map)
        printf("%s", *map++);
    printf("\n");
}

int read_map(t_data *data, char *map_path)
{
    int     i;
    int     fd;
    char    *line;
    char    **lines;

    fd = open(map_path, O_RDONLY);
    if (fd == -1)
        return (printf("FILE: %s, LINE: %d\n", __FILE__, __LINE__), perror(map_path), 0);
    
    i = 0;
    line = get_next_line(fd);
    if (!line)
        return (close(fd), 0);
    
    data->map_width = ft_strlen(line) - 1;
    while (line)
    {
        ++i;
        printf("%s", line);  // For debug
        free(line);
        line = get_next_line(fd);
    }
    data->map_height = i;
    close(fd);

    fd = open(map_path, O_RDONLY);
    if (fd == -1)
        return (0);
    
    lines = (char **)malloc(sizeof(char *) * (data->map_height + 1));
    if (!lines)
        return (close(fd), 0);
    
    // Read and store each line
    i = 0;
    while (i < data->map_height)
    {
        lines[i] = get_next_line(fd);
        if (!lines[i])
        {
            while (--i >= 0)
                free(lines[i]);
            free(lines);
            return (close(fd), 0);
        }
        i++;
    }
    lines[i] = NULL;
    
    close(fd);
    data->map = lines;
    return (1);
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

bool is_empty_line(char *line)
{
    int i = -1;
    while(line && line[++i] && ft_isspace(line[i]));
    if (!line[i])
        return (true);
    return (false);
}

int init_payer_pos(t_data *data, char **map)
{
    (void)map;
    // int x, y;

    // // y = data->map_start;
    // y = -1;
    // while(map && map[++y])
    // {
    //     x = -1;
    //     // printf("%s", map[y]);
    //     if (is_empty_line(map[y]))
    //         continue;
    //     while(map[y] && map[y][++x])
    //     {
    //         if (!ft_strchr("NSEW01\t\n ", map[y][x]))
    //         {
    //             fprintf(stderr, "Error: map not valid: not supported characters: [%d][%d]:[%c]\n", y, x, map[y][x]);
    //             exit(1);
    //         }
    //         if (strchr("NSEW", map[y][x]))
    //         {
    //             data->player_dir = map[y][x];
    //             data->map[y][x] = '0';
    //             data->player_x = x;
    //             data->player_y = y;
    //             printf("player at: [%lf][%lf] = [%c]\n", data->player_y, data->player_x, data->map[(int)data->player_y][(int)data->player_x]);
    //         }
    //     }
    // }

    data->player_x = 2.0;
    data->player_y = 2.0;

    return (0);
}

int check_map_borders(char **map, int height, int width, int map_start)
{
    (void)width;

    int i = -1;
    // int j = -1;
    printf("\n======= %s =========\n", map[map_start]);
    
    // check the first line in the map
    while(map && map[map_start][++i])
        if (!ft_strchr("1\n ", map[map_start][i]))
            return(printf("\n💩Error File: %s Line: %d [%c]\n", __FILE__, __LINE__, map[map_start][i]), exit(1), 1);
    
    // check the last line in the map
    i = -1;
    while(map && map[height - 1][++i])
        if (!ft_strchr("1\n ", map[height - 1][i]))
            return(printf("\n💩Error File: %s Line: %d [%c]\n", __FILE__, __LINE__, map[height - 1][i]), exit(1), 1);
    
    // check the left and right borders
    i = map_start;
    while (map && map[++i + 1])
    {
        int j = 0;
        while (map[i][j] && map[i][j] == ' ')
            j++;
            
        // printf("[%d]\n", map[i][ft_strlen(map[i]) - 2]);
        if (map[i][j] && (map[i][j] != '1' || map[i][ft_strlen(map[i]) - 2] != '1'))// || map[i][ft_strlen(map[i] - 2)] != '1'))
            return(printf("\n💩Error File: %s Line: %d [%c]\n", __FILE__, __LINE__, map[height - 1][i]), exit(1), 1);
    }

    printf("VALID MAP: ✅\n");
    return (0);
}

int arr_len(char **array)
{
    int i = -1;
    while(array && array[++i])
        ;
    return (i);
}

int str_to_color(char *str_color)
{
    int color = 0;
    char **colors = ft_split(str_color, ',');
    if (!colors || arr_len(colors) < 3)
        exit(1);
        
    int r = ft_atoi(colors[0]);
    int g = ft_atoi(colors[1]);
    int b = ft_atoi(colors[2]);
    
    color = (r << 16) + (g << 8) + b;
    free_array(colors);
    return color;
}

int looad_floor_sky_colors(t_data *data, char **map)
{
    int flag = 0;
    int i = data->map_start - 1;
    
    while (map && map[++i] && flag != 2)
    {
        if (is_empty_line(map[i]))
            continue;

        char *map_line = ft_strtrim(map[i], "\n");
        printf("\n ====== %s =======\n", map_line);
        char **splited = ft_split(map_line, ' ');
        if (!splited || arr_len(splited) < 2)
            return (printf("Error: invalid colors\n"), free(map_line), free_array(splited), exit(1), 1);

        if (!ft_strcmp("F", splited[0]))
            data->floor_color = str_to_color(splited[1]);
        else if (!ft_strcmp("C", splited[0]))
            data->ceiling_color = str_to_color(splited[1]);
        flag++;
    }
    data->map_start = i;
    return (0);
}

int looad_textures(t_data *data, char **map)
{
    int i = -1;
    int flag = 0;

    while(map && map[++i] && flag != 4)
    {
        if (is_empty_line(map[i]))
            continue;

        char *map_line = ft_strtrim(map[i], "\n");
        char **splited = ft_split(map_line, ' ');
        
        printf("map line: %s\n", map_line);
        if (!splited || arr_len(splited) < 2)
            return (printf("Error, invalid texture path.\n"), free(map_line), free_array(splited), exit (1), 1);

        if (!ft_strcmp("NO", splited[0]))
            data->no_texture_path = ft_strdup(splited[1]);
        else if (!ft_strcmp("SO", splited[0]))
            data->so_texture_path = ft_strdup(splited[1]);
        else if (!ft_strcmp("WE", splited[0]))
            data->we_texture_path = ft_strdup(splited[1]);
        else if (!ft_strcmp("EA", splited[0]))
            data->ea_texture_path = ft_strdup(splited[1]);
        free_array(splited);
        free(map_line);
        flag++;
    }
    data->map_start = i;
    return (0);
}

int parse_map(t_data *data, int ac, char **av)
{
    (void) ac;
    (void) av;
    if (ac != 2)
    {
        write(2, "Error, there is no map\n", 24);
        return (1);
    }
    
    printf("map file is: %s\n", av[1]);
    if (!ft_strnstr(&av[1][ft_strlen(av[1]) - 4], ".cub", 4))
    {
        write(2, "Error, map file extention\n", 27);
        printf("==== Line: %d ====\n", __LINE__);
        printf("==== File: %s ====\n", __FILE__);
		return (1);
    }
    
    if (read_map(data, av[1]))
        return (1);
    
    // if (looad_textures(data, data->map))
    //     return (1);

    // if (looad_floor_sky_colors(data, data->map))
    //     return (1);
        
    // if (check_map_borders(data->map, data->map_height, data->map_width, data->map_start))
    //     return (1);
        
    if (init_payer_pos(data, data->map))
        return (1);

    return 0;
}
