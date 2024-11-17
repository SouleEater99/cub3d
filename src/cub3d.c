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

void    Ft_Create_Images(t_data *Data)
{
    (void)Data;
    // Ft_Write_Projection_Img(Data);
    // Ft_Write_Player(Data);
    // mlx_put_image_to_window(Data->Mlx, Data->Mlx_Win, Data->Projection_Img.Img, 0, 0);
    // mlx_put_image_to_window(Data->Mlx, Data->Mlx_Win, Data->Player_Img.Img, Data->Start_Player_X, Data->Start_Player_Y);
    // Ft_Write_Map_Img(Data);
    // mlx_put_image_to_window(Data->Mlx, Data->Mlx_Win, Data->Map_Img.Img, 0, 0);

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
    // Ft_Create_Images(Data);
    mlx_hook(Data->Mlx_Win, 2, (1L<<0) ,Ft_Key_Press, Data);
    mlx_hook(Data->Mlx_Win, 3, (1L<<1) ,Ft_Key_Release, Data);
    mlx_hook(Data->Mlx_Win, 17, (0L) ,Ft_Key_Destroy, Data);
    mlx_loop_hook(Data->Mlx, Ft_Loop_Hook, Data);
    mlx_loop(Data->Mlx);
    Ft_Free_All(NULL, Data, 0);
}