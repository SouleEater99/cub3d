/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:44:54 by aelkheta          #+#    #+#             */
/*   Updated: 2023/11/19 10:48:56 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(long int n)
{
	long int	counter;

	counter = 0;
	if (n < 0)
	{
		n *= -1;
		counter++;
	}
	while (n >= 10)
	{
		counter++;
		n /= 10;
	}
	if (n < 10)
		counter++;
	return (counter);
}

char	*ft_itoa(int n)
{
	char		*str;
	long int	nbr;
	int			i;

	nbr = n;
	i = int_len(nbr);
	str = (char *)malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[i] = '\0';
	if (nbr < 0)
		nbr *= -1;
	while (i--)
	{
		str[i] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
