/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maim <ael-maim@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 04:00:00 by ael-maim          #+#    #+#             */
/*   Updated: 2024/10/09 04:00:17 by ael-maim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->Data + (y * img->Lenght + x * (img->N_Bytes / 8));
	*(unsigned int*)dst = color;
}

int main()
{
    t_data  *Data;
    char *Map[] = {
        "111111111111111111",
        "100000001000000001",
        "100000000000110001",
        "100000001000110001",
        "100011011110110001",
        "100000001000000001",
        "100000000000000001",
        "100000001000000001",
        "111111111111111111",
    };
    printf("=========== We Are In Debug Mode ============\n");
    Data = Init_Data();
    Data->Map = Map;
    Init_Mlx(Data);
    Ft_Create_Image(Data);
    mlx_hook(Data->Mlx_Win, 2, (1L<<0) ,Ft_Key_Hook, Data);
    mlx_hook(Data->Mlx_Win, 17, (0L) ,Ft_Key_Destroy, Data);
    mlx_loop_hook(Data->Mlx, Ft_Loop_Hook, Data);
    mlx_loop(Data->Mlx);
    Ft_Free_All(NULL, Data, 0);
}