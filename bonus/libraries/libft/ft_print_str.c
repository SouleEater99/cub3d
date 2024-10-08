/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:18:26 by aelkheta          #+#    #+#             */
/*   Updated: 2023/11/27 15:18:28 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_str(char *str)
{
	int	counter;

	counter = 0;
	if (!str)
		return (ft_print_str("(null)"));
	while (*str)
		counter += write(1, str++, 1);
	return (counter);
}
