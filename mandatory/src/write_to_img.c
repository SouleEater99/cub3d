
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

			// printf("========+{x : %d | y : %d }=======\n", x + i ,y + j);
            My_Mlx_Pixel_Put(&Data->Projection_Img, i + x, j + y, Color);
            j++;
        }
        i++;
    }

}


void    Ft_Create_Projection_Img(t_data *Data)
{
    Data->Projection_Img.Img = mlx_new_image(Data->Mlx, WIDTH, HIGH);
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

void	ft_write_player_view(t_data *Data)
{
	int		x;
	double	Angle;

	x = 0;
	Angle = Data->Player_Angle - (FOV / 2);
	while (x < Data->Num_Rays)
	{
		if (Angle > 2 * PI)
   			Angle -= 2 * PI;
		else if (Angle < 0)
    		Angle += 2 * PI;
 		Ft_Write_Line(Data, cos(Angle) * 60 * Data->Factor_Scale_Map, sin(Angle) * 60 * Data->Factor_Scale_Map, BLUE);
		Angle = Angle + ((double)FOV / (double)Data->Num_Rays);
		x++;
	}

}

void	ft_write_player(t_data *Data)
{
	int		x;
	int		y;

	x= 0;
    while (x < PLAYER_TILE)
    {
        y = 0;
        while (y < PLAYER_TILE)
        {
            My_Mlx_Pixel_Put(&Data->Projection_Img, ((Data->X_Player - (PLAYER_TILE / 2) ) + x) * Data->Factor_Scale_Map, ((Data->Y_Player - (PLAYER_TILE / 2)) + y) * Data->Factor_Scale_Map, RED);
            y++;
        }
        x++;
    }
	
}

void	ft_Write_mini_map(t_data *Data)
{

	int		x;
	int		y;
	double	ratio;

	ratio = (double)CUBE_TILE * Data->Factor_Scale_Map;
 	y = 0;
    while (y < Data->Col && y * ratio < HIGH)
    {
        x = 0;
        while (x < Data->Row && x  * ratio < WIDTH)
        {
			// printf("+=+++++++{x : %d | y : %d | ratio : %d}+++++++\n", x ,y, ratio);
            if (Data->Map[y][x] == '1')
                Ft_Write_Cub(Data, x * ratio, y * ratio, WHITE);
            else if (Data->Map[y][x] == 'D')
                Ft_Write_Cub(Data, x * ratio, y * ratio, YELLOW);
            else
                Ft_Write_Cub(Data, x * ratio, y * ratio, BLACK);
            x++;
        }
        y++;
    }
	ft_write_player(Data);
    // ft_write_player_wall_hit(Data);
	ft_write_player_view(Data);

}

int     ft_get_door_index(t_data *Data, int x, int y)
{
    int i;

    i = 0;
    while (i < Data->n_door)
    {
        if (Data->door[i].x == x && Data->door[i].y == y)
            return (i);
        i++;
    }
    return (0);
}

void    ft_write_player_wall_hit(t_data  *Data)
{
	Data->IsFaceDown = Ft_Is_Angle_Facing_Down(Data->Player_Angle);
	Data->IsFaceRight = Ft_Is_Angle_Facing_Right(Data->Player_Angle);
	Ft_Get_Wall_Hit(Data, Data->Player_Angle);
	if (Ft_Board_Protect(Data->Row, Data->Col, Data->WallHitX / CUBE_TILE, Data->WallHitY / CUBE_TILE) == 1)
    {
        if (Data->Map[(int)Data->WallHitY / CUBE_TILE][(int)Data->WallHitX / CUBE_TILE] == 'D')
        {
            Data->door_index = ft_get_door_index(Data, Data->WallHitX / CUBE_TILE, Data->WallHitY / CUBE_TILE);
            if (Data->door_index < 0)
                Ft_Free_All("Door_index Fail \n", Data, 1);
            if (!Data->door[Data->door_index].is_open)
                Data->door[Data->door_index].is_open = 1;
            else if (Data->door[Data->door_index].is_open)
                Data->door[Data->door_index].is_open = 0;
            printf("========== { index:  %c | is_open : %d } ==========\n",Data->Map[(int)Data->WallHitY / CUBE_TILE][(int)Data->WallHitX / CUBE_TILE], Data->door[Data->door_index].is_open);
        }
            // printf("===========\n");
 		// Ft_Write_Line(Data,(Data->WallHitX -  Data->X_Player) * Data->Factor_Scale_Map , (Data->WallHitY - Data->Y_Player)* Data->Factor_Scale_Map, BLUE);
    }
        
}