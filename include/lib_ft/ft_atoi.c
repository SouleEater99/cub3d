/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:36:07 by ael-maim          #+#    #+#             */
/*   Updated: 2023/11/16 15:03:16 by ael-maim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	count;

	i = 0;
	count = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -sign;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (count > 9223372036854775807 / 10)
		{
			if (sign > 0)
				return (-1);
			else
				return (0);
		}
		count = (count * 10) + (str[i] - '0');
		i++;
	}
	return (count * sign);
}
