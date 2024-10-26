/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:21:05 by aelkheta          #+#    #+#             */
/*   Updated: 2024/10/26 15:10:21 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_the_rest(char *buffer)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (ft_free(buffer));
	str = (char *)malloc((ft_strlen(&buffer[i])) * sizeof(char));
	if (!str)
		return (ft_free(buffer));
	i++;
	j = 0;
	while (buffer[i])
		str[j++] = buffer[i++];
	str[j] = '\0';
	free(buffer);
	return (str);
}

char	*check_next_line(char *buffer)
{
	int		i;
	int		len;
	char	*i_am_the_line;

	i = 0;
	len = 0;
	if (!buffer)
		return (NULL);
	while (buffer[len] && buffer[len] != '\n')
		len++;
	i_am_the_line = (char *)malloc((len + 2) * sizeof(char));
	if (!i_am_the_line)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
	{
		i_am_the_line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		i_am_the_line[i++] = '\n';
	i_am_the_line[i] = '\0';
	return (i_am_the_line);
}

char	*reach_the_line(int fd, char *buffer)
{
	char	*line;
	int		bytes_read;

	line = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, line, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(line);
			free(buffer);
			return (NULL);
		}
		line[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, line);
		if (!buffer)
			return (NULL);
	}
	free(line);
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = reach_the_line(fd, buffer);
	if (!buffer)
		return (NULL);
	line = check_next_line(buffer);
	buffer = get_the_rest(buffer);
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
