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
    unsigned short  Width;
    unsigned short  High;
    unsigned short  Row;
    unsigned short  Col;

    void            *Mlx;
    void            *Mlx_Win;
    
    char            **Map;

    double          Player_Angle;
    int             X_Player;
    int             Y_Player;
    short           Turn_Direction;
    short           Walk_direction;
    double          Turn_Speed;
    double          Move_Speed;

    double          Factor_Scale_Map;

    t_image         Map_Img;
    t_image         Projection_Img;
    t_image         Player_Img;
    int             Start_Player_X;
    int             Start_Player_Y;
    t_image         Texture_Img;

}   t_data;


t_data  *Init_Data();
void    Init_Mlx(t_data *Data);
void    Ft_Free_All(char *Msg, t_data *Data, int Exit_Status);
int     Ft_Key_Hook(int key, void *Param);
int     Ft_Key_Destroy(void *Param);
int     Ft_Loop_Hook(void *Param);
void    Ft_Write_Cub(t_data *Data, int x, int y, int Color);
void    Ft_Write_Player(t_data *Data);
void    Ft_Write_Map_Img(t_data *Data);
void    Ft_Write_Projection_Img(t_data *Data);
void    Ft_Create_Image(t_data *Data);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
int     Ft_Get_Color(t_image *Img, int x, int y);

#endif
