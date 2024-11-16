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


#define BLACK   0x00000000
#define WHITE   0x00FFFFFF
#define RED     0x00FF0000
#define YELLOW  0x00FFFF00
#define BLUE    0x000000FF
#define GREEN   0x0000FF00


#ifndef PI
#define PI      3.14
#endif


typedef struct  s_img
{
    void    *ImgAddr;
    char    *Data;
    int     Lenght;
    int     N_Bytes;
    int     Endian;
    int     Width;
    int     High;
}   t_img;

typedef struct  s_data
{
    unsigned short  Width;
    unsigned short  High;
    unsigned short  Row;
    unsigned short  Col;

    void            *Mlx;
    void            *Mlx_Win;
    
    char            **Map;

}   t_data;

#endif
