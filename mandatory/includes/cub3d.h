/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:04:03 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/12 17:30:03 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
# define CUB3D_H

// # include "../libraries/minilibx-linux/mlx.h"
# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>             // just for debugging
# include <string.h>
# include <sys/time.h>
# include <../libraries/libft/libft.h>
# include <fcntl.h>              //  for open syscall
# include <stdbool.h>
# include <macros.h>

// uint16_t lala;
// int64_t tata;
// uint_least64_t fafa;
// # define and &&

#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define COLOR_RESET "\e[0m"

typedef struct s_image
{
    void    *img_ptr;
    void    *img_data;
    int     bits_per_pixel;
    int     size_line;
    int     endian;
}   t_image;

typedef struct s_player
{
    double  dir_x;   // player direction x position
    double  dir_y;   // player direction y position
    
    double  player_x;
    double  player_y;
}   t_player;

typedef struct s_ray
{
    double  ray_dir_x;
    double  ray_dir_y;
}   t_ray;

typedef struct s_map
{
    char    **map;
    int     map_height;
    int     map_width;
    int     map_start;
    
    char    *no_texture_path;
    char    *so_texture_path;
    char    *we_texture_path;
    char    *ea_texture_path;

    int     floor_color;
    int     ceiling_color;
}   t_map;

typedef struct s_mlx
{
    void        *mlx_ptr;
    void        *win_ptr;
}   t_mlx;

typedef struct {
    void        *mlx_ptr;
    void        *win_ptr;

    t_map       map_;
    char        **map;
    int         map_height;
    int         map_width;
    int         *map_line_len;

    double      dir_x;   // player direction x position
    double      dir_y;   // player direction y position

    double      camera_x;

    double      plane_x;
    double      plane_y;
    char        player_dir;
    double      player_x;
    double      player_y;

    int         map_x;      // player grid position
    int         map_y;      // player grid position

    double      ray_dir_x;
    double      ray_dir_y;

    double      side_dist_x;
    double      side_dist_y;
    double      delta_dist_x;
    double      delta_dist_y;

    int         step_x;
    int         step_y;
    
    int16_t     rotate_right;
    int16_t     rotate_left;
    int16_t     move_forward;
    int16_t     move_backward;
    int16_t     move_right;
    int16_t     move_left;
    
    t_image     *image;

	int         hit;
	int         side;
	int         color;

	double      perp_wall_dist;
	int         line_height;
	int         draw_start;
	int         draw_end;

    char        *no_texture_path;
    char        *so_texture_path;
    char        *we_texture_path;
    char        *ea_texture_path;

    int         map_start;
    // uint32_t    floor_color;
    // uint32_t    ceiling_color;
    int64_t     floor_color;
    int64_t     ceiling_color;
    // int         sky_color;

    double      scale;
    int         minimap_radius;
    int         minimap_x_center;
    int         minimap_y_center;
    double      move_speed;
    double      rot_speed;
    int         clicks;
    int         player_radius;

} t_data;

// functions signature

/// @brief this function setting a pixel in an image with the cordinates given.
/// @param image t_image *image: A pointer to a struct that holds the image information. This struct typically includes:
/// @param img_data: A pointer to the raw image data (the actual pixel array).
/// @param size_line: The number of bytes that represent a single row (or "line") of pixels in the image.
/// @param bits_per_pixel: The number of bits used to represent a single pixel (often 32 bits, or 4 bytes).
/// @param endian: Information about the byte order (not used directly in this function).
/// @param x is the horizontal position of the coordinates of the pixel you want to modify.
/// @param y is the vertical position of the coordinates of the pixel you want to modify.
/// @param color The color value (in ARGB format) that will be applied to the specified pixel. This is typically a 32-bit integer where each byte represents a different color component (Alpha, Red, Green, Blue).
void        put_pixel_in_img(t_image *image, int x, int y, int color);

/// @brief Create a new image.
/// @param data the struct that hold all what we need.
/// @return return an allocated pointer to the image created.
t_image     *create_image(t_data *data);

void        raycasting(t_data *data);

void        init_game(t_data *data);
int         init_map(t_data *data);

void        free_array(char **arr);
int         key_press(int keycode, t_data *data);
int         key_release(int keycode, t_data *data);

int         game_loop(t_data *data);
int         destroy_notify(t_data *data);

void	    start_game(t_data *data);
void        update_player(t_data *data);

void        draw_mini_map(t_data *data);

int         mouse_events(int button, int x, int y, t_data *data);

// parsing time

int         parse_map(t_data *data, int ac, char **av);
void        print_error (char *error_str, char *file, int line);
void        free_map(char **map);
void        clean_up(t_data *data);

// void        std_error(char *error);

# endif // CUB3D_H