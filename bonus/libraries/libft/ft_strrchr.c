/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:01:52 by aelkheta          #+#    #+#             */
/*   Updated: 2023/11/21 09:55:13 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t		i;
	const char	*s;

	i = 0;
	s = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			s = &str[i];
		i++;
	}
	if (c == '\0')
		return ((char *)&str[i]);
	else
		return ((char *)s);
}
