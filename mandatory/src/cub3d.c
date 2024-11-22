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
    Data->Texture_Img_1.Img = mlx_xpm_file_to_image(Data->Mlx, "./textures/wall_1.xpm", &Data->Texture_Img_1.Width, &Data->Texture_Img_1.High);
    if (!Data->Texture_Img_1.Img)
        Ft_Free_All("Texture Image Load Fail\n", Data, 1);
    Data->Texture_Img_1.Data = mlx_get_data_addr(Data->Texture_Img_1.Img, &Data->Texture_Img_1.N_Bytes, &Data->Texture_Img_1.Lenght, &Data->Texture_Img_1.Endian);
    if (!Data->Texture_Img_1.Data)
        Ft_Free_All("Texture Data Load Fail\n", Data, 1);

    Data->Texture_Img_2.Img = mlx_xpm_file_to_image(Data->Mlx, "./textures/wall_2.xpm", &Data->Texture_Img_2.Width, &Data->Texture_Img_2.High);
    if (!Data->Texture_Img_2.Img)
        Ft_Free_All("Texture Image Load Fail\n", Data, 1);
    Data->Texture_Img_2.Data = mlx_get_data_addr(Data->Texture_Img_2.Img, &Data->Texture_Img_2.N_Bytes, &Data->Texture_Img_2.Lenght, &Data->Texture_Img_2.Endian);
    if (!Data->Texture_Img_2.Data)
        Ft_Free_All("Texture Data Load Fail\n", Data, 1);

    Data->Texture_Img_3.Img = mlx_xpm_file_to_image(Data->Mlx, "./textures/wall_3.xpm", &Data->Texture_Img_3.Width, &Data->Texture_Img_3.High);
    if (!Data->Texture_Img_3.Img)
        Ft_Free_All("Texture Image Load Fail\n", Data, 1);
    Data->Texture_Img_3.Data = mlx_get_data_addr(Data->Texture_Img_3.Img, &Data->Texture_Img_3.N_Bytes, &Data->Texture_Img_3.Lenght, &Data->Texture_Img_3.Endian);
    if (!Data->Texture_Img_3.Data)
        Ft_Free_All("Texture Data Load Fail\n", Data, 1);

    Data->Texture_Img_4.Img = mlx_xpm_file_to_image(Data->Mlx, "./textures/wall_4.xpm", &Data->Texture_Img_4.Width, &Data->Texture_Img_4.High);
    if (!Data->Texture_Img_4.Img)
        Ft_Free_All("Texture Image Load Fail\n", Data, 1);
    Data->Texture_Img_4.Data = mlx_get_data_addr(Data->Texture_Img_4.Img, &Data->Texture_Img_4.N_Bytes, &Data->Texture_Img_4.Lenght, &Data->Texture_Img_4.Endian);
    if (!Data->Texture_Img_4.Data)
        Ft_Free_All("Texture Data Load Fail\n", Data, 1);
}

int main()
{
    
    t_data  *Data;
    // char *Map[] = {
    //     "111111111111111111111111111111111111111111111",
    //     "100000001000000000000000000000000000000000001",
    //     "100000000000110000000000000000000000000000001",
    //     "100000001000110000000000000000000000000000001",
    //     "100011011110110000000000000000000000000000001",
    //     "100000001000000000000000000000000000000000001",
    //     "100000001000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000000000000000000000000000000000000000001",
    //     "100000001000000000000000000000000000000000001",
    //     "100000001000000000000000000000000000000000001",
    //     "100000001000000000000000000000000000000000001",
    //     "100000001000000000000000000000000000000000001",
    //     "100000001000000000000000000000000000000000001",
    //     "111111111111111111111111111111111111111111111",
    // };

    char *Map[] = {
        "1111111111111111111111",
        "10000000D0000000010001",
        "1000000011111111010001",
        "1000000000000001010001",
        "1000000000000001D10001",
        "10000001D1111000000001",
        "1000000000000000000001",
        "1000000000000000000001",
        "1000000000000000000001",
        "1111111111111111111111",
    };
    printf("=========== We Are In Debug Mode ============\n");
    Data = Init_Data();
    Data->Map = Map;
    Init_Mlx(Data);
    ft_init_door(Data);
    Ft_Write_Texture_Img(Data);
    mlx_hook(Data->Mlx_Win, 2, (1L<<0) ,Ft_Key_Press, Data);
    mlx_hook(Data->Mlx_Win, 3, (1L<<1) ,Ft_Key_Release, Data);
    mlx_hook(Data->Mlx_Win, 17, (0L) ,Ft_Key_Destroy, Data);
    mlx_loop_hook(Data->Mlx, Ft_Loop_Hook, Data);
    mlx_loop(Data->Mlx);
    Ft_Free_All(NULL, Data, 0);
}