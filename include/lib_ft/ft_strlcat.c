/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:03:08 by ael-maim          #+#    #+#             */
/*   Updated: 2023/11/19 08:51:12 by ael-maim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;
	size_t	res;
	size_t	dest_len;

	i = 0;
	if (!dest && src && !size)
	{
		return (ft_strlen(src));
	}
	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	res = dest_len + src_len;
	if (dest_len >= size)
		return (size + src_len);
	else
	{
		while (i < size - dest_len - 1 && src[i])
		{
			dest[dest_len + i] = src[i];
			i++;
		}
	}
	dest[dest_len + i] = '\0';
	return (res);
}
