#include "../include/cub3d.h"

void    Ft_Updata_Data(t_data *Data)
{
    if (Data->Walk_Direction != 0)
    {
        Data->Move_Step = Data->Move_Speed * Data->Walk_Direction * Data->Factor_Scale_Map;
        Ft_Is_Player_Inside_Wall(Data);
    }
    if (Data->Turn_Direction != 0)
    {
        Data->Player_Angle += Data->Turn_Direction * Data->Turn_Speed;
		Data->Player_Angle = Ft_Normalize_Angle(Data->Player_Angle);
    }
}

void    Ft_Update_Image(t_data *Data)
{
    Ft_Write_Player(Data);
    Ft_Write_Projection_Img(Data);
    Ft_Cast_All_Rays(Data);
    mlx_put_image_to_window(Data->Mlx, Data->Mlx_Win, Data->Projection_Img.Img, 0, 0);
    mlx_put_image_to_window(Data->Mlx, Data->Mlx_Win, Data->Map_Img.Img, 0, 0);
    mlx_put_image_to_window(Data->Mlx, Data->Mlx_Win, Data->Player_Img.Img, Data->Start_Player_X, Data->Start_Player_Y);
    mlx_destroy_image(Data->Mlx, Data->Player_Img.Img);
    mlx_destroy_image(Data->Mlx, Data->Projection_Img.Img);
}