/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 04:00:00 by ael-maim          #+#    #+#             */
/*   Updated: 2024/11/26 13:43:57 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"


int main(int ac, char **av)
{
    t_data  data;
    memset(&data, 0, sizeof(t_data));

    init_data(&data, ac, av);
    mlx_hook(data.win_ptr, 2, (1L<<0) ,ft_key_press, &data);
    mlx_hook(data.win_ptr, 3, (1L<<1) ,ft_key_release, &data);
    mlx_hook(data.win_ptr, 17, (0L) ,ft_key_destroy, &data);
	mlx_mouse_hook(data.win_ptr, mouse_events, &data);
    mlx_loop_hook(data.mlx_ptr, ft_loop_hook, &data);
    mlx_loop(data.mlx_ptr);
    ft_free_all(NULL, &data, 0);

}