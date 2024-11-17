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
	while ((*x > 0 && *x < Data->Width) && (*y < Data->High && *y > 0))
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
	while ((*x > 0 && *x < Data->Width) && (*y < Data->High && *y > 0))
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

void	Ft_Write_Projection(t_data *Data, int i)
{
	int j = 0;
	u_int32_t color;
	// unsigned int		texture_offset_x;
	// unsigned int		texture_offset_y;

	Data->Start = (Data->High / 2) - (Data->WallSliceHigh / 2);
	if (Data->Start < 0)
		Data->Start = 0;
	Data->End = (Data->High / 2) + (Data->WallSliceHigh / 2);
	if (Data->End > Data->High)
		Data->End = Data->High;
	// if (Data->IsHitVirt)
	// 	texture_offset_x = (int)Data->WallHitY % TEXTURE_TILE;
	// 	texture_offset_x = (int)Data->WallHitY % Data->texture_img_high;
	// else
	// 	texture_offset_x = (int)Data->WallHitX % TEXTURE_TILE;
	// 	texture_offset_x = (int)Data->WallHitX % Data->texture_img_width;
	j = 0;
	while (j < Data->Start)
		My_Mlx_Pixel_Put(&Data->Projection_Img, i * WALL_STRIP, j++, 0x0000FFFF);
	j = Data->Start;
	while (j < Data->End)
	{
		// texture_offset_y = (j - Data->Start) * Data->texture_img_high / wallhigh;
		// printf("============== {WallHittX : %d | WallHitY : %d} ===============\n", (int)Data->WallHitX % TEXTURE_TILE, (int)Data->WallHitY % TEXTURE_TILE);
		// printf("============== {OffsetX : %d | OffsetY : %d| IsHitVirt : %d} ===============\n", (int)texture_offset_x, (int)texture_offset_y, Data->IsHitVirt);
		// if ( (int) texture_offset_x < Data->texture_img_width && (int)texture_offset_y < Data->texture_img_high)
			// color = ft_get_pixel_color(Data, texture_offset_x , texture_offset_y);
			// color /= Data->texture[(texture_offset_y * TEXTURE_TILE) + texture_offset_x];
		color = 0xFFFFFFFF;
		My_Mlx_Pixel_Put(&Data->Projection_Img,i * WALL_STRIP, j++, color);
	}
	j = Data->End;
	while (j < Data->High)
		My_Mlx_Pixel_Put(&Data->Projection_Img, i * WALL_STRIP, j++, 0xFF0F0F00);
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
        Ft_Write_Line_Player(Data, cos(Angle) * 40, sin(Angle) * 40, RED);
        // Ft_Write_Line(Data, (Data->WallHitX - Data->X_Player) * Data->Factor_Scale_Map, (Data->WallHitY - Data->Y_Player) * Data->Factor_Scale_Map, RED);
		Angle = Angle + ((double)FOV / (double)Data->Num_Rays);
		i++;
	}

}