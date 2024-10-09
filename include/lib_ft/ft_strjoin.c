/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:48:50 by ael-maim          #+#    #+#             */
/*   Updated: 2023/11/11 17:11:16 by ael-maim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	s1_len;
	char	*d;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	s1_len = ft_strlen(s1);
	d = (char *)malloc(s1_len + ft_strlen(s2) + 1);
	if (d == NULL)
		return (NULL);
	while (s1[i])
	{
		d[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		d[s1_len + i] = s2[i];
		i++;
	}
	d[s1_len + i] = '\0';
	return (d);
}
