/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:57:06 by aelkheta          #+#    #+#             */
/*   Updated: 2023/11/21 09:39:08 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*str;
	unsigned char	*destination;

	if (!dest && !src)
		return (NULL);
	if (src == dest)
		return (dest);
	str = (unsigned char *)src;
	destination = (unsigned char *)dest;
	while (n--)
	{
		*destination++ = *str++;
	}
	return (dest);
}
