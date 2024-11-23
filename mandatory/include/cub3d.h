/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 04:00:30 by ael-maim          #+#    #+#             */
/*   Updated: 2024/11/23 11:57:08 by aelkheta         ###   ########.fr       */
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

#define WIDTH           800
#define HIGH            600
#define CUBE_TILE       64
#define TEXTURE_TILE    64
#define PLAYER_TILE     10
#define FOV             (66 * (PI / 180))
#define WALL_STRIP      1
#define BLACK           0x00000000
#define WHITE           0x00FFFFFF
#define RED             0x00FF0000
#define YELLOW          0x00FFFF00
#define BLUE            0x000000FF
#define GREEN           0x0000FF00
#define CEILING         0x00E11E1E
#define FLOOR           0x00DC6400

#ifndef PI
#define PI              3.14159265358979323846
#endif

typedef struct s_door
{
    int x;
    int y;
    int is_open;
}t_door;


typedef struct  s_image
{
    void    *img_ptr;
    void    *img_data;
    int     bits_per_pixel;
    int     size_line;
    int     endian;
    int     width;
    int     height;
}   t_image;

typedef struct  s_data
{
    int             i;

    unsigned short  img_width;
    unsigned short  img_height;
    unsigned short  row;
    unsigned short  col;

    void            *mlx_ptr;
    void            *win_ptr;
    
    char            **map;
    unsigned int    color;
	int             is_face_down;
	int             is_face_right;
    double          distance;
    double          correct_distance;
    double          wall_slice_high;
    double          wall_hit_x;
    double          wall_hit_y;
    int             is_hit_virt;
    int             num_rays;

    
    double          plan_distanced;
    int             start;
    int             end;

    t_door          door;
    int             flag;

    double          x_player;
    double          y_player;
    int             turn_direction;
    int             walk_direction;
    double          turn_speed;
    double          move_speed;
    double          move_step;
    double          step;
    double          player_angle;
    double          player_distance;
    double          player_wallhit_x;
    double          player_wallhit_y;
    

    double          factor_scale_map;

    t_image         projection_img;
    t_image         texture_img_1;
    t_image         texture_img_2;
    t_image         texture_img_3;
    t_image         texture_img_4;
    int             start_player_x;
    int             start_player_y;
    int             player_offset;

}   t_data;


t_data  *init_data();
void    init_mlx(t_data *data);
void    ft_free_all(char *Msg, t_data *data, int Exit_Status);
int     ft_key_destroy(void *Param);
int     ft_loop_hook(void *Param);
void    ft_write_cub(t_data *data, int x, int y, int Color);
void    ft_create_pojection_img(t_data *data);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
int     ft_get_color(t_image *Img, int x, int y);
void    ft_write_line(t_data *data, int dx, int dy, int color);
int     ft_is_angle_facing_down(double angle);
int     ft_is_angle_facing_right(double angle);
int     ft_board_protect(int Width, int High, int x, int  y);
int     ft_is_a_wall(t_data *data, int x, int y);
int     ft_is_player_inside_wall(t_data *data);
double	ft_normalize_angle(double angle);
int     ft_key_press(int key, void *Param);
int     ft_key_release(int key, void *Param);
void    ft_update_data(t_data *data);
void    ft_update_image(t_data *data);
double  ft_calc_distance(t_data *data, double x, double y);
void    ft_cast_all_rays(t_data *data);
void	ft_get_wall_hit(t_data *data, double Angle);
void    ft_get_horz_hit(t_data *data, double Angle, double *x, double *y);
void    ft_get_virt_hit(t_data *data, double Angle, double *x, double *y);
void	ft_write_projection(t_data *data, int i);
void    ft_write_texture_img(t_data *data);
void	ft_write_mini_map(t_data *data);
void	ft_write_player(t_data *data);
void	ft_write_player_view(t_data *data);
void	ft_write_wall(t_data *data, int i);
void	ft_write_ceiling(t_data *data, int i);
void	ft_write_floor(t_data *data, int i);
void	ft_get_texture_color(t_data *data, int j);
void    ft_write_player_wall_hit(t_data  *data);


#endif
