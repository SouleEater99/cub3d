/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:57:46 by aelkheta          #+#    #+#             */
/*   Updated: 2023/11/22 20:06:24 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_count(const char *s, char c)
{
	size_t	counter;

	counter = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			counter++;
			while (*s && *s != c)
				s++;
		}
	}
	return (counter);
}

static void	*free_err(char **sub_str, size_t j)
{
	while (j > 0)
		free(sub_str[--j]);
	free(sub_str);
	return (NULL);
}

static char	*fill_sub(char *str, const char *s, size_t len)
{
	size_t	i;

	i = 0;
	while (len)
	{
		str[i] = s[i];
		i++;
		len--;
	}
	str[i] = '\0';
	return (str);
}

static char	**splited(char **sub_str, const char *s, char c, size_t sub_count)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = 0;
	while (s[i] && j < sub_count)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			len++;
			i++;
		}
		sub_str[j] = (char *)malloc((len + 1) * sizeof(char));
		if (!sub_str[j])
			free_err(sub_str, j);
		fill_sub(sub_str[j], &s[i - len], len);
		len = 0;
		j++;
	}
	sub_str[j] = NULL;
	return (sub_str);
}

char	**ft_split(const char *s, char c)
{
	size_t	sub_count;
	char	**sub_str;

	if (s == NULL)
		return (NULL);
	sub_count = word_count(s, c);
	sub_str = (char **)malloc((sub_count + 1) * sizeof(char *));
	if (!sub_str)
		return (NULL);
	sub_str = splited(sub_str, s, c, sub_count);
	return (sub_str);
}
