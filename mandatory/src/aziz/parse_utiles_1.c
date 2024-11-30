/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:19:43 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/28 12:46:50 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/// @brief claculate the lenght of an array of strings.
/// @param array the array to calculate its lenght.
/// @return the lenght of the array.
int	arr_len(char **array)
{
	int	i;

	i = -1;
	if (!array)
		return (0);
	while (array[++i])
		;
	return (i);
}

/// @brief checks for white-space characters.  In the "C" and "POSIX" locales,
// these are: space, form-feed ('\f'), newline  ('\n'),
//  carriage  return  ('\r'), horizontal tab ('\t'), and vertical tab ('\v').
/// @param c the character that we want to check if it is a white-space.
/// @return return 1 if the character is an white-space.
int	ft_isspace(int c)
{
	if (ft_strchr("\n\f\t\v\t ", c))
		return (1);
	return (0);
}

/// @brief print string in stderr.
/// @param error_str string to be printed.
/// @param file which file the error is.
/// @param line which line the error is.
void	print_error(char *error_str, char *file, int line)
{
	ft_putstr_fd("\n", 2);
	ft_putstr_fd(error_str, 2);
	ft_putstr_fd("File: ------> ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(":", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd("\n\n", 2);
}

void	ft_panic(int line_num, int col_num, const char *line, void *data)
{
	printf("%d:%d: %s", line_num, col_num, line);
	ft_free_all(NULL, data, 1);
}
