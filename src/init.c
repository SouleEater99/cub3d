
#include "../include/cub3d.h"

t_data  *Init_Data()
{
    t_data *Data;

    Data = (t_data *)malloc(sizeof(t_data));
    if (!Data)
        return (NULL);
    Data = memset(Data, 0, sizeof(t_data));
    Data->Row = 18;
    Data->Col = 9;
    Data->Width = Data->Row * CUBE_TILE;
    Data->High = Data->Col * CUBE_TILE;
    Data->X_Player = 5 * CUBE_TILE + (CUBE_TILE / 2);
    Data->Y_Player = 3 * CUBE_TILE + (CUBE_TILE / 2);
    Data->Player_Angle = PI / 2;
    Data->Turn_Speed = 0.2;
    Data->Move_Speed = 4;
    Data->Factor_Scale_Map  = 0.2;
    Data->Player_Img.Width = 2 * CUBE_TILE * Data->Factor_Scale_Map;
    Data->Player_Img.High = 2 * CUBE_TILE * Data->Factor_Scale_Map;
    if (CUBE_TILE > PLAYER_TILE)
        Data->Player_Offset = CUBE_TILE - PLAYER_TILE;
    else
        Data->Player_Offset = CUBE_TILE;
    return (Data);
}

void    Init_Mlx(t_data *Data)
{
    Data->Mlx = mlx_init();
    if (!Data->Mlx)
        Ft_Free_All("Mlx Fail\n", Data, 1);
    Data->Mlx_Win = mlx_new_window(Data->Mlx, Data->Width, Data->High, "First Game 3D");
    if (!Data->Mlx_Win)
        Ft_Free_All("Mlx_Win Fail\n", Data, 1);
    
}