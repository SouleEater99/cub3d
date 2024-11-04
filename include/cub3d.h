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

#define WIDTH 1080
#define HIGH  480
#define CUB_SIZE 40
#define PLAYER_SIZE 4
#define	FOV_ANGLE 66
#define WALL_STRIP 4

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


typedef struct s_ray
{
	long	WallHitX;
	long	WallHitY;
	double	RayAngle;
	double	distance;
}t_ray;

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
	double	move_step;
	double	rotation_speed;
	double	step;
	t_ray	*ray;
	


}t_data ;


void	ft_write_map_img(t_data *data);
void	ft_write_player_to_img(t_data *data);
void ft_write_line(t_data *data,int dx, int dy, int color);
void	ft_write_cub_to_img(t_image *img, int x, int y, int color);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
int	ft_key_hook(int keycode, t_data *data);
void	ft_update_img(t_data *data);
t_data *ft_init_data();
void	ft_free_all(t_data *data, char *msg, int status);
int		ft_is_angle_facing_down(double angle);
int		ft_is_angle_facing_right(double angle);
void	ft_cast_all_rays(t_data *data);
int	ft_is_a_wall(t_data *data, int x, int y);
void ft_get_horz_hit(t_data *data, t_ray *ray, long *x, long *y);
void ft_get_virt_hit(t_data *data, t_ray *ray, long *x, long *y);
int	ft_normalize_angle(int angle);
int	ft_board_protect(t_data *data, int x, int y);
int		ft_calc_distance(t_data *data, int x, int y);
void	ft_get_wall_hit(t_data *data, t_ray *ray);

#endif
