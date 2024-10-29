/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:04:03 by aelkheta          #+#    #+#             */
/*   Updated: 2024/10/25 11:44:05 by aelkheta         ###   ########.fr       */
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
#include <fcntl.h>              //  for open syscall

# define PI 3.14159265358979323846

# define SCREEN_WIDTH   800
# define SCREEN_HEIGHT  600

# define RAY_LENGHT     500

// # define MAP_WIDTH      30      // just an example
// # define MAP_HEIGHT     9       // just an example

# define CLR_SKY        0x69c9fa
# define CLR_FLR        0xc28951

# define CLR_EAW        0xcacaca
# define CLR_SAN        0xf5f5f5

# define TILE_SIZE      16      // the cell grid size

# define CENTER (SCREEN_WIDTH / 2 - MAP_WIDTH * TILE_SIZE / 2)


#ifdef __APPLE__
    // macOS keycodes
    # define ESC_KEY        53
    # define U_KEY          126
    # define D_KEY          125
    # define R_KEY          124
    # define L_KEY          123
    
    # define MOVE_SPEED     0.09     // player speed
    # define ROT_SPEED      0.06     // Rotation speed (in radians)

#elif __linux__
    // Linux (X11) keycodes
    # define ESC_KEY        65307
    # define U_KEY          65362
    # define D_KEY          65364
    # define R_KEY          65363
    # define L_KEY          65361
    
    # define MOVE_SPEED     0.04     // player speed
    # define ROT_SPEED      0.02     // Rotation speed (in radians)
#else
    #error "Unsupported platform"
#endif

// # define CLR_SKY        0x89CFF3
// # define CLR_FLR        0xB99470

// # define CLR_EAW        0xB5B5B5
// # define CLR_SAN        0xF5F5F5

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

typedef struct s_map
{
    char    **map;
    int     map_height;
    int     map_width;
}   t_map;

typedef struct {
    void    *mlx_ptr;
    void    *win_ptr;

    char    **map;
    int     map_height;
    int     map_width;

    double  dir_x;   // player direction x position
    double  dir_y;   // player direction y position

    double  camera_x;

    double  plane_x;
    double  plane_y;
    char    player_dir;
    double  player_x;
    double  player_y;

    int     map_x;      // player grid position
    int     map_y;      // player grid position

    double  ray_dir_x;
    double  ray_dir_y;

    double  side_dist_x;
    double  side_dist_y;
    double  delta_dist_x;
    double  delta_dist_y;

    int     step_x;
    int     step_y;
    
    short   rotate_right;
    short   rotate_left;
    short   move_forward;
    short   move_backward;
    
    t_image *image;

	int     hit;
	int     side;
	int     color;

	double  perp_wall_dist;
	int     line_height;
	int     draw_start;
	int     draw_end;

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

// parsing time

int         parse_map(t_data *data, int ac, char **av);
void        std_error(char *error);

# endif // CUB3D_H
