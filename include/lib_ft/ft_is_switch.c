/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_switch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maim <ael-maim@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:56:57 by ael-maim          #+#    #+#             */
/*   Updated: 2024/08/17 13:59:09 by ael-maim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_switch(char *str, char *switches)
{
	int	i;
	int	j;

	i = 0;
	if (!str || !switches)
		return (0);
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		j = 0;
		while (switches[j])
			if (switches[j++] != str[i])
				return (-1);
		i++;
	}
	return (1);
}
