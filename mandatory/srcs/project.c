// #include <mlx.h>
# include "../includes/mlx.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "../libraries/libft/libft.h"
#include <fcntl.h>
#include <stdbool.h>

#ifdef __linux__
    #include "../includes/keycodes_linux.h"
#endif
// #include "../includes/macros.h"

# define PI                 3.14159265358979323846

# define SCREEN_WIDTH       800
# define SCREEN_HEIGHT      600

// # define SCREEN_WIDTH       1920
// # define SCREEN_HEIGHT      1080

# define RAY_LENGHT         500

// # define MAP_WIDTH          30      // just an example
// # define MAP_HEIGHT         30       // just an example

# define CLR_SKY            0x69c9fa
# define CLR_FLR            0xc28951

# define CLR_EAW            0xcacaca
# define CLR_SAN            0xf5f5f5

# define TILE_SIZE          32      // the cell grid size

// # define CENTER             (SCREEN_WIDTH / 2 - MAP_WIDTH * TILE_SIZE / 2)

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

#define TEXTURE_WIDTH       64
#define TEXTURE_HEIGHT      64
#define NUM_TEXTURES        4

# ifdef __APPLE__
    // macOS keycodes
    # define ESC_KEY        53
    # define U_KEY          126
    # define D_KEY          125
    # define R_KEY          124
    # define L_KEY          123
    
    # define MOVE_SPEED     0.09     // player speed
    # define ROT_SPEED      0.06     // Rotation speed (in radians)

# elif __linux__
    // Linux (X11) keycodes
    // # define ESC_KEY     65307
    // # define UP_KEY      65362
    // # define DOWN_KEY    65364
    // # define RIGHT_KEY   65363
    // # define LEFT_KEY    65361
    
    // # define MOVE_SPEED     0.08    // player speed
    // # define ROT_SPEED      0.06    // Rotation speed (in radians)

    # define MOVE_SPEED     0.008    // player speed
    # define ROT_SPEED      0.004    // Rotation speed (in radians)

# else
    #error "Unsupported platform"
# endif

typedef struct s_image
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
    // t_image     *frames[2];
    t_image     *frames;
}   t_player;

typedef struct s_map
{
    char    **map;
    int     map_height;
    int     map_width;
    int     map_start;
    int     *line_len;
    // char    *map_path;
}   t_map;

typedef struct s_texture {
    void    *img_ptr;
    int     *data;
    int     width;
    int     height;
    int     bits_per_pixel;
    int     size_line;
    int     endian;
} t_texture;

typedef struct s_data {
    void    *mlx_ptr;
    void    *win_ptr;

    t_map   map;

    double  dir_x;
    double  dir_y;
    double  camera_x;
    double  plane_x;
    double  plane_y;
    char    player_dir;
    double  player_x;
    double  player_y;

    int     map_x;
    int     map_y;

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

    int     hit;
    int     side;
    int     color;

    t_image *image;

    double  perp_wall_dist;
    int     line_height;
    int     draw_start;
    int     draw_end;

    char    *no_texture_path;
    char    *so_texture_path;
    char    *we_texture_path;
    char    *ea_texture_path;

    int     floor_color;
    int     ceiling_color;

    double  scale;
    int     minimap_radius;
    int     minimap_x_center;
    int     minimap_y_center;
    double  move_speed;
    double  rot_speed;
    int     clicks;
    int     player_radius;
    
    // char    *textures_path[NUM_TEXTURES];
    t_texture   *textures[NUM_TEXTURES];

    // t_texture    *textures[4];  // NO, SO, WE, EA
    double      wall_x;        // Where exactly the wall was hit
    int         tex_x;         // X coordinate on the texture
    int         tex_y;         // Y coordinate on the texture
    double      step;          // How much to increase the texture coordinate per screen pixel
    double      tex_pos;       // Starting texture coordinate

    t_player    player;

    int         shoot;
} t_data;

void    put_pixel_in_img(t_image *image, int x, int y, int color)
{
    int pixel_index;

    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
        return;

    pixel_index = (y * image->size_line) + (x * (image->bits_per_pixel / 8));
    *(int *)(image->img_data + pixel_index) = color;
}

t_image *create_image(t_data *data)
{
    t_image *img;

    img = malloc(sizeof(t_image));
    if (!img)
        return (NULL);
    img->img_ptr = mlx_new_image(data->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!img->img_ptr)
    {
        free(img);
        return (NULL);
    }
    img->img_data = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel,
            &img->size_line, &img->endian);
    if (!img->img_data)
    {
        mlx_destroy_image(data->mlx_ptr, img->img_ptr);
        free(img);
        return (NULL);
    }
    return (img);
}

void free_map(char **map)
{
    int i;

    i = -1;
    if (!map)
        return;
    while (map[++i])
        free(map[i]);
    free(map);
}

// int read_map(t_data *data, char *map_path)
// {
//     int     i;
//     int     fd;
//     char    *line;
//     char    **lines;

//     fd = open(map_path, O_RDONLY);
//     if (fd == -1)
//         return (printf("FILE: %s, LINE: %d\n", __FILE__, __LINE__), perror(map_path), 0);
    
//     i = 0;
//     line = get_next_line(fd);
//     if (!line)
//         return (close(fd), 0);
    
//     data->map.map_width = ft_strlen(line) - 1;
//     while (line)
//     {
//         ++i;
//         printf("%s", line);  // For debug
//         free(line);
//         line = get_next_line(fd);
//     }
//     data->map.map_height = i;
//     close(fd);

//     fd = open(map_path, O_RDONLY);
//     if (fd == -1)
//         return (0);
    
//     lines = (char **)malloc(sizeof(char *) * (data->map.map_height + 1));
//     if (!lines)
//         return (close(fd), 0);
    
//     // Read and store each line
//     i = 0;
//     while (i < data->map.map_height)
//     {
//         lines[i] = get_next_line(fd);
//         if (!lines[i])
//         {
//             while (--i >= 0)
//                 free(lines[i]);
//             free(lines);
//             return (close(fd), 0);
//         }
//         i++;
//     }
//     lines[i] = NULL;
    
//     close(fd);
//     data->map.map = lines;
//     return (1);
// }


int read_map(t_data *data, char *map_path)
{
    int     i;
    int     fd;
    char    *line;
    char    **lines;
    size_t  width = 0;

    fd = open(map_path, O_RDONLY);
    if (fd == -1)
        return (printf("FILE: %s, LINE: %d\n", __FILE__, __LINE__), perror(map_path), 0);
    
    i = 0;
    line = get_next_line(fd);
    if (!line)
        return (close(fd), 0);
    
    // Find the maximum width among all lines
    while (line)
    {
        size_t current_width = ft_strlen(line) - 1;  // -1 for newline
        width = (current_width > width) ? current_width : width;
        ++i;
        free(line);
        line = get_next_line(fd);
    }
    data->map.map_width = width;
    data->map.map_height = i;
    close(fd);

    // Reopen file to read the map
    fd = open(map_path, O_RDONLY);
    if (fd == -1)
        return (0);
    
    lines = (char **)malloc(sizeof(char *) * (data->map.map_height + 1));
    if (!lines)
        return (close(fd), 0);
    
    i = 0;
    while (i < data->map.map_height)
    {
        lines[i] = get_next_line(fd);
        if (!lines[i])
        {
            while (--i >= 0)
                free(lines[i]);
            free(lines);
            return (close(fd), 0);
        }
        i++;
    }
    lines[i] = NULL;
    close(fd);
    data->map.map = lines;
    return (1);
}

int init_map(t_data *data, char *map_path)
{    
    if (!read_map(data, map_path))
        return (1);

    return (0);
}

int init_player_direction(t_data *data)
{
    data->player_dir = 'S';  // Set default direction
    
    if (!data->player_dir)
        return (1);

    if (data->player_dir == 'N')
    {
        data->dir_x = 0;
        data->dir_y = -1;
        data->plane_x = 0.66;
        data->plane_y = 0;
    }
    else if (data->player_dir == 'S')
    {
        data->dir_x = 0;
        data->dir_y = 1;
        data->plane_x = -0.66;
        data->plane_y = 0;
    }
    else if (data->player_dir == 'W')
    {
        data->dir_x = -1;
        data->dir_y = 0;
        data->plane_x = 0;
        data->plane_y = 0.66;
    }
    else if (data->player_dir == 'E')
    {
        data->dir_x = 1;
        data->dir_y = 0;
        data->plane_x = 0;
        data->plane_y = -0.66;
    }
    return (0);
}

// t_texture *load_texture(t_data *data, t_texture *texture, char *path)
int load_texture(t_data *data, t_texture *texture, char *path)
{
    if (!texture || !path || !data->mlx_ptr)
        return (0);

    texture->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, path, &texture->width, &texture->height);
    if (!texture->img_ptr)
    {
        printf("Error: mlx_xpm_file_to_image: fail\n");
        return (0);
    }

    texture->data = (int *)mlx_get_data_addr(texture->img_ptr, &texture->bits_per_pixel, &texture->size_line, &texture->endian);
    if (!texture->data)
    {
        mlx_destroy_image(data->mlx_ptr, texture->img_ptr);
        return (0);
    }

    if (texture->width != TEXTURE_WIDTH || texture->height != TEXTURE_HEIGHT)
    {
        mlx_destroy_image(data->mlx_ptr, texture->img_ptr);
        return (0);
    }

    return (1);
}

void free_textures(t_data *data, int up_to)
{
    int i = -1;
    while (++i < up_to)
    {
        if (data->textures[i])
        {
            if (data->textures[i]->img_ptr)
                mlx_destroy_image(data->mlx_ptr, data->textures[i]->img_ptr);
            free(data->textures[i]);
            data->textures[i] = NULL;
        }
    }
}

int init_textures(t_data *data)
{
    if (!data || !data->mlx_ptr)
        return (0);

    int i = -1;
    while (++i < NUM_TEXTURES)
        data->textures[i] = NULL;

    char *texture_paths[NUM_TEXTURES] = {
        data->no_texture_path,  // North
        data->so_texture_path,  // South
        data->we_texture_path,  // West
        data->ea_texture_path   // East
    };

    i = -1;
    while (++i < NUM_TEXTURES)
    {
        data->textures[i] = (t_texture *)malloc(sizeof(t_texture));
        if (!data->textures[i])
        {
            free_textures(data, i);
            return (0);
        }

        data->textures[i]->img_ptr = NULL;
        data->textures[i]->data = NULL;

        if (!load_texture(data, data->textures[i], texture_paths[i]))
        {
            free_textures(data, i + 1);
            return (0);
        }
    }

    return (1);
}

void init_player_sprites(t_data *data)
{
    data->player.frames = malloc(sizeof(t_image) * 22);
    
    // data->player.frames[0].img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/sprites/w0_a.xpm", &data->player.frames[0].width, &data->player.frames[0].height);
    // data->player.frames[0].img_data = mlx_get_data_addr(data->player.frames[0].img_ptr, &data->player.frames[0].bits_per_pixel, &data->player.frames[0].size_line, &data->player.frames[0].endian);
    // data->player.frames[1].img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/sprites/w0_b.xpm", &data->player.frames[1].width, &data->player.frames[1].height);
    // data->player.frames[1].img_data = mlx_get_data_addr(data->player.frames[1].img_ptr, &data->player.frames[1].bits_per_pixel, &data->player.frames[1].size_line, &data->player.frames[1].endian);
    int i = -1;
    while(++i < 22)
    {
        char *sprite_index = ft_itoa(i);
        char *extension = ft_strdup(".xpm");
        char *str = ft_strjoin(sprite_index, extension);
        char *sprite_path = ft_strjoin(ft_strdup("./textures/sprites/LOgTFqa/"), str);

        printf("%s\n", sprite_path);
        free(str);
        free(extension);
        data->player.frames[i].img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, sprite_path, &data->player.frames[i].width, &data->player.frames[i].height);
        data->player.frames[i].img_data = mlx_get_data_addr(data->player.frames[i].img_ptr, &data->player.frames[i].bits_per_pixel, &data->player.frames[i].size_line, &data->player.frames[i].endian);    
    }
    
    // data->player.frames[1].img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/sprites/LOgTFqa/1.xpm", &data->player.frames[1].width, &data->player.frames[1].height);
    // data->player.frames[1].img_data = mlx_get_data_addr(data->player.frames[1].img_ptr, &data->player.frames[1].bits_per_pixel, &data->player.frames[1].size_line, &data->player.frames[1].endian);

    // data->player.frames[2].img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/sprites/LOgTFqa/2.xpm", &data->player.frames[2].width, &data->player.frames[2].height);
    // data->player.frames[2].img_data = mlx_get_data_addr(data->player.frames[2].img_ptr, &data->player.frames[2].bits_per_pixel, &data->player.frames[2].size_line, &data->player.frames[2].endian);
    
    // data->player.frames[3].img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/sprites/LOgTFqa/3.xpm", &data->player.frames[3].width, &data->player.frames[3].height);
    // data->player.frames[3].img_data = mlx_get_data_addr(data->player.frames[3].img_ptr, &data->player.frames[3].bits_per_pixel, &data->player.frames[3].size_line, &data->player.frames[3].endian);
}

int init_game(t_data *data, char *map_path)
{
    data->scale             =   SCALE;
    data->rot_speed         =   ROT_SPEED;
    data->move_speed        =   MOVE_SPEED;
    data->player_radius     =   PLAYER_RADIUS;
    data->minimap_radius    =   MINIMAP_RADIUS;
    data->minimap_x_center  =   MINIMAP_MID_X;
    data->minimap_y_center  =   MINIMAP_MID_Y;

    // data->player.frames[0] = create_image(data);
    // data->player.frames[1] = create_image(data);

    // data->no_texture_path   =   ft_strdup("../textures/north_wall.xpm");
    // data->so_texture_path   =   ft_strdup("../textures/south_wall.xpm");
    // data->ea_texture_path   =   ft_strdup("../textures/east_wall.xpm");
    // data->we_texture_path   =   ft_strdup("../textures/west_wall.xpm");

    data->player_x          =    2.0;
    data->player_y          =    2.0;

    if (init_player_direction(data))
        return (1);

    if (init_map(data, map_path) != 0)
        return (1);

    data->image = create_image(data);
    if (!data->image)
        return (1);
    
    init_player_sprites(data);

    // if (!init_textures(data))
    //     return (1);

    return (0);
}

// void safe_free(void *ptr)
// {
//     if (ptr)
//         free(ptr);
    // ptr = NULL;
// }

void clean_up(t_data *data)
{
    if (!data)
        return;
        
    if (data->no_texture_path)
        free(data->no_texture_path);
    if (data->so_texture_path)
        free(data->so_texture_path);
    if (data->we_texture_path)
        free(data->we_texture_path);
    if (data->ea_texture_path)
        free(data->ea_texture_path);
    
    if (data->image)
    {
        if (data->image->img_ptr && data->mlx_ptr)
            mlx_destroy_image(data->mlx_ptr, data->image->img_ptr);
        free(data->image);
    }

    // mlx_destroy_image(data->mlx_ptr, data->player.frames[0]->img_ptr);
    // free(data->player.frames[0]);
    // mlx_destroy_image(data->mlx_ptr, data->player.frames[1]->img_ptr);
    // free(data->player.frames[1]);
    
    if (data->win_ptr && data->mlx_ptr)
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);

    #ifdef __linux__
    if (data->mlx_ptr)
    {
        mlx_destroy_display(data->mlx_ptr);
        free(data->mlx_ptr);
    }
    #endif

    if (data->map.map)
        free_map(data->map.map);

    free_textures(data, NUM_TEXTURES);
}

int key_press(int keycode, t_data *data)
{
    printf("keycode: %d\n", keycode);

    if (keycode == ESC_KEY)
    {
        clean_up(data);
        exit(0);
    }
    else if (keycode == 'w' || keycode == UP_KEY)
        data->move_forward = 1;
    else if (keycode == 's' || keycode == DOWN_KEY)
        data->move_backward = 1;
    else if (keycode == 'a' || keycode == LEFT_KEY)
        data->rotate_left = 1;
    else if (keycode == 'd' || keycode == RIGHT_KEY)
        data->rotate_right = 1;
    else if (keycode == SPACE_KEY)
        data->shoot = 1;
    return (0);
}

int key_release(int keycode, t_data *data)
{
    if (keycode == 'w' || keycode == UP_KEY)
        data->move_forward = 0;
    else if (keycode == 's' || keycode == DOWN_KEY)
        data->move_backward = 0;
    else if (keycode == 'a' || keycode == LEFT_KEY)
        data->rotate_left = 0;
    else if (keycode == 'd' || keycode == RIGHT_KEY)
        data->rotate_right = 0;
    return (0);
}

int check_click_space(t_data *data, int x, int y)
{
    int dx = x - data->minimap_x_center;
    int dy = y - data->minimap_y_center;
    double distance = sqrt(dx * dx + dy * dy);
    return (distance <= data->minimap_radius);
}

int mouse_events(int button, int x, int y, t_data *data)
{
    if (button == LEFT_CLICK && check_click_space(data, x, y))
    {
        data->clicks++;
        if (data->clicks % 2 != 0)
        {
            data->scale = SCALE * 2;
            data->rot_speed = ROT_SPEED * 2;
            data->move_speed = MOVE_SPEED * 2;
            data->player_radius = PLAYER_RADIUS;
            data->minimap_radius = MINIMAP_RADIUS * 4;
            data->minimap_x_center = MAP_MID_X;
            data->minimap_y_center = MAP_MID_Y;
        }
        else
        {
            data->scale = SCALE;
            data->rot_speed = ROT_SPEED;
            data->move_speed = MOVE_SPEED;
            data->player_radius = PLAYER_RADIUS;
            data->minimap_radius = MINIMAP_RADIUS;
            data->minimap_x_center = MINIMAP_MID_X;
            data->minimap_y_center = MINIMAP_MID_Y;
        }
    }
    return (0);
}

void draw_vert_line(t_image *image, int x, int draw_start, int draw_end, int color)
{
    int y;

    y = draw_start - 1;
    while (++y < draw_end)
        put_pixel_in_img(image, x, y, color);
}

void dda_algorithm(t_data *data)
{
    data->hit = 0;
    while (data->hit == 0)
    {
        if (data->side_dist_x < data->side_dist_y)
        {
            data->side_dist_x += data->delta_dist_x;
            data->map_x += data->step_x;
            data->side = 0;
        }
        else
        {
            data->side_dist_y += data->delta_dist_y;
            data->map_y += data->step_y;
            data->side = 1;
        }
        
        if (data->map_x < 0 || data->map_x >= data->map.map_width || 
            data->map_y < 0 || data->map_y >= data->map.map_height)
            break;
            
        if (data->map.map[data->map_y][data->map_x] == '1')
            data->hit = 1;
    }
}

void draw_vert_cols(t_data *data, int x)
{
    int color = 0xFFFFFF;

    if (data->side == 0)
        data->perp_wall_dist = data->side_dist_x - data->delta_dist_x;
    else
        data->perp_wall_dist = data->side_dist_y - data->delta_dist_y;

    color = (data->side == 0) ? CLR_EAW : CLR_SAN;

    data->line_height = (int)(SCREEN_HEIGHT / data->perp_wall_dist);
    data->draw_start = -data->line_height / 2 + SCREEN_HEIGHT / 2;
    data->draw_start = (data->draw_start < 0) ? 0 : data->draw_start;

    data->draw_end = data->line_height / 2 + SCREEN_HEIGHT / 2;
    data->draw_end = (data->draw_end >= SCREEN_HEIGHT) ? SCREEN_HEIGHT - 1 : data->draw_end;

    draw_vert_line(data->image, x, 0, data->draw_start, CLR_SKY);
    draw_vert_line(data->image, x, data->draw_start, data->draw_end, color);
    draw_vert_line(data->image, x, data->draw_end, SCREEN_HEIGHT, CLR_FLR);
}

void calculate_side_dist_x_y(t_data *data)
{
    if (data->ray_dir_x < 0)
    {
        data->step_x = -1;
        data->side_dist_x = (data->player_x - data->map_x) * data->delta_dist_x;
    }
    else
    {
        data->step_x = 1;
        data->side_dist_x = (data->map_x + 1.0 - data->player_x) * data->delta_dist_x;
    }
    
    if (data->ray_dir_y < 0)
    {
        data->step_y = -1;
        data->side_dist_y = (data->player_y - data->map_y) * data->delta_dist_y;
    }
    else
    {
        data->step_y = 1;
        data->side_dist_y = (data->map_y + 1.0 - data->player_y) * data->delta_dist_y;
    }
}

void raycasting(t_data *data)
{
    int x;
    
    x = -1;
    while (++x < SCREEN_WIDTH)
    {
        data->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
        data->ray_dir_x = data->dir_x + data->plane_x * data->camera_x;
        data->ray_dir_y = data->dir_y + data->plane_y * data->camera_x;

        // Calculate the current map square the ray is in
        data->map_x = (int)data->player_x;
        data->map_y = (int)data->player_y;

        // Calculate delta_dist based on ray direction
        data->delta_dist_x = fabs(1 / data->ray_dir_x);
        data->delta_dist_y = fabs(1 / data->ray_dir_y);

        // Calculate step and initial side_dist
        // calculate_side_dist_x_y(data);
        if (data->ray_dir_x < 0)
        {
            data->step_x = -1;
            data->side_dist_x = (data->player_x - data->map_x) * data->delta_dist_x;
        }
        else
        {
            data->step_x = 1;
            data->side_dist_x = (data->map_x + 1.0 - data->player_x) * data->delta_dist_x;
        }
        
        if (data->ray_dir_y < 0)
        {
            data->step_y = -1;
            data->side_dist_y = (data->player_y - data->map_y) * data->delta_dist_y;
        }
        else
        {
            data->step_y = 1;
            data->side_dist_y = (data->map_y + 1.0 - data->player_y) * data->delta_dist_y;
        }

        // Perform DDA algorithm
        dda_algorithm(data);

        // Draw the vertical wall strips
        // draw_vert_cols(data, x);
        int color = 0xFFFFFF;

        if (data->side == 0)
            data->perp_wall_dist = data->side_dist_x - data->delta_dist_x;
        else
            data->perp_wall_dist = data->side_dist_y - data->delta_dist_y;

        color = (data->side == 0) ? CLR_EAW : CLR_SAN;

        data->line_height = (int)(SCREEN_HEIGHT / data->perp_wall_dist);
        data->draw_start = -data->line_height / 2 + SCREEN_HEIGHT / 2;
        data->draw_start = (data->draw_start < 0) ? 0 : data->draw_start;

        data->draw_end = data->line_height / 2 + SCREEN_HEIGHT / 2;
        data->draw_end = (data->draw_end >= SCREEN_HEIGHT) ? SCREEN_HEIGHT - 1 : data->draw_end;

        draw_vert_line(data->image, x, 0, data->draw_start, CLR_SKY);
        draw_vert_line(data->image, x, data->draw_start, data->draw_end, color);
        draw_vert_line(data->image, x, data->draw_end, SCREEN_HEIGHT, CLR_FLR);
    }
}


// static int get_texture_number(t_data *data)
// {
//     if (data->side == 0)
//         return (data->ray_dir_x < 0) ? 2 : 3; // West or East
//     return (data->ray_dir_y < 0) ? 0 : 1;     // North or South
// }

// // Calculate wall texture coordinates
// static void calculate_wall_texture(t_data *data)
// {
//     // Calculate wall X coordinate (where the ray hit the wall)
//     if (data->side == 0)
//         data->wall_x = data->player_y + data->perp_wall_dist * data->ray_dir_y;
//     else
//         data->wall_x = data->player_x + data->perp_wall_dist * data->ray_dir_x;
//     data->wall_x -= floor(data->wall_x);

//     // Calculate X coordinate on texture
//     data->tex_x = (int)(data->wall_x * TEXTURE_WIDTH);
//     if (data->side == 0 && data->ray_dir_x > 0)
//         data->tex_x = TEXTURE_WIDTH - data->tex_x - 1;
//     if (data->side == 1 && data->ray_dir_y < 0)
//         data->tex_x = TEXTURE_WIDTH - data->tex_x - 1;
// }

// // Draw a vertical textured wall stripe
// static void draw_wall_stripe(t_data *data, int x, int tex_num)
// {
//     double step = 1.0 * TEXTURE_HEIGHT / data->line_height;
//     double tex_pos = (data->draw_start - SCREEN_HEIGHT / 2 + data->line_height / 2) * step;

//     for (int y = data->draw_start; y < data->draw_end; y++)
//     {
//         data->tex_y = (int)tex_pos & (TEXTURE_HEIGHT - 1);
//         tex_pos += step;

//         int color = data->textures[tex_num]->data[TEXTURE_HEIGHT * data->tex_y + data->tex_x];
        
//         // Make color darker for y-sides (east-west walls)
//         if (data->side == 1)
//             color = (color >> 1) & 8355711;

//         put_pixel_in_img(data->image, x, y, color);
//     }
// }

// #define MAX(a, b) ((a) > (b) ? (a) : (b))
// #define MIN(a, b) ((a) < (b) ? (a) : (b))

// void raycasting(t_data *data)
// {
//     for (int x = 0; x < SCREEN_WIDTH; x++)
//     {
//         // Calculate ray position and direction
//         data->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
//         data->ray_dir_x = data->dir_x + data->plane_x * data->camera_x;
//         data->ray_dir_y = data->dir_y + data->plane_y * data->camera_x;

//         // Initialize map position
//         data->map_x = (int)data->player_x;
//         data->map_y = (int)data->player_y;

//         // Calculate distance between rays
//         data->delta_dist_x = fabs(1 / data->ray_dir_x);
//         data->delta_dist_y = fabs(1 / data->ray_dir_y);

//         // Calculate step and initial side distance
//         calculate_side_dist_x_y(data);

//         // Perform DDA to find wall hit
//         dda_algorithm(data);

//         // Calculate perpendicular wall distance to prevent fisheye effect
//         data->perp_wall_dist = (data->side == 0) 
//             ? data->side_dist_x - data->delta_dist_x
//             : data->side_dist_y - data->delta_dist_y;

//         // Calculate wall height and drawing boundaries
//         data->line_height = (int)(SCREEN_HEIGHT / data->perp_wall_dist);
//         data->draw_start = MAX(0, -data->line_height / 2 + SCREEN_HEIGHT / 2);
//         data->draw_end = MIN(SCREEN_HEIGHT - 1, data->line_height / 2 + SCREEN_HEIGHT / 2);

//         // Calculate texture coordinates
//         calculate_wall_texture(data);

//         // Draw ceiling
//         draw_vert_line(data->image, x, 0, data->draw_start, CLR_SKY);

//         // Draw textured wall
//         int tex_num = get_texture_number(data);
//         draw_wall_stripe(data, x, tex_num);

//         // Draw floor
//         draw_vert_line(data->image, x, data->draw_end, SCREEN_HEIGHT, CLR_FLR);
//     }
// }

void rotate_player(t_data *data, double rot_speed)
{
    double old_dir_x;
    double old_plane_x;

    old_dir_x = data->dir_x;
    old_plane_x = data->plane_x;
    
    data->dir_x = data->dir_x * cos(rot_speed) - data->dir_y * sin(rot_speed);
    data->dir_y = old_dir_x * sin(rot_speed) + data->dir_y * cos(rot_speed);
    data->plane_x = data->plane_x * cos(rot_speed) - data->plane_y * sin(rot_speed);
    data->plane_y = old_plane_x * sin(rot_speed) + data->plane_y * cos(rot_speed);
}

void move_player(t_data *data)
{
    if (data->move_forward)
    {
        if (data->map.map[(int)data->player_y]
            [(int)(data->player_x + data->dir_x * data->move_speed)] != '1')
            data->player_x += data->dir_x * data->move_speed;
        if (data->map.map[(int)(data->player_y + data->dir_y * data->move_speed)]
            [(int)data->player_x] != '1')
            data->player_y += data->dir_y * data->move_speed;
    }
    if (data->move_backward)
    {
        if (data->map.map[(int)data->player_y]
            [(int)(data->player_x - data->dir_x * data->move_speed)] != '1')
            data->player_x -= data->dir_x * data->move_speed;
        if (data->map.map[(int)(data->player_y - data->dir_y * data->move_speed)]
            [(int)data->player_x] != '1')
            data->player_y -= data->dir_y * data->move_speed;
    }
    if (data->rotate_right)
        rotate_player(data, data->rot_speed);
    if (data->rotate_left)
        rotate_player(data, -data->rot_speed);
}

void draw_background(t_data *data, t_image *image)
{
    int y = -data->minimap_radius - 1;

	while (++y <= data->minimap_radius)
    {
        int x = -data->minimap_radius - 1;
        while (++x <= data->minimap_radius)
        {
            double distance = sqrt(x * x + y * y);
            if (distance <= data->minimap_radius)
            {
                int screen_x = data->minimap_x_center + x;
                int screen_y = data->minimap_y_center + y;
                put_pixel_in_img(image, screen_x, screen_y, 0x222222);
            }
        }
    }
}

void draw_tile(t_data *data, t_image *image, double x, double y, int color)
{
    int     size;
    double  screen_x;
    double  screen_y;
    double  distance;

    size = (int)(TILE_SIZE * data->scale);
    screen_x = data->minimap_x_center + (x - data->player_x * TILE_SIZE * data->scale);
    screen_y = data->minimap_y_center + (y - data->player_y * TILE_SIZE * data->scale);
    
    int di = -1;
    while (++di < size)
    {
        int dj = -1;
        while (++dj < size)
        {
            distance = sqrt(pow(screen_x + di - data->minimap_x_center, 2)
                + pow(screen_y + dj - data->minimap_y_center, 2));
            if (distance <= data->minimap_radius)
                put_pixel_in_img(image, screen_x + di, screen_y + dj, color);
        }
    }
}

void draw_map(t_data *data, t_image *image)
{
    // double scale = 0.25;
    
    int visible_range = (int)(data->minimap_radius / (TILE_SIZE * data->scale)) + 1;
    
    int player_map_x = (int)data->player_x;
    int player_map_y = (int)data->player_y;
    
    int dy = -visible_range -1;
    while (++dy <= visible_range)
    {
        int dx = -visible_range - 1;
        while (++dx <= visible_range)
        {
            int map_x = player_map_x + dx;
            int map_y = player_map_y + dy;
            
            // Check if the tile is within map bounds
            // if (map_x >= 0 && map_x < data->map.map_width && map_y >= 0 && map_y < data->map.map_height)
            if (map_x >= 0 && map_x < data->map.map_width && 
                map_y >= 0 && map_y < data->map.map_height && 
                data->map.map[map_y] != NULL &&  // Check if row exists
                map_x < (int)ft_strlen(data->map.map[map_y]))
            {
                double tile_x = map_x * TILE_SIZE * data->scale;
                double tile_y = map_y * TILE_SIZE * data->scale;
                
                if (data->map.map[map_y][map_x] == '1')
                    draw_tile(data, image, tile_x, tile_y, 0x000000);
                else if (data->map.map[map_y][map_x] == '0')
                    draw_tile(data, image, tile_x, tile_y, 0xAAAAAA);
            }
        }
    }
}

void draw_player(t_data *data, t_image *image)
{
    int x;
    int y;
    double dist;

    x = -data->player_radius;
    while (++x <= data->player_radius)
    {
        y = -data->player_radius;
        while (++y <= data->player_radius)
        {
            dist = sqrt(x * x + y * y);
            if (dist <= data->player_radius)
                put_pixel_in_img(image, data->minimap_x_center + x,  data->minimap_y_center + y, 0xffff00);
        }
    }
}

void draw_player_direction(t_data *data, t_image *image)
{
    // Draw direction indicator
    double angle = atan2(data->dir_y, data->dir_x);
    double fov = 60 * PI / 180.0; // 60 degrees FOV
    int i = -30 - 1;
    while (++i <= 30)
    {
        double ray_angle = angle + (i * fov / 60);
        double ray_length = MINIMAP_RADIUS * 0.3; // Length of direction indicator
        
        double end_x = data->minimap_x_center + cos(ray_angle) * ray_length;
        double end_y = data->minimap_y_center + sin(ray_angle) * ray_length;
        
        // Draw ray line
        double dx = end_x - data->minimap_x_center;
        double dy = end_y - data->minimap_y_center;
        double steps = fmax(fabs(dx), fabs(dy));
        
        if (steps == 0)
			continue;
        
        double x_increment = dx / steps;
        double y_increment = dy / steps;
        double x = data->minimap_x_center;
        double y = data->minimap_y_center;
        
		int step = -1;
        while (++step <= steps)
        {
            double dist_x = x - data->minimap_x_center;
            double dist_y = y - data->minimap_y_center;
			
            if (sqrt(dist_x * dist_x + dist_y * dist_y) <= MINIMAP_RADIUS)
                put_pixel_in_img(image, round(x), round(y), 0xFF0000);
            x += x_increment;
            y += y_increment;
        }
    }
}

void draw_minimap(t_data *data)
{
    // draw black background for our minimap
	draw_background(data, data->image);
    
    // draw the map (floor and walls)
    draw_map(data, data->image);
    
    // Draw the player's vield od view
    draw_player_direction(data, data->image);
    
    // Draw the player dot (or just the player)	// TODO
    draw_player(data, data->image);
    
    // Draw the minimap border	// TODO
    // draw_minimap_border(data->image);
}

void render_sprites_to_image(t_image *image, t_image *sprite_image, int x, int y)
{
    if (!image || !sprite_image || !image->img_data || !sprite_image->img_data)
        return;

    int sy = -1;
    while (++sy < sprite_image->height)
    {
        int sx = -1;
        while (++sx < sprite_image->width)
        {
            if (sx < 0 || sx >= SCREEN_WIDTH || sy < 0 || sy >= SCREEN_HEIGHT)
                continue;

            int sprite_pixel = ((int *)sprite_image->img_data)[sy * sprite_image->width + sx];

            // Handle transparency (assuming 0xFF000000 is fully transparent)
            if ((sprite_pixel & 0xFF000000) == 0xFF000000)
                continue;

            int dx = x + sx;
            int dy = y + sy;

            // Ensure we don't draw outside the main image bounds
            if (dx >= 0 && dx < SCREEN_WIDTH && dy >= 0 && dy < SCREEN_HEIGHT)
                ((int *)image->img_data)[dy * SCREEN_WIDTH + dx] = sprite_pixel;
        }
    }
}

void render_sprites(t_data *data)
{
    if (!data || !data->mlx_ptr || !data->win_ptr || !data->image)
        return;

    t_image *img = data->image;
    t_image sprite_image = data->player.frames[0]; // Default sprite for rendering

    if (data->shoot)
    {
        // Loop for sprite animation during shooting
        int i = 10;
        // while (++i < 10)
        {
            sprite_image = data->player.frames[i];
            int x = SCREEN_WIDTH / 2 - sprite_image.width / 2;
            int y = SCREEN_HEIGHT - sprite_image.height;

            // Render sprite onto the image buffer (but don’t display yet)
            render_sprites_to_image(img, &sprite_image, x, y);
            mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img->img_ptr, 0, 0);
        }
        data->shoot = 0;
    }
    else
    {
        // Render the default sprite (non-shooting state)
        int x = SCREEN_WIDTH / 2 - sprite_image.width / 2;
        int y = SCREEN_HEIGHT - sprite_image.height;

        render_sprites_to_image(img, &sprite_image, x, y);
    }
    
    // Call mlx_put_image_to_window only once after rendering everything
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img->img_ptr, 0, 0);
}

int game_loop(t_data *data)
{
    // Clear the image
    memset(data->image->img_data, 0, SCREEN_WIDTH * SCREEN_HEIGHT * (data->image->bits_per_pixel / 8));

    // Update player position based on movement
    move_player(data);

    // Perform raycasting and render sprites
    if (!(data->clicks % 2))
    {
        raycasting(data);
        render_sprites(data);
    }
    
    // Draw minimap
    draw_minimap(data);

    // Put image to window (only once after all rendering tasks)
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image->img_ptr, 0, 0);

    return (0);
}

void print_error (char *error_str, char *file, int line)
{
    ft_putstr_fd("\n", 2);
    ft_putstr_fd(error_str, 2);
    ft_putstr_fd("File: ------> ", 2);
    ft_putstr_fd(file, 2);
    ft_putstr_fd("\n", 2);
    ft_putstr_fd("Line: ------> ", 2);
    ft_putnbr_fd(line, 2);
    ft_putstr_fd("\n\n", 2);
}

int check_map_extension(const char *map_path)
{
    int fd;

    if ((fd = open(map_path, O_RDONLY)) == -1)
    {
        print_error("Error: File does not exist!\n", __FILE__, __LINE__);
        return (0);
    }
    else
        close(fd);

    if (!ft_strnstr(&map_path[ft_strlen(map_path) - 4], ".cub", 4))
    {
        print_error("Error, map file extension!\n", __FILE__, __LINE__);
		return (0);
    }
    return (1);
}

int parse_map(int ac, char **av)
{
    if (ac != 2)
    {
        print_error("Error: Bad arguments!\n", __FILE__, __LINE__);
        return (0);
    }
    if (!check_map_extension(av[1]))
        return (0);
    return (1);
}

int main(int ac, char **av)
{
    t_data data;

    if (!parse_map(ac, av))
    {
        print_error("Error: Map parsing failed\n", __FILE__, __LINE__);
        return (1);
    }

    memset(&data, 0, sizeof(t_data));

    data.mlx_ptr = mlx_init();
    if (!data.mlx_ptr)
    {
        print_error("Error: MLX initialization failed\n", __FILE__, __LINE__);
        return (1);
    }

    data.win_ptr = mlx_new_window(data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster");
    if (!data.win_ptr)
    {
        clean_up(&data);
        print_error("Error: Window creation failed\n", __FILE__, __LINE__);
        return (1);
    }

    if (init_game(&data, av[1]) != 0)
    {
        clean_up(&data);
        print_error("Error: Game initialization failed\n", __FILE__, __LINE__);
        return (1);
    }

    mlx_hook(data.win_ptr, 2, 1L<<0, key_press, &data);
    mlx_hook(data.win_ptr, 3, 1L<<1, key_release, &data);
    mlx_hook(data.win_ptr, 4, 1L<<2, mouse_events, &data);
    mlx_loop_hook(data.mlx_ptr, game_loop, &data);
    mlx_loop(data.mlx_ptr);

    return (0);
}

// int main(int ac, char **av)
// {
//     t_data data;
//     (void)ac;
//     (void)av;

//     // if (!parse_map(ac, av))
//     //     return (1);

//     memset(&data, 0, sizeof(t_data));

//     data.mlx_ptr = mlx_init();
//     if (!data.mlx_ptr)
//         return (1);

//     data.win_ptr = mlx_new_window(data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster");
//     if (!data.win_ptr)
//     {
//         clean_up(&data);
//         return (1);
//     }

//     if (init_game(&data, av[1]) != 0)
//     {
//         clean_up(&data);
//         return (1);
//     }

//     mlx_hook(data.win_ptr, 2, 1L<<0, key_press, &data);
//     mlx_hook(data.win_ptr, 3, 1L<<1, key_release, &data);
//     mlx_hook(data.win_ptr, 4, 1L<<2, mouse_events, &data);
//     mlx_loop_hook(data.mlx_ptr, game_loop, &data);
//     mlx_loop(data.mlx_ptr);

//     return (0);
// }
