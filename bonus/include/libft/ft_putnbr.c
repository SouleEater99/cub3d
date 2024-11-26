/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:16:55 by aelkheta          #+#    #+#             */
/*   Updated: 2023/11/28 11:13:47 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n)
{
	int	counter;

	counter = 0;
	if (n == -2147483648)
		counter += write(1, "-2147483648", 11);
	else if (n < 0)
	{
		counter += ft_print_char('-');
		counter += ft_putnbr(-n);
	}
	else if (n >= 0 && n < 10)
		counter += ft_print_char(n + '0');
	else
	{
		counter += ft_putnbr(n / 10);
		counter += ft_putnbr(n % 10);
	}
	return (counter);
}
