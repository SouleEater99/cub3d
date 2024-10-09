/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:52:48 by ael-maim          #+#    #+#             */
/*   Updated: 2023/11/24 08:29:38 by ael-maim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;
	size_t			i;

	if (!dest && !src)
		return (dest);
	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	i = 0;
	if (d > s)
		while (n-- > 0)
			d[n] = s[n];
	else
		while (i++ < n && n != 0)
			*d++ = *s++;
	return (dest);
}
