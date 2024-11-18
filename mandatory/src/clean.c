
#include "../include/cub3d.h"

void    Ft_Free_All(char *Msg, t_data *Data, int Exit_Status)
{
    if (Data)
    {
        // if (Data->Player_Img.Img)
        //     mlx_destroy_image(Data->Mlx ,Data->Player_Img.Img);
        if (Data->Texture_Img_1.Img)
            mlx_destroy_image(Data->Mlx, Data->Texture_Img_1.Img);
        if (Data->Texture_Img_2.Img)
            mlx_destroy_image(Data->Mlx, Data->Texture_Img_2.Img);
        if (Data->Texture_Img_3.Img)
            mlx_destroy_image(Data->Mlx, Data->Texture_Img_3.Img);
        if (Data->Texture_Img_4.Img)
            mlx_destroy_image(Data->Mlx, Data->Texture_Img_4.Img);
        if (Data->Map_Img.Img)
            mlx_destroy_image(Data->Mlx, Data->Map_Img.Img);
        if (Data->Mlx_Win)
            mlx_destroy_window(Data->Mlx , Data->Mlx_Win);
        if (Data->Mlx)
        {
            mlx_destroy_display(Data->Mlx);
            free(Data->Mlx);
        }
        /// free All IMages
        free(Data);
    }
    if (Msg)
        write(2, Msg, strlen(Msg));
    exit(Exit_Status);
}
