/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:45:04 by ael-maim          #+#    #+#             */
/*   Updated: 2024/12/03 16:27:43 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_nl(char *to_free)
{
	if (to_free)
		free(to_free);
	return (NULL);
}

char	*get_buffer_line(int fd, char *buckup)
{
	int		rd_byts;
	char	*buffer;

	rd_byts = 1;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (ft_free_nl(buckup));
	while (rd_byts > 0 && ft_check_nl(buckup) == 0)
	{
		rd_byts = read(fd, buffer, BUFFER_SIZE);
		if (rd_byts < 0)
			return (free(buffer), ft_free_nl(buckup));
		buffer[rd_byts] = '\0';
		buckup = ft_strjoin_nl(buckup, buffer);
	}
	if (!buckup[0])
		return (free(buffer), ft_free_nl(buckup));
	return (free(buffer), buckup);
}

// char	*get_next_line(int fd)
// {
// 	static char	*buckup;
// 	char		*line;

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	buckup = get_buffer_line(fd, buckup);
// 	if (!buckup)
// 		return (NULL);
// 	line = ft_get_nl(buckup);
// 	if (!line)
// 		return (NULL);
// 	buckup = ft_get_remaind(buckup);
// 	return (line);
// }

// #include <unistd.h>
// #include <stdlib.h>
// #include <string.h>
// #include <fcntl.h>
// #include <stdio.h>

#include "libft.h"

char *get_next_line(int fd)
{
    size_t buffer_size = 128;
    char *line = malloc(buffer_size);
    size_t pos = 0;
    char ch;
    ssize_t bytes_read;

    if (fd < 0 || !line)
        return (NULL);

    while ((bytes_read = read(fd, &ch, 1)) > 0)
    {
        if (pos >= buffer_size - 1)
        {
            char *temp = realloc(line, buffer_size * 2);
            if (!temp)
            {
                free(line);
                return (NULL);
            }
            line = temp;
            buffer_size *= 2;
        }
        line[pos++] = ch;
        if (ch == '\n')
            break;
    }

    if (bytes_read <= 0 && pos == 0)
    {
        free(line);
        return (NULL);
    }

    line[pos] = '\0';
    return (line);
}