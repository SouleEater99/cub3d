/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:14:48 by ael-maim          #+#    #+#             */
/*   Updated: 2023/11/19 09:16:17 by ael-maim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	while (n > 0 && *str1 && *str2 && *str1 == *str2)
	{
		n--;
		str1++;
		str2++;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)*(str1) - (unsigned char)*(str2));
}
