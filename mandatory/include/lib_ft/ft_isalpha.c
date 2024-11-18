/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:05:43 by ael-maim          #+#    #+#             */
/*   Updated: 2023/11/11 12:05:52 by ael-maim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int argument)
{
	if (argument >= 'a' && argument <= 'z')
		return (1);
	else if (argument >= 'A' && argument <= 'Z')
		return (2);
	return (0);
}
