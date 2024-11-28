/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:40:59 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/28 12:53:08 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	apply_shadow(int color, double shadow_factor)
{
	int	r;
	int	g;
	int	b;

	r = color >> 16 & 0xFF;
	g = color >> 8 & 0xFF;
	b = color & 0xFF;
	r = (int)(r * shadow_factor);
	g = (int)(g * shadow_factor);
	b = (int)(b * shadow_factor);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return (r << 16 | (g << 8) | b);
}

int	shade_walls(int color, double distance)
{
	double	ambient_light;
	double	shadow_factor;

	ambient_light = 0.01;
	shadow_factor = fmax(ambient_light, 1.0 / (distance + 1.0));
	return (apply_shadow(color, shadow_factor));
}
