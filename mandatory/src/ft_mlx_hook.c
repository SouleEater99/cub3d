
#include "../include/cub3d.h"



int Ft_Key_Press(int key, void *Param)
{
    t_data *Data;

    Data = (t_data *)Param;
    (void) Data;
    if (key == XK_Up || key == XK_w)
        Data->Walk_Direction = 1;
    else if (key == XK_Down || key == XK_s)
       Data->Walk_Direction = -1;
    else if (key == XK_Right)
        Data->Turn_Direction = 1;
    else if (key == XK_Left)
        Data->Turn_Direction = -1;
    else if (key == XK_m)
    {
        if (Data->Factor_Scale_Map == 1)
            Data->Factor_Scale_Map = 0.2;
        else
            Data->Factor_Scale_Map = 1;
        if (Data->Map_Img.Img)
        {
            mlx_destroy_image(Data->Mlx, Data->Map_Img.Img);
            Data->Map_Img.Img = NULL;
        }
        Ft_Write_Map_Img(Data);
        mlx_clear_window(Data->Mlx, Data->Mlx_Win);
    }
    else if (key == XK_Escape)
        Ft_Free_All(NULL, Data, 0);
    return (0);
}

int Ft_Key_Release(int key, void *Param)
{
    t_data *Data;

    Data = (t_data *)Param;
    (void) Data;
    if (key == XK_Up || key == XK_w)
        Data->Walk_Direction = 0;
    else if (key == XK_Down || key == XK_s)
       Data->Walk_Direction = 0;
    else if (key == XK_Right)
        Data->Turn_Direction = 0;
    else if (key == XK_Left)
        Data->Turn_Direction = 0;
    return (0);
}

int Ft_Key_Destroy(void *Param)
{
    Ft_Free_All(NULL, (t_data *)Param, 0);
    return (0);
}


int Ft_Loop_Hook(void *Param)
{
    t_data *Data;

    Data = (t_data *)Param;
    (void ) Data;
    Ft_Updata_Data(Data);
    Ft_Update_Image(Data);

    return (0);
}