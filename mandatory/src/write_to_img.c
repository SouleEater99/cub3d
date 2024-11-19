
#include "../include/cub3d.h"

void    Ft_Write_Cub(t_data *Data, int x, int y, int Color)
{
    int i;
    int j;

    i = 0;
    while (i < (int)(CUBE_TILE * Data->Factor_Scale_Map))
    {
        j = 0;
        while (j < (int)(CUBE_TILE * Data->Factor_Scale_Map))
        {
            My_Mlx_Pixel_Put(&Data->Projection_Img, i + x, j + y, Color);
            j++;
        }
        i++;
    }

}


void    Ft_Create_Projection_Img(t_data *Data)
{
    Data->Projection_Img.Img = mlx_new_image(Data->Mlx, Data->Width, Data->High);
    if (!Data->Projection_Img.Img)
        Ft_Free_All("Image Projection Image Fail\n", Data, 1);
    Data->Projection_Img.Data = mlx_get_data_addr(Data->Projection_Img.Img, &Data->Projection_Img.N_Bytes, &Data->Projection_Img.Lenght, &Data->Projection_Img.Endian);
    if (!Data->Projection_Img.Data)
        Ft_Free_All("Projection Data Addres Fail\n", Data, 1);

}

int     Ft_Get_Color(t_image *Img, int x, int y)
{
    int Color;

    // if (Ft_Board_Protect(Img->Width, Img->High, x, y))
        Color = *(int *)(Img->Data + (y * Img->Lenght) + x  * (Img->N_Bytes / 8));
    return (Color);
}

