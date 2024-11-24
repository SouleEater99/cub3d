/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 09:58:46 by aelkheta          #+#    #+#             */
/*   Updated: 2023/11/23 10:39:20 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dstlen;
	size_t	srclen;

	i = 0;
	if (src == NULL)
		return (0);
	srclen = ft_strlen(src);
	if (dst == NULL && size == 0)
		return (srclen);
	dstlen = ft_strlen(dst);
	j = dstlen;
	if (size == 0 || size <= dstlen)
		return (srclen + size);
	while (src[i] && i < size - dstlen - 1)
		dst[j++] = src[i++];
	dst[j] = '\0';
	return (dstlen + srclen);
}
