/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:27:39 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/01 10:29:49 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# define PI                 3.14159265358979323846

# define SCREEN_WIDTH       800
# define SCREEN_HEIGHT      600

# define RAY_LENGHT         500

# define MAP_WIDTH          30      // just an example
# define MAP_HEIGHT         30      // just an example

# define CLR_SKY            0x69c9fa
# define CLR_FLR            0xc28951

# define CLR_EAW            0xcacaca
# define CLR_SAN            0xf5f5f5

# define TILE_SIZE          32      // the cell grid size

# define CENTER             (SCREEN_WIDTH / 2 - MAP_WIDTH * TILE_SIZE / 2)

# define PLAYER_RADIUS      6
# define MINIMAP_RADIUS     80

# define SCALE              0.25

# define MAP_MID_X          (SCREEN_WIDTH / 2)
# define MAP_MID_Y          (SCREEN_HEIGHT / 2)

# define MINIMAP_MID_X      (SCREEN_WIDTH - MINIMAP_RADIUS - 20)
# define MINIMAP_MID_Y      (MINIMAP_RADIUS + 20)

# define LEFT_CLICK         1
# define MIDDLE_CLICK       2
# define RIGHT_CLICK        3
# define SCROLL_UP          4
# define SCROLL_DOWN        5

# define PLAYER_DIR         "NSEW"
# define SUPPORTED_CHARS    "NSEW01\t\n "

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
    
    // # define MOVE_SPEED     0.06    // player speed
    // # define ROT_SPEED      0.03    // Rotation speed (in radians)

    # define MOVE_SPEED     0.2    // player speed
    # define ROT_SPEED      0.08    // Rotation speed (in radians)

#else
    #error "Unsupported platform"
#endif

// # define CLR_SKY        0x89CFF3
// # define CLR_FLR        0xB99470

// # define CLR_EAW        0xB5B5B5
// # define CLR_SAN        0xF5F5F5