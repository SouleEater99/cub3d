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

#define WIDTH 840
#define HIGH  480
#define CUB_SIZE 30
#define PLAYER_SIZE 10

#ifndef PI
#define PI 3.14
#endif

typedef struct	s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;




typedef struct s_data
{
	int		i;
    t_image	*img;
	void	*mlx;
	void	*mlx_win;
	char	**map;
	int		row;
	int		col;
    double     x_player;
    double     y_player;
	double	rotation_angle;
	double	walk_direction;
	double	turn_direction;
	double	move_speed;
	int		move_step;
	double	rotation_speed;
	double	step;
	


}t_data ;


void	ft_write_map_img(t_data *data);
void	ft_write_player_to_img(t_data *data);
void ft_write_line(t_data *data,int dx, int dy);
void	ft_write_cub_to_img(t_image *img, int x, int y, int color);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
int	ft_key_hook(int keycode, t_data *data);
void	ft_update_img(t_data *data);
t_data *ft_init_data();

#endif
