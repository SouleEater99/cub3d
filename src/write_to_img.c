
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
            if (i % (int)(CUBE_TILE * Data->Factor_Scale_Map) && j % (int)(CUBE_TILE * Data->Factor_Scale_Map))
                My_Mlx_Pixel_Put(&Data->Map_Img, i + x, j + y, Color);
            else
                My_Mlx_Pixel_Put(&Data->Map_Img, i + x, j + y, BLACK);
            j++;
        }
        i++;
    }

}

// void    Ft_Write_Map_Img(t_data *Data)
// {
//     int x;
//     int y;

//     Data->Map_Img.Width = Data->Width * Data->Factor_Scale_Map;
//     Data->Map_Img.High= Data->High * Data->Factor_Scale_Map;
//     Data->Map_Img.Img = mlx_new_image(Data->Mlx, Data->Map_Img.Width, Data->Map_Img.High);
//     if (!Data->Map_Img.Img)
//         Ft_Free_All("Image Map Fail\n", Data, 1);
//     Data->Map_Img.Data = mlx_get_data_addr(Data->Map_Img.Img, &Data->Map_Img.N_Bytes, &Data->Map_Img.Lenght, &Data->Map_Img.Endian);
//     if (!Data->Map_Img.Data)
//         Ft_Free_All("Map Data Addres Fail\n", Data, 1);

//     y = 0;
//     while (y < Data->Col)
//     {
//         x = 0;
//         while (x < Data->Row)
//         {
//             if (Data->Map[y][x] == '1')
//                 Ft_Write_Cub(Data, x * CUBE_TILE * Data->Factor_Scale_Map, y * CUBE_TILE * Data->Factor_Scale_Map, WHITE);
//             else
//                 Ft_Write_Cub(Data, x * CUBE_TILE * Data->Factor_Scale_Map, y * CUBE_TILE * Data->Factor_Scale_Map, BLACK);
//             x++;
//         }
//         y++;
//     }
//     x = 0;
//     while (x < PLAYER_TILE)
//     {
//         y = 0;
//         while (y < PLAYER_TILE)
//         {
//             // printf("======== x : %d | y : %d | player_x :%d | player_y : %d ======\n",x,y,Data->X_Player, Data->Y_Player);
//             My_Mlx_Pixel_Put(&Data->Map_Img, ((Data->X_Player - (PLAYER_TILE / 2) ) + x) * Data->Factor_Scale_Map, ((Data->Y_Player - (PLAYER_TILE / 2)) + y) * Data->Factor_Scale_Map, RED);
//             y++;
//         }
//         x++;
//     }
//     Ft_Write_Line(Data, cos(Data->Player_Angle) * 30, sin(Data->Player_Angle) * 30, BLUE);
    
// }

void    Ft_Write_Projection_Img(t_data *Data)
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

    Color = *(int *)(Img->Data + (y * Img->Lenght) + x  * (Img->N_Bytes / 8));
    return (Color);
}

void    Ft_Clone_Map_To_Player_Img(t_data *Data)
{
    int i;
    int j;
    int Color;

    i = 0;
    while (i < Data->Player_Img.Width)
    {
        j = 0;
        while (j < Data->Player_Img.High)
        {
            Color = Ft_Get_Color(&Data->Map_Img, i + Data->Start_Player_X, j + Data->Start_Player_Y);
            My_Mlx_Pixel_Put(&Data->Player_Img, i, j, Color);
            j++;
        }
        i++;
    }
}

void    Ft_Write_Map_Img(t_data *Data)
{
    int x;
    int y;

    y = 0;
    Data->Map_Img.Width = Data->Width * Data->Factor_Scale_Map;
    Data->Map_Img.High= Data->High * Data->Factor_Scale_Map;
    Data->Map_Img.Img = mlx_new_image(Data->Mlx, Data->Map_Img.Width, Data->Map_Img.High);
    if (!Data->Map_Img.Img)
        Ft_Free_All("Image Map Fail\n", Data, 1);
    Data->Map_Img.Data = mlx_get_data_addr(Data->Map_Img.Img, &Data->Map_Img.N_Bytes, &Data->Map_Img.Lenght, &Data->Map_Img.Endian);
    if (!Data->Map_Img.Data)
        Ft_Free_All("Map Data Addres Fail\n", Data, 1);
    while (y < Data->Col)
    {
        x = 0;
        while (x < Data->Row)
        {
            if (Data->Map[y][x] == '1')
                Ft_Write_Cub(Data, x * CUBE_TILE * Data->Factor_Scale_Map, y * CUBE_TILE * Data->Factor_Scale_Map, WHITE);
            else
                Ft_Write_Cub(Data, x * CUBE_TILE * Data->Factor_Scale_Map, y * CUBE_TILE * Data->Factor_Scale_Map, BLACK);
            x++;
        }
        y++;
    }
}



void    Ft_Write_Player(t_data *Data)
{
    Data->Player_Img.Width = 2 * CUBE_TILE * Data->Factor_Scale_Map;
    Data->Player_Img.High = 2 * CUBE_TILE * Data->Factor_Scale_Map;
    if (CUBE_TILE > PLAYER_TILE)
        Data->Player_Offset = CUBE_TILE - PLAYER_TILE;
    else
        Data->Player_Offset = CUBE_TILE;
    Data->Start_Player_X = (Data->X_Player - CUBE_TILE) * Data->Factor_Scale_Map;
    Data->Start_Player_Y = (Data->Y_Player - CUBE_TILE) * Data->Factor_Scale_Map;
    Data->Player_Img.Img = mlx_new_image(Data->Mlx, Data->Player_Img.Width, Data->Player_Img.High);
    if (!Data->Player_Img.Img)
        Ft_Free_All("Image Player Image Fail\n", Data, 1);
    Data->Player_Img.Data = mlx_get_data_addr(Data->Player_Img.Img, &Data->Player_Img.N_Bytes, &Data->Player_Img.Lenght, &Data->Player_Img.Endian);
    if (!Data->Player_Img.Data)
        Ft_Free_All("Player Data Addres Fail\n", Data, 1);
    Ft_Clone_Map_To_Player_Img(Data);
}

