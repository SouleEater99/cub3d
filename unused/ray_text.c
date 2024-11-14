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
    # define ESC_KEY        65307
    # define U_KEY          65362
    # define D_KEY          65364
    # define R_KEY          65363
    # define L_KEY          65361
    
    // # define MOVE_SPEED     0.08    // player speed
    // # define ROT_SPEED      0.06    // Rotation speed (in radians)

    # define MOVE_SPEED     0.02    // player speed
    # define ROT_SPEED      0.01    // Rotation speed (in radians)

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
}   t_image;

typedef struct s_texture {
    void    *img_ptr;
    int     *data;
    int     width;
    int     height;
    int     bits_per_pixel;
    int     size_line;
    int     endian;
} t_texture;

typedef struct s_player
{
    double  dir_x;
    double  dir_y;
    double  player_x;
    double  player_y;
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

    t_texture    textures[4];  // NO, SO, WE, EA
    double      wall_x;        // Where exactly the wall was hit
    int         tex_x;         // X coordinate on the texture
    int         tex_y;         // Y coordinate on the texture
    double      step;          // How much to increase the texture coordinate per screen pixel
    double      tex_pos;       // Starting texture coordinate
} t_data;



// functions definition.
void draw_vert_cols(t_data *data, int x);
void load_texture(t_data *data, t_texture *texture, char *path);
void init_textures(t_data *data);
void    put_pixel_in_img(t_image *image, int x, int y, int color);
t_image *create_image(t_data *data);
void free_map(char **map);
int read_map(t_data *data, char *map_path);
int init_map(t_data *data, char *map_path);
int init_player_direction(t_data *data);
int init_game(t_data *data, char *map_path);
void clean_up(t_data *data);
int key_press(int keycode, t_data *data);
int key_release(int keycode, t_data *data);
int check_click_space(t_data *data, int x, int y);
int mouse_events(int button, int x, int y, t_data *data);
void draw_vert_line(t_image *image, int x, int draw_start, int draw_end, int color);
void dda_algorithm(t_data *data);
void calculate_side_dist_x_y(t_data *data);
void raycasting(t_data *data);
void rotate_player(t_data *data, double rot_speed);
void move_player(t_data *data);
void draw_background(t_data *data, t_image *image);
void draw_tile(t_data *data, t_image *image, double x, double y, int color);
void draw_map(t_data *data, t_image *image);
void draw_player(t_data *data, t_image *image);
void draw_player_direction(t_data *data, t_image *image);
void draw_minimap(t_data *data);
int game_loop(t_data *data);
void print_error (char *error_str, char *file, int line);
int check_map_extension(const char *map_path);
int parse_map(int ac, char **av);
void calculate_texture_coordinates(t_data *data);
void draw_textured_line(t_data *data, int x);
void draw_vert_cols(t_data *data, int x);




void load_texture(t_data *data, t_texture *texture, char *path)
{
    // Load the texture using MLX
    texture->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, path, 
                                            &texture->width, &texture->height);
    if (!texture->img_ptr)
        return;

    // Get the texture data
    texture->data = (int *)mlx_get_data_addr(texture->img_ptr, 
                                            &texture->bits_per_pixel,
                                            &texture->size_line,
                                            &texture->endian);
}

void init_textures(t_data *data)
{
    // Load all textures
    load_texture(data, &data->textures[0], data->no_texture_path); // North
    load_texture(data, &data->textures[1], data->so_texture_path); // South
    load_texture(data, &data->textures[2], data->we_texture_path); // West
    load_texture(data, &data->textures[3], data->ea_texture_path); // East
}




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

int read_map(t_data *data, char *map_path)
{
    int     i;
    int     fd;
    char    *line;
    char    **lines;

    fd = open(map_path, O_RDONLY);
    if (fd == -1)
        return (printf("FILE: %s, LINE: %d\n", __FILE__, __LINE__), perror(map_path), 0);
    
    i = 0;
    line = get_next_line(fd);
    if (!line)
        return (close(fd), 0);
    
    data->map.map_width = ft_strlen(line) - 1;
    while (line)
    {
        ++i;
        printf("%s", line);  // For debug
        free(line);
        line = get_next_line(fd);
    }
    data->map.map_height = i;
    close(fd);

    fd = open(map_path, O_RDONLY);
    if (fd == -1)
        return (0);
    
    lines = (char **)malloc(sizeof(char *) * (data->map.map_height + 1));
    if (!lines)
        return (close(fd), 0);
    
    // Read and store each line
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

int init_game(t_data *data, char *map_path)
{
    data->scale = SCALE;
    data->rot_speed = ROT_SPEED;
    data->move_speed = MOVE_SPEED;
    data->player_radius = PLAYER_RADIUS;
    data->minimap_radius = MINIMAP_RADIUS;
    data->minimap_x_center = MINIMAP_MID_X;
    data->minimap_y_center = MINIMAP_MID_Y;

    // data->map.map_width = MAP_WIDTH;
    // data->map.map_height = MAP_HEIGHT;
    // data->map.map_path = av[1];

    data->player_x = 2.0;
    data->player_y = 2.0;

    if (init_player_direction(data))
        return (1);

    if (init_map(data, map_path) != 0)
        return (1);

    // Create the persistent image
    data->image = create_image(data);
    if (!data->image)
        return (1);

    return (0);
}

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
}

int key_press(int keycode, t_data *data)
{
    if (keycode == ESC_KEY)
    {
        clean_up(data);
        exit(0);
    }
    else if (keycode == 'w' || keycode == U_KEY)
        data->move_forward = 1;
    else if (keycode == 's' || keycode == D_KEY)
        data->move_backward = 1;
    else if (keycode == 'a' || keycode == L_KEY)
        data->rotate_left = 1;
    else if (keycode == 'd' || keycode == R_KEY)
        data->rotate_right = 1;
    return (0);
}

int key_release(int keycode, t_data *data)
{
    if (keycode == 'w' || keycode == U_KEY)
        data->move_forward = 0;
    else if (keycode == 's' || keycode == D_KEY)
        data->move_backward = 0;
    else if (keycode == 'a' || keycode == L_KEY)
        data->rotate_left = 0;
    else if (keycode == 'd' || keycode == R_KEY)
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
            data->rot_speed = ROT_SPEED * 8;
            data->move_speed = MOVE_SPEED * 8;
            data->player_radius = PLAYER_RADIUS;
            data->minimap_radius = MINIMAP_RADIUS * 10;
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

// void draw_vert_cols(t_data *data, int x)
// {
//     int color = 0xFFFFFF;

//     if (data->side == 0)
//         data->perp_wall_dist = data->side_dist_x - data->delta_dist_x;
//     else
//         data->perp_wall_dist = data->side_dist_y - data->delta_dist_y;

//     color = (data->side == 0) ? CLR_EAW : CLR_SAN;

//     data->line_height = (int)(SCREEN_HEIGHT / data->perp_wall_dist);
//     data->draw_start = -data->line_height / 2 + SCREEN_HEIGHT / 2;
//     data->draw_start = (data->draw_start < 0) ? 0 : data->draw_start;

//     data->draw_end = data->line_height / 2 + SCREEN_HEIGHT / 2;
//     data->draw_end = (data->draw_end >= SCREEN_HEIGHT) ? SCREEN_HEIGHT - 1 : data->draw_end;

//     draw_vert_line(data->image, x, 0, data->draw_start, CLR_SKY);
//     draw_vert_line(data->image, x, data->draw_start, data->draw_end, color);
//     draw_vert_line(data->image, x, data->draw_end, SCREEN_HEIGHT, CLR_FLR);
// }

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
        calculate_side_dist_x_y(data);

        // Perform DDA algorithm
        dda_algorithm(data);

        // Draw the vertical wall strips
        draw_vert_cols(data, x);
    }
}

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

int game_loop(t_data *data)
{
    // Clear the image
    memset(data->image->img_data, 0, SCREEN_WIDTH * SCREEN_HEIGHT * (data->image->bits_per_pixel / 8));

    // Update player position based on movement
    move_player(data);

    // Perform raycasting
    raycasting(data);

    // Draw minimap
    draw_minimap(data);

    // Put image to window
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





void calculate_texture_coordinates(t_data *data)
{
    // Calculate wall_x (where exactly the wall was hit)
    if (data->side == 0)
        data->wall_x = data->player_y + data->perp_wall_dist * data->ray_dir_y;
    else
        data->wall_x = data->player_x + data->perp_wall_dist * data->ray_dir_x;
    data->wall_x -= floor(data->wall_x);

    // Get texture index based on wall direction
    int tex_num;
    if (data->side == 0 && data->ray_dir_x > 0)
        tex_num = 3; // East
    else if (data->side == 0 && data->ray_dir_x < 0)
        tex_num = 2; // West
    else if (data->side == 1 && data->ray_dir_y > 0)
        tex_num = 1; // South
    else
        tex_num = 0; // North

    // Calculate x coordinate on the texture
    data->tex_x = (int)(data->wall_x * data->textures[tex_num].width);
    if (data->side == 0 && data->ray_dir_x < 0)
        data->tex_x = data->textures[tex_num].width - data->tex_x - 1;
    if (data->side == 1 && data->ray_dir_y > 0)
        data->tex_x = data->textures[tex_num].width - data->tex_x - 1;

    // Calculate how much to increase the texture coordinate per screen pixel
    data->step = 1.0 * data->textures[tex_num].height / data->line_height;
    // Starting texture coordinate
    data->tex_pos = (data->draw_start - SCREEN_HEIGHT / 2 + data->line_height / 2) * data->step;
}

void draw_textured_line(t_data *data, int x)
{
    // Draw ceiling
    draw_vert_line(data->image, x, 0, data->draw_start, CLR_SKY);

    // Get texture index based on wall direction
    int tex_num;
    if (data->side == 0 && data->ray_dir_x > 0)
        tex_num = 3; // East
    else if (data->side == 0 && data->ray_dir_x < 0)
        tex_num = 2; // West
    else if (data->side == 1 && data->ray_dir_y > 0)
        tex_num = 1; // South
    else
        tex_num = 0; // North

    // Draw the textured wall
    for (int y = data->draw_start; y < data->draw_end; y++)
    {
        data->tex_y = (int)data->tex_pos & (data->textures[tex_num].height - 1);
        data->tex_pos += data->step;

        // Get the color from the texture
        int color = data->textures[tex_num].data[data->textures[tex_num].height * data->tex_y + data->tex_x];
        
        // Make color darker for y-sides
        if (data->side == 1)
            color = (color >> 1) & 8355711;

        put_pixel_in_img(data->image, x, y, color);
    }

    // Draw floor
    draw_vert_line(data->image, x, data->draw_end, SCREEN_HEIGHT, CLR_FLR);
}

// Modified draw_vert_cols function
void draw_vert_cols(t_data *data, int x)
{
    if (data->side == 0)
        data->perp_wall_dist = data->side_dist_x - data->delta_dist_x;
    else
        data->perp_wall_dist = data->side_dist_y - data->delta_dist_y;

    // Calculate height of line to draw on screen
    data->line_height = (int)(SCREEN_HEIGHT / data->perp_wall_dist);

    // Calculate lowest and highest pixel to fill in current stripe
    data->draw_start = -data->line_height / 2 + SCREEN_HEIGHT / 2;
    if (data->draw_start < 0)
        data->draw_start = 0;
    data->draw_end = data->line_height / 2 + SCREEN_HEIGHT / 2;
    if (data->draw_end >= SCREEN_HEIGHT)
        data->draw_end = SCREEN_HEIGHT - 1;

    // Calculate texture coordinates
    calculate_texture_coordinates(data);

    // Draw the textured line
    draw_textured_line(data, x);
}



int main(int ac, char **av)
{
    t_data data;
    (void)ac;
    (void)av;

    // if (!parse_map(ac, av))
    //     return (1);

    memset(&data, 0, sizeof(t_data));

    data.mlx_ptr = mlx_init();
    if (!data.mlx_ptr)
        return (1);

    data.win_ptr = mlx_new_window(data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster");
    if (!data.win_ptr)
    {
        clean_up(&data);
        return (1);
    }

    if (init_game(&data, av[1]) != 0)
    {
        clean_up(&data);
        return (1);
    }

    mlx_hook(data.win_ptr, 2, 1L<<0, key_press, &data);
    mlx_hook(data.win_ptr, 3, 1L<<1, key_release, &data);
    mlx_hook(data.win_ptr, 4, 1L<<2, mouse_events, &data);
    mlx_loop_hook(data.mlx_ptr, game_loop, &data);
    mlx_loop(data.mlx_ptr);

    return (0);
}
