/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heisenberg <heisenberg@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:40:59 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/24 14:24:58 by heisenberg       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/cub3d.h"

int apply_shadow(int color, double shadow_factor)
{
	int r = color >> 16 & 0xFF;
	int g = color >> 8 & 0xFF;
	int b = color & 0xFF;


	r = (int)(r * shadow_factor);
	g = (int)(g * shadow_factor);
	b = (int)(b * shadow_factor);

	r = (r > 255) ? 255 : r;
    g = (g > 255) ? 255 : g;
    b = (b > 255) ? 255 : b;

	return (r << 16 | (g << 8) | b);
}

int shade_walls(int color ,double distance)
{
	double ambient_light = 0.2;
	double shadow_factor = fmax(ambient_light, 1.0 / (distance + 1.0)); // Calculate shadow factor

	return (apply_shadow(color, shadow_factor));
}
