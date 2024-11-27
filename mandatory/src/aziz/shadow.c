/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:40:59 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/27 20:29:33 by aelkheta         ###   ########.fr       */
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
	r = (r > 255) ? 255 : r;
	g = (g > 255) ? 255 : g;
	b = (b > 255) ? 255 : b;
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
