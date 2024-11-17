
#include "../include/cub3d.h"


int Ft_Key_Hook(int key, void *Param)
{
    t_data *Data;

    Data = (t_data *)Param;
    (void) Data;
    if (key == XK_Up || key == XK_w)
    {
        Data->Walk_direction = 1;
        // check play is inside wall
        Data->X_Player += cos(Data->Player_Angle) * Data->Move_Speed * Data->Walk_direction;
        Data->Y_Player += sin(Data->Player_Angle) * Data->Move_Speed * Data->Walk_direction;
    }
    else if (key == XK_Down || key == XK_s)
    {
        Data->Walk_direction = -1;
        // check play is inside wall
        Data->X_Player += cos(Data->Player_Angle) * Data->Move_Speed * Data->Walk_direction;
        Data->Y_Player += sin(Data->Player_Angle) * Data->Move_Speed * Data->Walk_direction;

    }
    else if (key == XK_Left)
    {

    }
    else if (key == XK_Right)
    {

    }
    else if (key == XK_Escape)
        Ft_Free_All(NULL, Data, 0);
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
    static unsigned int i;

    Data = (t_data *)Param;
    (void ) Data;
    // if (i % 3000 == 0)
    // {
    //    printf("==================\n");
        Ft_Write_Player(Data);
        mlx_put_image_to_window(Data->Mlx, Data->Mlx_Win, Data->Projection_Img.Img, 0, 0);
        mlx_put_image_to_window(Data->Mlx, Data->Mlx_Win, Data->Map_Img.Img, 0, 0);
        mlx_put_image_to_window(Data->Mlx, Data->Mlx_Win, Data->Player_Img.Img, Data->Start_Player_X, Data->Start_Player_Y);
        mlx_destroy_image(Data->Mlx, Data->Player_Img.Img);
    // }
    i++;
    return (0);
}