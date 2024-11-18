/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 08:41:06 by ael-maim          #+#    #+#             */
/*   Updated: 2023/11/17 08:49:37 by ael-maim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_creat_tab(char **tab, const char *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (str[i] != '\0')
		count = 1;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c && str[i + 1])
			count++;
		i++;
	}
	tab = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	tab[count] = NULL;
	return (tab);
}

static char	*ft_strdup_char(char const *str, char c)
{
	size_t	i;
	char	*d;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	d = (char *)malloc(i + 1);
	if (!d)
		return (NULL);
	i = 0;
	while (str[i] != c && str[i])
	{
		d[i] = str[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

static char	**ft_free(char **tab, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free(tab[j++]);
	free(tab);
	return (NULL);
}

static const char	*ft_replace_str(const char *s, char c)
{
	while (*s && *s != c)
		s++;
	while (*s && *s == c)
		s++;
	return (s);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**tab;

	if (!s)
		return (NULL);
	while (*s && *s == c)
		s++;
	i = 0;
	tab = NULL;
	tab = ft_creat_tab(tab, s, c);
	if (!tab)
		return (NULL);
	while (*s)
	{
		tab[i] = ft_strdup_char(s, c);
		if (!tab[i++])
			return (ft_free(tab, i));
		s = ft_replace_str(s, c);
	}
	return (tab);
}
