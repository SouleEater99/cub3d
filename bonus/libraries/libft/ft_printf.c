/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:16:09 by aelkheta          #+#    #+#             */
/*   Updated: 2023/12/01 18:05:21 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_specifier(char format, va_list args)
{
	int	counter;

	counter = 0;
	if (format == 'd' || format == 'i')
		counter += ft_putnbr(va_arg(args, int));
	else if (format == 'u')
		counter += ft_putnbr_unsigned(va_arg(args, unsigned int));
	else if (format == 'c')
		counter += ft_print_char(va_arg(args, int));
	else if (format == 's')
		counter += ft_print_str(va_arg(args, char *));
	else if (format == 'x')
		counter += ft_print_hex_low(va_arg(args, unsigned int));
	else if (format == 'X')
		counter += ft_print_hex_upp(va_arg(args, unsigned int));
	else if (format == 'p')
		counter += ft_print_address(va_arg(args, void *));
	else
		counter += ft_print_char(format);
	return (counter);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		counter;
	va_list	args;

	i = 0;
	counter = 0;
	va_start(args, format);
	if (!format || (*(format + 1) && *format == '%' && *(format + 1) == '\0'))
		return (-1);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] == '%')
		{
			counter += ft_print_char('%');
			i++;
		}
		else if (format[i] == '%')
			counter += check_specifier(format[++i], args);
		else
			counter += write(1, &format[i], 1);
		i++;
	}
	va_end(args);
	return (counter);
}
