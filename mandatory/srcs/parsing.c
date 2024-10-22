/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:57:39 by aelkheta          #+#    #+#             */
/*   Updated: 2024/10/22 11:47:52 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cub3d.h>

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
    
    int fd = open(av[1], O_RDONLY);
    if (fd == -1)
    {
        write(2, "Error opening file\n", 20);
        printf("==== Line: %d ====\n", __LINE__);
        printf("==== File: %s ====\n", __FILE__);
        return (1);
    }
    close(fd);
    
    if (init_map(data))
        return (1);
    return 0;
}
