/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_low.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:16:32 by aelkheta          #+#    #+#             */
/*   Updated: 2023/11/27 15:19:38 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hex_low(unsigned int x)
{
	int		counter;
	char	*s;

	s = "0123456789abcdef";
	counter = 0;
	if (x < 16)
		counter += ft_print_char(s[x]);
	else
	{
		counter += ft_print_hex_low(x / 16);
		counter += ft_print_char(s[x % 16]);
	}
	return (counter);
}
