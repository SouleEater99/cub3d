/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:45:04 by ael-maim          #+#    #+#             */
/*   Updated: 2024/12/03 13:30:36 by aelkheta         ###   ########.fr       */
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

char	*get_next_line(int fd)
{
	static char	*buckup;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buckup = get_buffer_line(fd, buckup);
	if (!buckup)
		return (NULL);
	line = ft_get_nl(buckup);
	if (!line)
		return (NULL);
	buckup = ft_get_remaind(buckup);
	return (line);
}
