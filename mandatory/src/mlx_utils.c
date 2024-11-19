#include "../include/cub3d.h"

void	My_Mlx_Pixel_Put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->Data + (y * img->Lenght + x * (img->N_Bytes / 8));
	*(unsigned int*)dst = color;
}


int Ft_Is_Angle_Facing_Down(double angle)
{
	if (angle > 0 && angle < PI)
		return (1);
	return (0);
}

int Ft_Is_Angle_Facing_Right(double angle)
{
	if ((angle < PI / 2 && angle >= 0) || (angle > (3 * PI) / 2))
		return (1);
	return (0);
}

int Ft_Board_Protect(int Width, int High, double x, double  y)
{
	if ((x > 0 && x < Width) && (y > 0 && y < High))
		return (1);
	return (0);
}


int Ft_Is_A_Wall(t_data *Data, int x, int y)
{
	if (Ft_Board_Protect(Data->Width, Data->High, x, y) == 1)
		if (Data->Map[y / CUBE_TILE][x / CUBE_TILE] == '1')
			return (1);
	return (0);
}

int	Ft_Is_Player_Inside_Wall(t_data *Data)
{
	double	x;
	double	y;

	x = Data->X_Player + (cos(Data->Player_Angle) * Data->Move_Step);
	y = Data->Y_Player + (sin(Data->Player_Angle) * Data->Move_Step);
	if (Data->Map[(int)y / CUBE_TILE][(int) x / CUBE_TILE] == '1')
		return (0);
	Data->X_Player = x;
	Data->Y_Player = y;
	return (1);
}

double	Ft_Normalize_Angle(double angle)
{
	if (angle > 2 * PI)
 	   angle -= 2 * PI;
	else if (angle < 0)
 	   angle += 2 * PI;
	return (angle);
}

void Ft_Write_Line(t_data *Data, int dx, int dy, int color)
{
	double x;
	double y;
	double x_increment;
	double y_increment;

	if (abs(dx) >= abs(dy))
		Data->Step = abs(dx);
	else
		Data->Step = abs(dy);
	x_increment = dx / Data->Step;
	y_increment = dy / Data->Step;
	x = (unsigned int)Data->X_Player * Data->Factor_Scale_Map; 
	y = (unsigned int)Data->Y_Player * Data->Factor_Scale_Map;
	Data->i = 0;
	while (Data->i <= Data->Step)
	{
		if (Ft_Board_Protect(Data->Width, Data->High, x, y))
			My_Mlx_Pixel_Put(&Data->Projection_Img, x, y, color);
		x += x_increment;
		y += y_increment;
		Data->i++;
	}
}


double Ft_Calc_Distance(t_data *Data, double x, double y)
{
    double dx = Data->X_Player - x;
    double dy = Data->Y_Player - y;
    return sqrt(dx * dx + dy * dy); // Euclidean distance
}