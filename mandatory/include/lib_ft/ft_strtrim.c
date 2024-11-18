/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:27:05 by ael-maim          #+#    #+#             */
/*   Updated: 2023/11/14 08:31:13 by ael-maim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_check_set(char c, char const *set)
{
	if (!set)
		return (1);
	while (*set)
		if (*set++ == c)
			return (0);
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	size_t	end;
	char	*str;

	i = 0;
	end = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	while (s1[i] && !ft_check_set(s1[i], set))
		i++;
	while (len > i && !ft_check_set(s1[len - 1], set))
		len--;
	str = malloc(len - i + 1);
	if (!str)
		return (NULL);
	while (i < len)
		str[end++] = s1[i++];
	str[end] = '\0';
	return (str);
}
