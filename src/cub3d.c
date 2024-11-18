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

void    Ft_Write_Texture_Img(t_data *Data)
{
    Data->Texture_Img.Img = mlx_xpm_file_to_image(Data->Mlx, "./wall_1.xpm", &Data->Texture_Img.Width, &Data->Texture_Img.High);
    if (!Data->Texture_Img.Img)
        Ft_Free_All("Texture Image Load Fail\n", Data, 1);
    Data->Texture_Img.Data = mlx_get_data_addr(Data->Texture_Img.Img, &Data->Texture_Img.N_Bytes, &Data->Texture_Img.Lenght, &Data->Texture_Img.Endian);
    if (!Data->Texture_Img.Data)
        Ft_Free_All("Texture Data Load Fail\n", Data, 1);
}

void    Ft_Create_Images(t_data *Data)
{
    Ft_Write_Map_Img(Data);
    Ft_Write_Texture_Img(Data);

}

int main()
{
    t_data  *Data;
    char *Map[] = {
        "11111111111111111111111",
        "10000000100000000000001",
        "10000000000011000000001",
        "10000000100011000000001",
        "10001101111011000000001",
        "10000000100000000000001",
        "10000000100000000000001",
        "10000000100000000000001",
        "10000000100000000000001",
        "10000000100000000000001",
        "11111111111111111111111",
    };
    printf("=========== We Are In Debug Mode ============\n");
    Data = Init_Data();
    Data->Map = Map;
    Init_Mlx(Data);
    Ft_Create_Images(Data);
    mlx_hook(Data->Mlx_Win, 2, (1L<<0) ,Ft_Key_Press, Data);
    mlx_hook(Data->Mlx_Win, 3, (1L<<1) ,Ft_Key_Release, Data);
    mlx_hook(Data->Mlx_Win, 17, (0L) ,Ft_Key_Destroy, Data);
    mlx_loop_hook(Data->Mlx, Ft_Loop_Hook, Data);
    mlx_loop(Data->Mlx);
    Ft_Free_All(NULL, Data, 0);
}