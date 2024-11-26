/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:18:03 by aelkheta          #+#    #+#             */
/*   Updated: 2023/11/23 06:43:25 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*ptr;
	size_t	c;

	c = n * size;
	if (n > 0 && SIZE_MAX / n < size)
		return (NULL);
	ptr = (void *)malloc(c);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, c);
	return (ptr);
}
