/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:44:10 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/20 20:46:00 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cub3d.h>

void std_error(char *error, char *file, int line)
{
    write(2, "line: ", 7);
    write(2, file, ft_strlen(file));
    printf("line: %d", line);
    write(2, error, ft_strlen(error));
    // int i = -1;
    // while(error && error[++i])
        // write(2, &error[i], 1);
}
