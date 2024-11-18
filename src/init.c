
#include "../include/cub3d.h"

t_data  *Init_Data()
{
    t_data *Data;

    Data = (t_data *)malloc(sizeof(t_data));
    if (!Data)
        return (NULL);
    Data = memset(Data, 0, sizeof(t_data));
    Data->Row = 23;
    Data->Col = 11;
    Data->Width = Data->Row * CUBE_TILE;
    Data->High = Data->Col * CUBE_TILE;
    Data->X_Player = 5 * CUBE_TILE + (CUBE_TILE / 2);
    Data->Y_Player = 3 * CUBE_TILE + (CUBE_TILE / 2);
    Data->Player_Angle = PI;
    Data->Turn_Speed = 0.2;
    Data->Move_Speed = 8;
    Data->Factor_Scale_Map  = 0.2;
    Data->Num_Rays = Data->Width / WALL_STRIP;
    Data->Plan_Distanced = (Data->Width / 2) / tan(FOV / 2);
   
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