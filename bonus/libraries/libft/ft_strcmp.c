/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:07:56 by aelkheta          #+#    #+#             */
/*   Updated: 2024/10/26 14:19:00 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;
    // size_t len_1 = ft_strlen(str1);
    // size_t len_2 = ft_strlen(str2);

    // size_t len = len_1 > len_2 ? len_1 : len_2;

	i = 0;
	// while (i < len && (str1[i] != '\0' || str2[i] != '\0'))
	while (str1[i] != '\0' || str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}
