
#include "../include/cub3d.h"

t_data  *Init_Data()
{
    t_data *Data;

    Data = (t_data *)malloc(sizeof(t_data));
    if (!Data)
        return (NULL);
    Data = memset(Data, 0, sizeof(t_data));
    Data->Row = 45;
    Data->Col = 27;
    // Data->img_Width = Data->Row * CUBE_TILE;
    // Data->img_High = Data->Col * CUBE_TILE;
    Data->X_Player = 5 * CUBE_TILE + (CUBE_TILE / 2);
    Data->Y_Player = 3 * CUBE_TILE + (CUBE_TILE / 2);
    Data->Player_Angle = PI;
    Data->Turn_Speed = 0.04;
    Data->Move_Speed = 5;
    Data->Factor_Scale_Map  = 0.2;
    Data->Num_Rays = WIDTH / WALL_STRIP;
    Data->Plan_Distanced = (WIDTH / 2) / tan(FOV / 2);
   
    return (Data);
}

void    Init_Mlx(t_data *Data)
{
    Data->Mlx = mlx_init();
    if (!Data->Mlx)
        Ft_Free_All("Mlx Fail\n", Data, 1);
    Data->Mlx_Win = mlx_new_window(Data->Mlx, WIDTH, HIGH, "First Game 3D");
    if (!Data->Mlx_Win)
        Ft_Free_All("Mlx_Win Fail\n", Data, 1);
    
}