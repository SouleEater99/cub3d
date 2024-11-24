/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_address.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:13:01 by aelkheta          #+#    #+#             */
/*   Updated: 2023/11/27 15:19:30 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_add_hex(unsigned long int x)
{
	int		counter;
	char	*s;

	s = "0123456789abcdef";
	counter = 0;
	if (x < 16)
		counter += ft_print_char(s[x]);
	else
	{
		counter += ft_print_add_hex(x / 16);
		counter += ft_print_char(s[x % 16]);
	}
	return (counter);
}

int	ft_print_address(void *ptr)
{
	int					counter;
	unsigned long int	x;

	counter = 0;
	x = (unsigned long int)ptr;
	if (ptr == (void *)0)
		return (ft_print_str("(nil)"));
	counter += write(1, "0x", 2);
	counter += ft_print_add_hex(x);
	return (counter);
}
