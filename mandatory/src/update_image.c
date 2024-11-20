#include "../include/cub3d.h"

void    Ft_Updata_Data(t_data *Data)
{
    if (Data->Walk_Direction != 0)// && Data->Factor_Scale_Map != 1)
    {
        Data->Move_Step = Data->Move_Speed * Data->Walk_Direction;
        Ft_Is_Player_Inside_Wall(Data);
    }
    if (Data->Turn_Direction != 0) //&& Data->Factor_Scale_Map != 1)
    {
        Data->Player_Angle += Data->Turn_Direction * Data->Turn_Speed;
		Data->Player_Angle = Ft_Normalize_Angle(Data->Player_Angle);
    }
}

void    Ft_Update_Image(t_data *Data)
{
    Ft_Create_Projection_Img(Data);
    Ft_Cast_All_Rays(Data);
    // ft_Write_mini_map(Data);
    mlx_put_image_to_window(Data->Mlx, Data->Mlx_Win, Data->Projection_Img.Img, 0, 0);
    mlx_destroy_image(Data->Mlx, Data->Projection_Img.Img);
}