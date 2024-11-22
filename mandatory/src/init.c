
#include "../include/cub3d.h"

void    ft_init_door(t_data *Data)
{
    Data->n_door = 3;
    Data->door = (t_door *)malloc(sizeof(t_door) * Data->n_door);
    Data->door   = memset(Data->door, 0, sizeof(t_door) * Data->n_door);
    Data->door[0].x = 8;
    Data->door[0].y = 1;
    Data->door[1].x = 16;
    Data->door[1].y = 4;
    Data->door[2].x = 8;
    Data->door[2].y = 5;
}

t_data  *Init_Data()
{
    t_data *Data;

    Data = (t_data *)malloc(sizeof(t_data));
    if (!Data)
        return (NULL);
    Data = memset(Data, 0, sizeof(t_data));
    Data->Row = 22;
    Data->Col = 10;
    Data->Factor_Scale_Map  = 0.2;
    Data->img_Width = Data->Row * (int)CUBE_TILE;
    Data->img_High = Data->Col * (int)CUBE_TILE;
    Data->X_Player = 5 * CUBE_TILE + (CUBE_TILE / 2);
    Data->Y_Player = 3 * CUBE_TILE + (CUBE_TILE / 2);
    Data->Player_Angle = PI;
    Data->Turn_Speed = 0.04;
    Data->Move_Speed = 5;
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