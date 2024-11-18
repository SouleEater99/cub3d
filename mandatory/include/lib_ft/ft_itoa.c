/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:08:54 by ael-maim          #+#    #+#             */
/*   Updated: 2023/11/11 17:26:46 by ael-maim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(int num)
{
	long	i;
	long	n;

	i = 0;
	n = num;
	if (num == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	nbr;
	long	tmp;
	char	*str;

	nbr = n;
	tmp = ft_count_digits(nbr);
	str = (char *)malloc(tmp + 1);
	if (!str)
		return (NULL);
	str[tmp--] = '\0';
	if (n == 0)
		str[0] = '0';
	if (nbr < 0)
	{
		nbr = -nbr;
		str[0] = '-';
	}
	while (nbr > 0)
	{
		str[tmp--] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (str);
}
