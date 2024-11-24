/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:17:07 by aelkheta          #+#    #+#             */
/*   Updated: 2023/11/27 15:17:10 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_unsigned(unsigned int x)
{
	int	counter;

	counter = 0;
	if (x < 10)
		counter += ft_print_char(x + '0');
	else
	{
		counter += ft_putnbr_unsigned(x / 10);
		counter += ft_putnbr_unsigned(x % 10);
	}
	return (counter);
}
