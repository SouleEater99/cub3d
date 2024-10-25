/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:57:39 by aelkheta          #+#    #+#             */
/*   Updated: 2024/10/25 10:46:27 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cub3d.h>

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
    int i;
    int fd;
    int map_h;
    
    fd = open(map_path, O_RDONLY);
    if (fd == -1)
        return (printf("FILE: %s, LINE: %d\n", __FILE__, __LINE__), perror(map_path), 1);
    
    i = -1;
    map_h = map_height(map_path);
    data->map = (char **)malloc(sizeof(char *) * (map_h + 1));
    while(++i < map_h)
        data->map[i] = get_next_line(fd);
    data->map[i] = NULL;
    
    data->map_height = map_h;
    data->map_width = ft_strlen(data->map[0]);

    print_map(data->map);
    
    // free_array(data->map);
    close(fd);
    return (0);
}

void init_payer_pos(t_data *data, char **map)
{
    int x, y;

    y = -1;
    while(map && map[++y])
    {
        x = -1;
        while(map[y] && map[y][++x])
        {
            // if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W')
            if (strchr("NSEW", map[y][x]))
            {
                data->player_dir = map[y][x];
                data->map[y][x] = '0';
                data->player_x = x;
                data->player_y = y;
                printf("player at: [%lf][%lf] = [%c]\n", data->player_y, data->player_x, data->map[(int)data->player_y][(int)data->player_x]);
                return ;
            }
        }
    }
}

int parse_map(t_data *data, int ac, char **av)
{
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
    
    init_payer_pos(data, data->map);
    // if (init_map(data))
    //     return (1);
    return 0;
}
