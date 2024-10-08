/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:04:03 by aelkheta          #+#    #+#             */
/*   Updated: 2024/10/08 13:23:52 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>             // just for debugging
# include <string.h>
# include <sys/time.h>
# include <../libraries/libft/libft.h>

# define SCREEN_WIDTH   800
# define SCREEN_HEIGHT  600

# define ESC_KEY        65307
# define U_KEY          65362
# define D_KEY          65364
# define R_KEY          65363
# define L_KEY          65361

# define RAY_LENGHT     500

# define TILE_SIZE      32      // the cell grid size

# define MOVE_SPEED     0.2     // player speed
# define ROT_SPEED      0.05    // Rotation speed (in radians)

# define MAP_WIDTH      9       // just an example
# define MAP_HEIGHT     9       // just an example

typedef struct s_image
{
    void *img_ptr;
    void *img_data;
    int bits_per_pixel;
    int size_line;
    int endian;
}   t_image;

typedef struct {
    void *mlx_ptr;
    void *win_ptr;

    char **map;

    double dir_x;
    double dir_y;

    double camera_x;

    double plane_x;
    double plane_y;

    double player_x;
    double player_y;

    int map_x;
    int map_y;

    double ray_dir_x;
    double ray_dir_y;

    t_image *image;
} t_data;

# endif // CUB3D_H
