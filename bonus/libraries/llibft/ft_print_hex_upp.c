/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_upp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:16:45 by aelkheta          #+#    #+#             */
/*   Updated: 2023/11/27 15:19:44 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hex_upp(unsigned int x)
{
	int		counter;
	char	*s;

	s = "0123456789ABCDEF";
	counter = 0;
	if (x < 16)
		counter += ft_print_char(s[x]);
	else
	{
		counter += ft_print_hex_upp(x / 16);
		counter += ft_print_char(s[x % 16]);
	}
	return (counter);
}
