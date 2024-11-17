/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maim <ael-maim@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 04:00:30 by ael-maim          #+#    #+#             */
/*   Updated: 2024/10/09 04:02:09 by ael-maim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
#include "./minilibx/minilibx-linux/mlx.h"
#include "./minilibx/minilibx-linux/mlx_int.h"

#define CUBE_TILE   64
#define PLAYER_TILE 10
#define BLACK       0x00000000
#define WHITE       0x00FFFFFF
#define RED         0x00FF0000
#define YELLOW      0x00FFFF00
#define BLUE        0x000000FF
#define GREEN       0x0000FF00

#ifndef PI
#define PI      3.14
#endif


typedef struct  s_image
{
    void    *Img;
    char    *Data;
    int     Lenght;
    int     N_Bytes;
    int     Endian;
    int     Width;
    int     High;
}   t_image;

typedef struct  s_data
{
    int             i;

    unsigned short  Width;
    unsigned short  High;
    unsigned short  Row;
    unsigned short  Col;

    void            *Mlx;
    void            *Mlx_Win;
    
    char            **Map;

    double          Player_Angle;
    double          X_Player;
    double          Y_Player;
    int             Turn_Direction;
    int             Walk_Direction;
    double          Turn_Speed;
    double          Move_Speed;
    double          Move_Step;
    double          Step;

    double          Factor_Scale_Map;

    t_image         Map_Img;
    t_image         Projection_Img;
    t_image         Player_Img;
    int             Start_Player_X;
    int             Start_Player_Y;
    int             Player_Offset;
    t_image         Texture_Img;

}   t_data;


t_data  *Init_Data();
void    Init_Mlx(t_data *Data);
void    Ft_Free_All(char *Msg, t_data *Data, int Exit_Status);
int     Ft_Key_Destroy(void *Param);
int     Ft_Loop_Hook(void *Param);
void    Ft_Write_Cub(t_data *Data, int x, int y, int Color);
void    Ft_Write_Player(t_data *Data);
void    Ft_Write_Map_Img(t_data *Data);
void    Ft_Write_Projection_Img(t_data *Data);
void    Ft_Create_Images(t_data *Data);
void	My_Mlx_Pixel_Put(t_image *img, int x, int y, int color);
int     Ft_Get_Color(t_image *Img, int x, int y);
void    Ft_Clone_Map_To_Player_Img(t_data *Data);
void    Ft_Write_Line(t_data *Data, int dx, int dy, int color);
int     Ft_Is_Angle_Facing_Down(double angle);
int     Ft_Is_Angle_Facing_Right(double angle);
int     Ft_Board_Protect_Map(t_data *Data, double x, double  y);
int     Ft_Is_A_Wall(t_data *Data, int x, int y);
int     Ft_Is_Player_Inside_Wall(t_data *Data);
double	Ft_Normalize_Angle(double angle);
int     Ft_Key_Press(int key, void *Param);
int     Ft_Key_Release(int key, void *Param);
void    Ft_Updata_Data(t_data *Data);
void    Ft_Update_Image(t_data *Data);


#endif
