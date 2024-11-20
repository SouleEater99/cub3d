#include "../include/cub3d.h"

void Ft_Get_Virt_Hit(t_data *Data, double Angle, double *x, double *y)
{
	double ystep;
	double xstep;

	if (Data->IsFaceRight)
		*x = (long)(Data->X_Player / CUBE_TILE) * CUBE_TILE + CUBE_TILE;
	else
		*x = (long)(Data->X_Player / CUBE_TILE) * CUBE_TILE;
	*y = ((*x - Data->X_Player) * tan(Angle)) + Data->Y_Player;
	xstep = CUBE_TILE;
	if (!Data->IsFaceRight)
		xstep *= -1;
	ystep = xstep * tan(Angle);
	if (!Data->IsFaceDown && ystep > 0)
		ystep *= -1;

	if (!Data->IsFaceRight)
		*x -= 1;
	while ((*x > 0 && *x < Data->img_Width) && (*y < Data->img_High && *y > 0))
	{
		if (Ft_Is_A_Wall(Data, *x, *y))
			break;
		*y += ystep;
		*x += xstep;
	}
}

void Ft_Get_Horz_Hit(t_data *Data, double Angle, double *x, double *y)
{
	double ystep;
	double xstep;

	if (Data->IsFaceDown)
		*y = (long)(Data->Y_Player / CUBE_TILE) * CUBE_TILE + CUBE_TILE;
	else
		*y = (long)(Data->Y_Player / CUBE_TILE) * CUBE_TILE;
	*x = ((*y - Data->Y_Player) / tan(Angle)) + Data->X_Player;
	ystep = CUBE_TILE;
	if (!Data->IsFaceDown)
		ystep *= -1;
	xstep = ystep / tan(Angle);
	if (!Data->IsFaceRight && xstep > 0)
		xstep *= -1;
	if (!Data->IsFaceDown)
		*y -= 1;
	while ((*x > 0 && *x < Data->img_Width) && (*y < Data->img_High && *y > 0))
	{
		if (Ft_Is_A_Wall(Data, *x, *y))
			break;
		*y += ystep;
		*x += xstep;
	}
}

void	Ft_Get_Wall_Hit(t_data *Data, double Angle)
{
	double	VirtHitX;
	double	VirtHitY;
	double	HorzHitX;
	double	HorzHitY;

	HorzHitX = 0;
	HorzHitY = 0;
	VirtHitX = 0;
	VirtHitY = 0;
	// if (Data->DataAngle != PI / 2 && Data->DataAngle !=  3 * (PI / 2))
	Ft_Get_Virt_Hit(Data, Angle, &VirtHitX, &VirtHitY);
	// if (Data->DataAngle != PI / 2 && Data->DataAngle != (3 * PI) / 2)
	Ft_Get_Horz_Hit(Data, Angle, &HorzHitX, &HorzHitY);
	if (Ft_Calc_Distance(Data, HorzHitX, HorzHitY) < Ft_Calc_Distance(Data, VirtHitX, VirtHitY))
	{
		Data->Distance = Ft_Calc_Distance(Data, HorzHitX, HorzHitY);
		Data->CorrectDistance = Data->Distance * cos(Angle - Data->Player_Angle);
		Data->WallSliceHigh = ((double)CUBE_TILE / Data->CorrectDistance) * (double)Data->Plan_Distanced;
		Data->WallHitX = HorzHitX;
		Data->WallHitY = HorzHitY;
		Data->IsHitVirt = 0;
	}
	else
	{
		Data->Distance = Ft_Calc_Distance(Data, VirtHitX, VirtHitY);
		Data->CorrectDistance = Data->Distance * cos(Angle - Data->Player_Angle);
		Data->WallSliceHigh = ((double)CUBE_TILE / Data->CorrectDistance) * (double)Data->Plan_Distanced;
		Data->WallHitX = VirtHitX;
		Data->WallHitY = VirtHitY;
		Data->IsHitVirt = 1;
	}
	// printf("======{distance_horz : %f | x = %f | y = %f}======\n", Ft_Calc_Distance(Data, HorzHitX, HorzHitY),HorzHitX, HorzHitY);
	// printf("======{distance_virt : %f | x : %f | y : %f}======\n", Ft_Calc_Distance(Data, VirtHitX, VirtHitY), VirtHitX, VirtHitY);
	// printf("x_player : %f | y_player : %f\n", Data->X_Player, Data->Y_Player);
}

void	ft_write_floor(t_data *Data, int i)
{
	int	j;

	j = Data->End;
	while (j < HIGH)
		My_Mlx_Pixel_Put(&Data->Projection_Img, i * WALL_STRIP, j++, RED);
}

void	ft_write_ceiling(t_data *Data, int i)
{
	int	j;

	j = 0;
	while (j < Data->Start)
		My_Mlx_Pixel_Put(&Data->Projection_Img, i * WALL_STRIP, j++, WHITE);
}

void	ft_get_texture_color(t_data *Data, int j)
{
	int		texture_offset_x;
	int		texture_offset_y;

	if (Data->IsHitVirt)
		texture_offset_x = (int)Data->WallHitY % TEXTURE_TILE;
	else
		texture_offset_x = (int)Data->WallHitX % TEXTURE_TILE;
	int	DistanceFromTop = j + (Data->WallSliceHigh / 2) - (HIGH / 2);
	texture_offset_y = DistanceFromTop * ((double)TEXTURE_TILE / Data->WallSliceHigh);
	if ((texture_offset_x >= 0 && texture_offset_x < TEXTURE_TILE - 1) && (texture_offset_y >= 0 && texture_offset_y < TEXTURE_TILE - 1))
	{
		if (Data->IsHitVirt && Data->IsFaceRight)
			Data->color = Ft_Get_Color(&Data->Texture_Img_1 ,texture_offset_x , texture_offset_y);
		else if (Data->IsHitVirt && !Data->IsFaceRight)
			Data->color = Ft_Get_Color(&Data->Texture_Img_2 ,texture_offset_x , texture_offset_y);
		else if (!Data->IsHitVirt && Data->IsFaceDown)
			Data->color = Ft_Get_Color(&Data->Texture_Img_3 ,texture_offset_x , texture_offset_y);
		else if (!Data->IsHitVirt && !Data->IsFaceDown)
			Data->color = Ft_Get_Color(&Data->Texture_Img_4 ,texture_offset_x , texture_offset_y);
	}
}

void	ft_write_wall(t_data *Data, int i)
{
	int		j;

	j = Data->Start;
	while (j < Data->End)
	{
		ft_get_texture_color(Data, j);
		// Data->color = CEILING;
		My_Mlx_Pixel_Put(&Data->Projection_Img,i * WALL_STRIP, j++, Data->color);
	}
}

void	Ft_Write_Projection(t_data *Data, int i)
{
	Data->Start = (HIGH / 2) - (Data->WallSliceHigh / 2);
	if (Data->Start < 0)
		Data->Start = 0;
	Data->End = (HIGH / 2) + (Data->WallSliceHigh / 2);
	if (Data->End > HIGH)
		Data->End = HIGH;
	ft_write_ceiling(Data, i);
	ft_write_wall(Data, i);	
	ft_write_floor(Data, i);
}

void Ft_Cast_All_Rays(t_data *Data)
{
	int		i;
	double	Angle;

	i = 0;
	Angle = Data->Player_Angle - (FOV / 2);
	while (i < Data->Num_Rays)
	{
		if (Angle > 2 * PI)
   			Angle -= 2 * PI;
		else if (Angle < 0)
    		Angle += 2 * PI;
	    Data->IsFaceDown = Ft_Is_Angle_Facing_Down(Angle);
	    Data->IsFaceRight = Ft_Is_Angle_Facing_Right(Angle);
		Ft_Get_Wall_Hit(Data, Angle);
		Ft_Write_Projection(Data, i);
        // Ft_Write_Line(Data, (Data->WallHitX - Data->X_Player) * Data->Factor_Scale_Map, (Data->WallHitY - Data->Y_Player) * Data->Factor_Scale_Map, RED);
		Angle = Angle + ((double)FOV / (double)Data->Num_Rays);
		i++;
	}
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
            else
                Ft_Write_Cub(Data, x * ratio, y * ratio, BLACK);
            x++;
        }
        y++;
    }
	ft_write_player(Data);
	ft_write_player_view(Data);

}