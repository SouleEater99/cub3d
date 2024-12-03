/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 21:27:26 by aelkheta          #+#    #+#             */
/*   Updated: 2023/11/20 11:37:24 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			i;
	unsigned int	len;
	char			*str_mapi;

	i = 0;
	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	str_mapi = (char *)malloc((len + 1) * sizeof(char));
	if (!str_mapi)
		return (NULL);
	while (i < len)
	{
		str_mapi[i] = f(i, s[i]);
		i++;
	}
	str_mapi[i] = '\0';
	return (str_mapi);
}
