/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 04:00:30 by ael-maim          #+#    #+#             */
/*   Updated: 2024/11/28 11:06:53 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <mlx.h>
#include <libft.h>
#include <mlx_int.h>
#include <keycodes.h>

#define WIDTH           800
#define HIGH            600

#define CUBE_TILE       256
#define TEXTURE_TILE    256

#define PLAYER_TILE     10
#define FOV             (66 * (PI / 180))
#define WALL_STRIP      1
#define WALL_DISTANCE   (1.5 * CUBE_TILE)
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

// ========================= //

#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define COLOR_RESET "\e[0m"

# define PLAYER_DIR         "NSEW"
# define SUPPORTED_CHARS    "NSEW01\t\n "
# define SUPPORTED_CHARS_BONUS "DNSEW01\t\n "

# define NUM_TEXTURES       5
# define NUM_COLORS         2

# define PLAYER_RADIUS      6
# define MINIMAP_RADIUS     80
# define TILE_SIZE          64

# define DOOR_SYMBOL        'D'

# define SCALE              0.25

# define SCREEN_WIDTH       WIDTH
# define SCREEN_HEIGHT      HIGH

# define MAP_MID_X          (SCREEN_WIDTH / 2)
# define MAP_MID_Y          (SCREEN_HEIGHT / 2)

# define MINIMAP_MID_X      (SCREEN_WIDTH - MINIMAP_RADIUS - 20)
# define MINIMAP_MID_Y      (MINIMAP_RADIUS + 20)

# define LEFT_CLICK         1
# define MIDDLE_CLICK       2
# define RIGHT_CLICK        3
# define SCROLL_UP          4
# define SCROLL_DOWN        5

# define MOUSE_SENSITIVITY  0.01
# define FRAME_DELAY        8

# define ROT_SPEED          0.02
# define MOVE_SPEED         10

// # define ROT_SPEED          0.1
// # define MOVE_SPEED         30

// ========================= //

typedef struct s_minimap
{

    double start_x;
    double start_y;
		
    double end_x; 
    double end_y;
}   t_minimap;

typedef struct s_map
{
    char    **map;
    int     map_height;
    int     map_width;
    int     map_start;
    int     *map_line_len;
    
    char    *no_texture_path;
    char    *so_texture_path;
    char    *we_texture_path;
    char    *ea_texture_path;

    int     floor_color;
    int     ceiling_color;
}   t_map;

// ======================== //

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

typedef struct s_player
{
    double      dir_x;
    double      dir_y;
    double      player_x;
    double      player_y;
    void        *current_img;
    t_image     *frames;
    int         frames_num;
    char        *frames_path;
}   t_player;

typedef struct  s_data
{
    int             i;

    unsigned short  img_width;
    unsigned short  img_height;
    unsigned short  row;
    unsigned short  col;

    void            *mlx_ptr;
    void            *win_ptr;
    
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

    t_door          *door;
    int             n_door;
    int             door_index;
    int             flag;

    double          x_player;
    double          y_player;
    int             turn_direction;
    int             walk_direction;
    int             strafe_direction;
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
    int             start_player_x;
    int             start_player_y;
    int             player_offset;

    // ================== //

    t_map       map;
    double      scale;
    int         minimap_radius;
    int         minimap_x_center;
    int         minimap_y_center;
    int         clicks;
    int         player_radius;
    double      player_x;
    double      player_y;
    int16_t     player_dir;

    char        *no_texture_path;
    char        *so_texture_path;
    char        *we_texture_path;
    char        *ea_texture_path;
    char        *dr_texture_path;
    
    t_image     *textures[NUM_TEXTURES];
    t_player    player;
    int         shoot;
    int         frames_num;
    int         frame_counter;
	int         frame;
    // t_image		*img;

    int         mouse_x;
    int         mouse_y;
	double      sensitivity;

    // t_minimap   minimap;

	double	dist_x;
	double	dist_y;
	double	y_increment;
    double	x_increment;

    // int         doors_num;
}   t_data;


int     init_data(t_data *data, int ac, char **av);
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
void    ft_write_texture_img(t_data *data, char *path);
void	ft_write_mini_map(t_data *data);
void	ft_write_player(t_data *data);
void	ft_write_player_view(t_data *data);
void	ft_write_wall(t_data *data, int i);
void	ft_write_ceiling(t_data *data, int i, int color);
void	ft_write_floor(t_data *data, int i, int color);
void	ft_get_texture_color(t_data *data, int j);
void    ft_write_player_wall_hit(t_data  *data);
// void    ft_init_door(t_data *data);
int     ft_get_door_index(t_data *data, int x, int y);


void    draw_minimap(t_data *data);
int     parse_map(t_data *data, int ac, char **av);
int     shade_walls(int color ,double distance);
int     shade_walls(int color ,double distance);
void    render_sprites(t_data *data);
void    init_player_sprites(t_data *data, char *dir_path, int frames_num);
void    print_error (char *error_str, char *file, int line);
int     mouse_events(int button, int x, int y, t_data *data);
void    mouse_hooks(t_data *data);
void	free_array(char **arr);

#endif
